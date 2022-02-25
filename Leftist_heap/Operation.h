#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#include<malloc.h>
typedef int Data;
struct left_heap
{
    Data e;
    left_heap *lt;
    left_heap *rt;
    int npl;
};
left_heap *merge2(left_heap *,left_heap *);
left_heap *merge1(left_heap *H1,left_heap *H2)
{
    if(H1==NULL)
        return H2;
    if(H1->e<H2->e)
        return merge2(H1,H2);
    else
        return merge2(H2,H1);
}
void swap_children(left_heap *H)
{
    left_heap *tmp=H->lt;
    H->lt=H->rt;
    H->rt=tmp;
}
left_heap *merge2(left_heap *H1,left_heap *H2)
{
    if(H1->lt==NULL)
        H1->lt=H2;
    else
    {
        H1->rt=merge1(H1->rt,H2);
        if(H1->lt->npl<H1->rt->npl)
            swap_children(H1);
        H1->npl=H1->rt->npl+1;
    }
    return H1;
}
left_heap *Insert_node(left_heap *H,Data key)
{
    left_heap *newnode=(left_heap *)malloc(sizeof(left_heap));
    newnode->e=key;
    newnode->lt=newnode->rt=NULL;
    newnode->npl=0;
    return merge1(H,newnode);
}
left_heap *Delete_min(left_heap *H)
{
    left_heap *left=H->lt,*right=H->rt;
    free(H);
    if(right==NULL) return left;
    return merge1(left,right);
}
void Tree_print(left_heap *H,int floor)
{
    if(H==NULL)
        return;
    else
    {
        Tree_print(H->rt,floor+1);
        for(int i=1;i<=floor;i++)
            printf("  ");
        printf("%d\n",H->e);
        Tree_print(H->lt,floor+1);
    }
}
void Inorder_traversal_npl(left_heap *H)
{
    if(H)
    {
        Inorder_traversal_npl(H->lt);
        printf("Data:%d npl:%d\n",H->e,H->npl);
        Inorder_traversal_npl(H->rt);
    }
}
void Delete_left_heap(left_heap *H)
{
    if(H)
    {
        Delete_left_heap(H->lt);
        Delete_left_heap(H->rt);
        free(H);
    }
}
#endif // OPERATION_H_INCLUDED

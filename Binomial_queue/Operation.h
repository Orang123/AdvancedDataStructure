#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#include<malloc.h>
#define maxn 10
#define INF 0x3f3f3f3f
typedef int  Data;
struct Binnode
{
    Data e;
    Binnode *leftchild;
    Binnode *nextsibling;
};
struct Binqueue
{
    int cursize;
    Binnode *Thetrees[maxn];
};
void Init_Binqueue(Binqueue **Q)
{
    *Q=(Binqueue *)malloc(sizeof(Binqueue));
    (*Q)->cursize=0;
    for(int i=0;i<maxn;i++)
        (*Q)->Thetrees[i]=NULL;
}
void Init_Binnode(Binnode **T,Data key)
{
    *T=(Binnode *)malloc(sizeof(Binnode));
    (*T)->e=key;
    (*T)->leftchild=(*T)->nextsibling=NULL;
}
Binnode *Combinetrees(Binnode *T1,Binnode *T2)
{
    if(T1->e>T2->e)
        return Combinetrees(T2,T1);
    T2->nextsibling=T1->leftchild;
    T1->leftchild=T2;
    return T1;
}
void Merge_queue(Binqueue *Q1,Binqueue *Q2)
{
    Binnode *T1,*T2,*carry=NULL;
    Q1->cursize+=Q2->cursize;
    for(int i=0,j=1;j<=Q1->cursize;i++,j*=2)
    {
        T1=Q1->Thetrees[i],T2=Q2->Thetrees[i];
        switch(!!T1+2*!!T2+4*!!carry)
        {
        case 0:
        case 1:
            break;
        case 2:
            Q1->Thetrees[i]=T2;
            Q2->Thetrees[i]=NULL;break;
        case 3:
            carry=Combinetrees(T1,T2);
            Q1->Thetrees[i]=Q2->Thetrees[i]=NULL;break;
        case 4:
            Q1->Thetrees[i]=carry;
            carry=NULL;break;
        case 5:
            carry=Combinetrees(T1,carry);
            Q1->Thetrees[i]=NULL;
            break;
        case 6:
            carry=Combinetrees(T2,carry);
            Q2->Thetrees[i]=NULL;
            break;
        case 7:
            Q1->Thetrees[i]=carry;
            carry=Combinetrees(T1,T2);
            Q2->Thetrees[i]=NULL;
            break;
        }
    }
}
Data Delete_min(Binqueue *Q)
{
    Binqueue *Delete_queue;
    Init_Binqueue(&Delete_queue);
    Binnode *Deletedtree,*oldroot;
    int min_tree;
    Data min_data=INF;
    for(int i=0,j=1;j<=Q->cursize;i++,j*=2)//这里之所以采取线性遍历,是因为操作系统进程并不是很多,并不是用户百万级的数据,所以没必要小题大做采取AVL查找树来查找最左边的最小元或者也可以线索化
        if(Q->Thetrees[i]&&Q->Thetrees[i]->e<min_data)
    {
        min_data=Q->Thetrees[i]->e;
        min_tree=i;
    }
    oldroot=Deletedtree=Q->Thetrees[min_tree];
    Q->Thetrees[min_tree]=NULL;
    Deletedtree=Deletedtree->leftchild;
    free(oldroot);
    for(int i=min_tree-1;i>=0;i--)
    {
        Delete_queue->Thetrees[i]=Deletedtree;
        Deletedtree=Deletedtree->nextsibling;
        Delete_queue->Thetrees[i]->nextsibling=NULL;
    }
    Delete_queue->cursize=(1<<min_tree)-1;
    Q->cursize-=Delete_queue->cursize+1;//+1是为了把当时删去的最小根节点删去
    Merge_queue(Q,Delete_queue);
    return min_data;
}
void Inorder_traversal(Binnode *T)
{
    if(T)
    {
        Inorder_traversal(T->leftchild);
        printf("%d ",T->e);
        Inorder_traversal(T->nextsibling);
    }
}
void Display_node(Binqueue *Q)
{
    for(int i=0,j=1;j<=Q->cursize;i++,j*=2)
        if(Q->Thetrees[i])
    {
        Inorder_traversal(Q->Thetrees[i]);
        putchar('\n');
    }
}
void Delete_Binnode(Binnode *T)
{
    if(T)
    {
        Delete_Binnode(T->leftchild);
        Delete_Binnode(T->nextsibling);
        free(T);
    }
}
void Delete_Binqueue(Binqueue *Q)
{
    for(int i=0,j=1;j<=Q->cursize;i++,j*=2)
        if(Q->Thetrees[i])
            Delete_Binnode(Q->Thetrees[i]);
}
#endif // OPERATION_H_INCLUDED

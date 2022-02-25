#ifndef OPERATION_H_INCLUDED//试着想一想树的树状输出,能宏观地看出树的结构,大概是竖着输出可能能实现
#define OPERATION_H_INCLUDED
typedef char Data;
struct CB_tree
{
    Data e;
    CB_tree *firstchild;
    CB_tree *nextchild;
};
void Creat_CB_tree(CB_tree **T)
{
    Data p;
    printf("Please input tree_node's data:");
    scanf(" %c",&p);
    if(p=='#') (*T)=NULL;
    else
    {
        *T=(CB_tree *)malloc(sizeof(CB_tree));
        (*T)->e=p;
        Creat_CB_tree(&(*T)->firstchild);
        Creat_CB_tree(&(*T)->nextchild);
    }
}
int CB_tree_Deep(CB_tree *T)
{
    if(T==NULL)
        return 0;
    int k,floor=0;
    T=T->firstchild;
    while(T)
    {
        k=CB_tree_Deep(T);
        if(floor<k)
            floor=k;
        T=T->nextchild;
    }
    return floor+1;
}
void Display_CB_tree(Data e)
{
    printf("%c",e);
}
void Pretraverse_CB_tree(CB_tree *T,void(*visit)(Data e))
{
    if(T)
    {
        (*visit)(T->e);
        Pretraverse_CB_tree(T->firstchild,visit);
        Pretraverse_CB_tree(T->nextchild,visit);
    }
}
void Posttraverse_CB_tree(CB_tree *T,void(*visit)(Data e))
{
    if(T)
    {
        Posttraverse_CB_tree(T->firstchild,visit);
        (*visit)(T->e);
        Posttraverse_CB_tree(T->nextchild,visit);
    }
}
void Delete_CB_tree(CB_tree *T)
{
    if(T)
    {
        Delete_CB_tree(T->firstchild);
        Delete_CB_tree(T->nextchild);
        free(T);
        T=NULL;
    }
}
#endif // OPERATION_H_INCLUDED

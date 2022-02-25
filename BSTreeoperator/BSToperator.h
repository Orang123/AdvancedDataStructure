#ifndef BSTOPERATOR_H_INCLUDED
#define BSTOPERATOR_H_INCLUDED
#include<malloc.h>
typedef int Data;
struct BST
{
    Data e;
    BST *lchild,*rchild;
};
void BSTree_creat_insert(BST **T,Data x)
{
    if(*T==NULL)
    {
        *T=(BST *)malloc(sizeof(BST));
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->e=x;
    }
    else
    {
        if(x>(*T)->e)
            BSTree_creat_insert(&(*T)->rchild,x);
        else if(x<(*T)->e)
            BSTree_creat_insert(&(*T)->lchild,x);
        else if(x==(*T)->e)
            return;
    }
}
bool BSTree_insert(BST **T,Data x)
{
    BST *p,*parent=NULL,*tmp=*T;
    while(tmp)
    {
        parent=tmp;
        if(x<tmp->e)
            tmp=tmp->lchild;
        else if(x>tmp->e)
            tmp=tmp->rchild;
        else
            return false;
    }
    p=(BST *)malloc(sizeof(BST));
    p->e=x;
    p->rchild=p->lchild=NULL;
    if(parent==NULL)
    {
        *T=p;
        return true;
    }
    else if(x<parent->e)
        parent->lchild=p;
    else
        parent->rchild=p;
    return true;
}
BST* search_BSTree(BST *T,Data x)
{
    while(T!=NULL)
    {
        if(x>T->e)
            T=T->rchild;
        else if(x<T->e)
            T=T->lchild;
        else
            return T;
    }
    return NULL;
}
void delete_BST_node1(BST **T)
{
    BST *temp,*x;
    if((*T)->lchild==NULL)//要删除的元素左孩子为空
    {
        temp=*T;
        *T=(*T)->rchild;//令要删除结点的右子树取代它
        free(temp);
    }
    else if((*T)->rchild==NULL)//要删除的元素右孩子为空
    {
        temp=*T;
        *T=(*T)->lchild;//令要删除结点的左子树取代它
        free(temp);
    }
    else
    {
        temp=*T;
        x=(*T)->lchild;
        while(x->rchild)//找到要删除结点的前驱
        {
            temp=x;
            x=x->rchild;
        }
        (*T)->e=x->e;//令前驱元素取代要删除结点
        if(temp!=*T)
            temp->rchild=x->lchild;//令前驱元素的前驱的右子树指向前驱元素的左子树,这有这样才能重新回到二叉排序树
        else//要删除结点的直接前驱为其左子树
            temp->lchild=x->lchild;
        free(x);
    }
}
void delete_BST_node2(BST **T)
{
    BST *x,*y;
    if((*T)->lchild==NULL)
    {
        x=*T;
        *T=(*T)->rchild;
        free(x);
    }
    else if((*T)->rchild==NULL)
    {
        x=*T;
        *T=(*T)->lchild;
        free(x);
    }
    else
    {
        y=*T;
        x=(*T)->rchild;
        while(x->lchild)
        {
            y=x;
            x=x->lchild;
        }
        y->e=x->e;
        if(y!=*T)
            y->lchild=x->rchild;
        else
            y->rchild=x->rchild;
        free(x);
    }
}
void delete_BST_node3(BST **T)//这种删除操作过于极端每次删除后左子树会偏高会极具不平衡,会将原先的一个根节点所连接的一个左右子树被新生成的左子树所替代,不过好像减少了右子树的个数
{
    BST *x,*y;
    if(!(*T)->lchild)
    {
        x=*T;
        *T=(*T)->rchild;
        free(x);
    }
    else if(!(*T)->rchild)
    {
        x=*T;
        *T=(*T)->lchild;
        free(x);
    }
    else
    {
        x=*T;
        y=(*T)->lchild;
        while(y->rchild)//找到要删除结点的直接前驱
            y=y->rchild;
        y->rchild=x->rchild;//令要删除结点的直接前驱指向要删除结点的直接后继即右子树
        *T=(*T)->lchild;//再令原先要删除结点的左子树取代它本身,这样避免再重复遍历要删除结点的右子树即直接后继
        free(x);
    }
}
void search_delete_node(BST **T,Data x)
{
    if(*T)
    {
        if(x<(*T)->e)
            search_delete_node(&(*T)->lchild,x);
        else if(x>(*T)->e)
            search_delete_node(&(*T)->rchild,x);
        else
            delete_BST_node3(&(*T));//delete_BST_node2(&(*T));//delete_BST_node1(&(*T));//这里采用在search里间接调用主要是因为，要传递真正的结点的指针的地址,方便在delete中真正意义上对于叶子结点的删除可以直接替代
    }
    else
        printf("There is no element.\n");
}
void Inorder_traversal(BST *T)
{
    if(T)
    {
        Inorder_traversal(T->lchild);
        printf("%d->",T->e);
        Inorder_traversal(T->rchild);
    }
}
void Tree_print(BST *T,int floor)
{
    if(T==NULL)
        return;
    else
    {
        Tree_print(T->rchild,floor+1);
        for(int i=1;i<=floor;i++)
            printf("  ");
            printf("%d\n",T->e);
        Tree_print(T->lchild,floor+1);
    }
}

#endif // BSTOPERATOR_H_INCLUDED

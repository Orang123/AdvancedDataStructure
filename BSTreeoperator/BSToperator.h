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
    if((*T)->lchild==NULL)//Ҫɾ����Ԫ������Ϊ��
    {
        temp=*T;
        *T=(*T)->rchild;//��Ҫɾ������������ȡ����
        free(temp);
    }
    else if((*T)->rchild==NULL)//Ҫɾ����Ԫ���Һ���Ϊ��
    {
        temp=*T;
        *T=(*T)->lchild;//��Ҫɾ������������ȡ����
        free(temp);
    }
    else
    {
        temp=*T;
        x=(*T)->lchild;
        while(x->rchild)//�ҵ�Ҫɾ������ǰ��
        {
            temp=x;
            x=x->rchild;
        }
        (*T)->e=x->e;//��ǰ��Ԫ��ȡ��Ҫɾ�����
        if(temp!=*T)
            temp->rchild=x->lchild;//��ǰ��Ԫ�ص�ǰ����������ָ��ǰ��Ԫ�ص�������,���������������»ص�����������
        else//Ҫɾ������ֱ��ǰ��Ϊ��������
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
void delete_BST_node3(BST **T)//����ɾ���������ڼ���ÿ��ɾ������������ƫ�߻Ἣ�߲�ƽ��,�Ὣԭ�ȵ�һ�����ڵ������ӵ�һ�����������������ɵ������������,��������������������ĸ���
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
        while(y->rchild)//�ҵ�Ҫɾ������ֱ��ǰ��
            y=y->rchild;
        y->rchild=x->rchild;//��Ҫɾ������ֱ��ǰ��ָ��Ҫɾ������ֱ�Ӻ�̼�������
        *T=(*T)->lchild;//����ԭ��Ҫɾ������������ȡ��������,�����������ظ�����Ҫɾ��������������ֱ�Ӻ��
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
            delete_BST_node3(&(*T));//delete_BST_node2(&(*T));//delete_BST_node1(&(*T));//���������search���ӵ�����Ҫ����Ϊ��Ҫ���������Ľ���ָ��ĵ�ַ,������delete�����������϶���Ҷ�ӽ���ɾ������ֱ�����
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

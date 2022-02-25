#ifndef LINKBITTREE_H_INCLUDED//这里在队列的处理上采取的是顺序队列,实际上我可以构造链式队列,这样就不必在静态分配数组了,后面自己再改改
#define LINKBITTREE_H_INCLUDED
#include<malloc.h>
#define maxsize 100
typedef char Data;
enum
{
    Link,Thread
};
typedef struct Bit_tree
{
    Data e;
    Bit_tree *lchild,*rchild;
    int ltag,rtag;
}Bit_node;
Bit_tree *Pre;
void Creat_Bit_tree(Bit_tree **T)//这里主要是为了能使二叉树的左右孩子数的结点与根结点能够连续,才采取二级指针来传递指针参数的,如果是一级指针则会成为值传递,左右孩子树与根节点就不会连接起来
{
    Data c;
    printf("Please input node 's data which you want to creat:");
    scanf(" %c",&c);
    if(c=='#') *T=NULL;
    else
    {
        *T=(Bit_tree *)malloc(sizeof(Bit_node));
        (*T)->e=c;
        (*T)->ltag=Link;
        (*T)->rtag=Link;
        Creat_Bit_tree(&(*T)->lchild);
        Creat_Bit_tree(&(*T)->rchild);
    }
}
void Tree_print(Bit_tree *T,int floor)
{
    if(T==NULL)
        return;
    else
    {
        Tree_print(T->rchild,floor+1);
        for(int i=1;i<=floor;i++)
            printf("  ");
            printf("%c\n",T->e);
        Tree_print(T->lchild,floor+1);
    }
}
void Level_print(Bit_tree *T)//按层输出
{
    Bit_tree *queue[maxsize];
    int front=-1,rear=0;
    Bit_node *p;
    queue[rear]=T;
    while(front!=rear)
    {
        front=(front+1)%maxsize;
        p=queue[front];
        printf("%c",p->e);
        if(p->lchild)
        {
            rear=(rear+1)%maxsize;
            queue[rear]=p->lchild;
        }
        if(p->rchild)
        {
            rear=(rear+1)%maxsize;
            queue[rear]=p->rchild;
        }
    }
}
void Preorder_traversal1(Bit_tree *T,int floor)//递归前序遍历二叉树的结点
{
    if(T)
    {
        printf("The %d floor:%c\n",floor,T->e);
        Preorder_traversal1(T->lchild,floor+1);
        Preorder_traversal1(T->rchild,floor+1);
    }
}
void Preorder_traversal2(Bit_tree *T)//非递归前序遍历二叉树的结点
{
    Bit_tree *stack[maxsize];
    int floor=0;
    while(T||floor>0)
    {
        while(T)
        {
            printf("%c",T->e);
            stack[floor++]=T;
            T=T->lchild;
        }
        if(floor>0)
        {
            T=stack[--floor];
            T=T->rchild;
        }
    }
}
void Inorder_traversal1(Bit_tree *T,int floor)//递归中序遍历二叉树的结点
{
    if(T)
    {
        Inorder_traversal1(T->lchild,floor+1);
        printf("The %d floor:%c\n",floor,T->e);
        Inorder_traversal1(T->rchild,floor+1);
    }
}
void Inorder_traversal2(Bit_tree *T)//非递归中序遍历二叉树的结点
{
    Bit_tree *stack[maxsize];
    int floor=0;
    while(T||floor>0)
    {
        while(T)
        {
            stack[floor++]=T;
            T=T->lchild;
        }
        if(floor>0)
        {
            T=stack[--floor];
            printf("%c",T->e);
            T=T->rchild;
        }
    }
}
void postorder_traversal1(Bit_tree *T,int floor)//递归后序遍历二叉树的结点
{
    if(T)
    {
        postorder_traversal1(T->lchild,floor+1);
        postorder_traversal1(T->rchild,floor+1);
        printf("The %d floor:%c\n",floor,T->e);
    }
}
void postorder_traversal2(Bit_tree *T)//非递归后序遍历二叉树的结点
{
    Bit_tree *stack[maxsize];
    Bit_tree *p;
    p=T;
    int floor=0;
    while(T||floor>0)
    {
        while(T)
        {
            stack[floor++]=T;
            T=T->lchild;
        }
        if(floor>0)
        {
            T=stack[floor-1];
            if(T->rchild==NULL||T->rchild==p)//这里还没想清楚是为什么,T->rchild==p就会进入if
            {
                printf("%c",T->e);
                p=T;
                T=NULL;
                floor--;
            }
            else
                T=T->rchild;
        }
    }
}
int leaf_num(Bit_tree *T)//求二叉树中的叶子结点
{
    if(T==NULL)
        return 0;
    if(T->lchild==NULL&&T->rchild==NULL)
        return 1;
    return leaf_num(T->lchild)+leaf_num(T->rchild);
}
int Not_leaf_num(Bit_tree *T)//求二叉树的非叶子结点
{
    if(T==NULL)
        return 0;
    if(T->lchild==NULL&&T->rchild==NULL)
        return 0;
    return Not_leaf_num(T->lchild)+Not_leaf_num(T->rchild)+1;
}
int Tree_deep(Bit_tree *T)//求二叉树的深度,这里还没有完全想清楚,下次有时间再想想
{
    int deep=0,deepl,deepr;
    if(T==NULL)
        return 0;
    deepl=Tree_deep(T->lchild);
    deepr=Tree_deep(T->rchild);
    deep=deepl>deepr?deepl:deepr;
    return deep+1;
}
/*void delete_Bit_node(Bit_tree *T)//非线索化的二叉树删除结点操作
{
    if(T)
    {
        if(T->lchild)
            delete_Bit_node(T->lchild);
        if(T->rchild)
            delete_Bit_node(T->rchild);
        free(T);
        T=NULL;
    }
}*/
void  delete_Thread_Bit_tree(Bit_tree *T)//删除线索化的二叉树结点操作
{
    Bit_tree *p=T->lchild,*temp;
    while(p!=T)
    {
        while(p->ltag==Link)
            p=p->lchild;
        while(p->rtag==Thread&&p->rchild!=T)
        {
            temp=p;
            p=p->rchild;
            free(temp);
        }
        temp=p;
        p=p->rchild;
        free(temp);
    }
}
void InThreading(Bit_tree *T)//二叉树的中序线索化
{
    if(T)
    {
        InThreading(T->lchild);
        if(T->lchild==NULL)//若左子树为NULL,则将其左孩子指向其前驱结点
        {
            T->ltag=Thread;
            T->lchild=Pre;
        }
        if(Pre->rchild==NULL)//若其前驱结点的有孩子为空,则将其右孩子（即Pre的后继结点）指向按中序回溯后的T这个结点
        {
            Pre->rtag=Thread;
            Pre->rchild=T;
        }
        Pre=T;
        InThreading(T->rchild);//执行正常的中序遍历
    }
}
void Inorder_Threading(Bit_tree *T,Bit_tree **top)
{
    *top=(Bit_tree *)malloc(sizeof(Bit_tree));
    (*top)->ltag=Link;
    (*top)->rtag=Thread;
    (*top)->rchild=*top;
    if(T==NULL)
        (*top)->lchild=*top;
    else
    {
        (*top)->lchild=T;
        Pre=*top;
        InThreading(T);
        Pre->rtag=Thread;//这里是为了将中序遍历的结点首尾相接,构成一个循环链表的样子,方便操作
        Pre->rchild=*top;
        (*top)->rchild=Pre;
    }
}
Bit_node *Insearch_pre(Bit_tree *p)//在中序线索树中查找结点P的直接前驱
{
    if(p->ltag==Thread)//如果该结点的没有左子树,则lchild指向的就是其前驱结点
        return p->lchild;
    else//这里的实现感觉其实不是线索树也可以就是其左子树里的最右边下一个右孩子为空的那个结点
    {
        p=p->lchild;//否则需按照中序遍历的方式先去遍历其左子树
        while(p->rtag==Link)//每次只需考虑其右字树,因为只有当把子树的最后一个右结点(即右叶子结点)遍历完成后,也就是当其rtag为Thread指向后继结点的时候,这个后继结点就是当前所要求的结点
            p=p->rchild;
        return p;
    }
}
Bit_node *Insearch_post(Bit_tree *p)
{
    if(p->rtag==Thread)//如果该结点没有右子树,说明该结点的rchild指向直接后继结点
        return p->rchild;
    else
    {
        p=p->rchild;//否则按照中序遍历的方式,先去遍历其右子树
        while(p->ltag==Link)//一直查找到其左叶子结点
        p=p->lchild;
        return p;
    }
}
void Inorder_Traverse_Thread(Bit_tree *T)
{
    Bit_tree *p=T->lchild;
    while(p!=T)
    {
        while(p->ltag==Link)
            p=p->lchild;
            //if(p->e==x)用于线索化的高效查找操作
            //return p;
        printf("%c",p->e);
        while(p->rtag==Thread&&p->rchild!=T)
        {
            p=p->rchild;
            //if(p->e==x) return p;
            printf("%c",p->e);
        }
        p=p->rchild;//若p->rtag不为Thread,则执行正常的中序遍历
    }
    putchar('\n');
}
int judge_similar_Bit_tree(Bit_tree *T,Bit_tree *T0)
{
    if(T==NULL&&T0==NULL)
        return 1;
    else if((T==NULL&&T0)||(T&&T0==NULL))
        return 0;
    return judge_similar_Bit_tree(T->lchild,T0->lchild)*judge_similar_Bit_tree(T->rchild,T0->rchild);
}
#endif // LINKBITTREE_H_INCLUDED

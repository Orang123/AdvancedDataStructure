#ifndef AVL_OPERATE_H_INCLUDED//还缺少删除结点后AVL树的平衡调整,自己仔细再想想
#define AVL_OPERATE_H_INCLUDED
#include<malloc.h>
typedef int Data;
typedef struct AVL
{
    Data e;
    AVL *lchild,*rchild;
    int bf;//balance factor平衡因子
}*Bit_avl;
void Right_rotate(Bit_avl *T);
void Left_rotate(Bit_avl *T);
void Right_balance(Bit_avl *T);
void Left_balance(Bit_avl *T);
void Creat_AVL_Tree(Bit_avl *T,Data x,int &taller)
{
    if(*T==NULL)
    {
        *T=(Bit_avl)malloc(sizeof(AVL));
        (*T)->e=x;
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=0;//产生的新子树的平衡因子为0
        taller=1;//产生新子树原树就会增高,就需要改变双亲结点以及更早的祖先结点的平衡因子,以及判断是否需要旋转
    }
    else
    {
        if(x==(*T)->e)
            return;
        if(x<(*T)->e)
        {
            Creat_AVL_Tree(&(*T)->lchild,x,taller);//寻找正确的插入位置
            if(taller)//判断是否需要旋转
            {
                switch((*T)->bf)
                {
                case 0://是0时产生的子树会使得平衡改变
                    (*T)->bf=1;
                    //taller=1;个人觉得这里不必进行赋1,taller本身不就是1吗
                    break;
                case 1://是1时新产生的子树说明该点就为最小不平衡子树,此时平衡因子已经失衡
                    Left_balance(T);
                    taller=0;//经过旋转后根据28原则,恢复局部的平衡,原先的整个树就可恢复平衡
                    break;
                case -1://说明原先已在此根节点处插入了右子树此时插入左子树平衡因子应从新置0
                    (*T)->bf=0;
                    taller=0;//这里同样不需要旋转,本身就是平衡的,只是使子树完全平衡了
                }
            }
        }
        else if(x>(*T)->e)
        {
            Creat_AVL_Tree(&(*T)->rchild,x,taller);
            if(taller)
            {
                switch((*T)->bf)
                {
                case 0:
                    (*T)->bf=-1;
                    //taller=1;
                    break;
                case 1:
                    (*T)->bf=0;
                    taller=0;
                    break;
                case -1:
                    Right_balance(T);
                    taller=0;
                }
            }
        }
    }
}
void Left_rotate(Bit_avl *T)
{
    AVL *lc;
    lc=(*T)->rchild;//要把右子树的左子树插入到双亲结点的右子树上,同时使根节点成为原先右子树的左子树
    (*T)->rchild=lc->lchild;
    lc->lchild=*T;
    *T=lc;
}
void Right_rotate(Bit_avl *T)
{
    Bit_avl rc;
    rc=(*T)->lchild;//要把左子树的右子树插入到双亲结点的左子树上,同时使根节点成为原先左子树的右子树
    (*T)->lchild=rc->rchild;
    rc->rchild=*T;
    *T=rc;
}
void Left_balance(Bit_avl *T)
{
    AVL *lc,*rc;
    lc=(*T)->lchild;
    switch(lc->bf)
    {
    case 1://说明是3个结点共线的时候进行一次单向有旋转即可恢复平衡
        lc->bf=(*T)->bf=0;//这里注意先后次序,一定是先改变平衡因子再去旋转,否则可能原先根节点处的平衡因子得不到修正
        Right_rotate(T);
        break;
    case -1://说明是LR型的
        rc=lc->rchild;
        switch(rc->bf)
        {
        case 1:
            lc->bf=0;//这里原先的左子树会获得完全的平衡
            (*T)->bf=-1;//最小不平衡结点点会向右偏
            break;
        case -1:
            lc->bf=1;//原先的左子树会向左偏
            (*T)->bf=0;//原先的最小不平衡结点会获得完全的平衡
            break;
        case 0://最小不平衡结点的左子树的右子树是叶子结点,则旋转后这三个结点都会获得完全的平衡
            lc->bf=(*T)->bf=0;
        }
        rc->bf=0;//这里rc最后都会变为这个局部子树的根节点而且会获得完全的平衡,没找到不完全平衡的情况
        Left_rotate(&(*T)->lchild);
        Right_rotate(T);
    }
}
void Right_balance(Bit_avl *T)
{
    AVL *rl,*lc;
    rl=(*T)->rchild;
    switch(rl->bf)
    {
    case -1:
        rl->bf=(*T)->bf=0;
        Left_rotate(T);
        break;
    case 1:
        lc=rl->lchild;
        switch(lc->bf)
        {
        case 0:
            (*T)->bf=rl->bf=0;
            break;
        case 1:
            (*T)->bf=0;
            rl->bf=-1;
            break;
        case -1:
            rl->bf=0;
            (*T)->bf=1;
        }
        lc->bf=0;
        Right_rotate(&(*T)->rchild);
        Left_rotate(T);
    }
}
void Inorder_traversal(Bit_avl T)
{
    if(T)
    {
        Inorder_traversal(T->lchild);
        printf("%d->",T->e);
        Inorder_traversal(T->rchild);
    }
}
void Tree_print(Bit_avl T,int floor)
{
    if(T)
    {
        Tree_print(T->rchild,floor+1);
        for(int i=1;i<=floor;i++)
            printf("  ");
            printf("%d\n",T->e);
        Tree_print(T->lchild,floor+1);
    }
}
/*void BSTree_creat_insert(Bit_avl *T,Data x)//非平衡二叉树课用于比较
{
    if(*T==NULL)
    {
        *T=(AVL *)malloc(sizeof(AVL));
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
}*/
#endif // AVL_OPERATE_H_INCLUDED

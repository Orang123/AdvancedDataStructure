#ifndef AVL_OPERATE_H_INCLUDED//��ȱ��ɾ������AVL����ƽ�����,�Լ���ϸ������
#define AVL_OPERATE_H_INCLUDED
#include<malloc.h>
typedef int Data;
typedef struct AVL
{
    Data e;
    AVL *lchild,*rchild;
    int bf;//balance factorƽ������
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
        (*T)->bf=0;//��������������ƽ������Ϊ0
        taller=1;//����������ԭ���ͻ�����,����Ҫ�ı�˫�׽���Լ���������Ƚ���ƽ������,�Լ��ж��Ƿ���Ҫ��ת
    }
    else
    {
        if(x==(*T)->e)
            return;
        if(x<(*T)->e)
        {
            Creat_AVL_Tree(&(*T)->lchild,x,taller);//Ѱ����ȷ�Ĳ���λ��
            if(taller)//�ж��Ƿ���Ҫ��ת
            {
                switch((*T)->bf)
                {
                case 0://��0ʱ������������ʹ��ƽ��ı�
                    (*T)->bf=1;
                    //taller=1;���˾������ﲻ�ؽ��и�1,taller��������1��
                    break;
                case 1://��1ʱ�²���������˵���õ��Ϊ��С��ƽ������,��ʱƽ�������Ѿ�ʧ��
                    Left_balance(T);
                    taller=0;//������ת�����28ԭ��,�ָ��ֲ���ƽ��,ԭ�ȵ��������Ϳɻָ�ƽ��
                    break;
                case -1://˵��ԭ�����ڴ˸��ڵ㴦��������������ʱ����������ƽ������Ӧ������0
                    (*T)->bf=0;
                    taller=0;//����ͬ������Ҫ��ת,�������ƽ���,ֻ��ʹ������ȫƽ����
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
    lc=(*T)->rchild;//Ҫ�������������������뵽˫�׽�����������,ͬʱʹ���ڵ��Ϊԭ����������������
    (*T)->rchild=lc->lchild;
    lc->lchild=*T;
    *T=lc;
}
void Right_rotate(Bit_avl *T)
{
    Bit_avl rc;
    rc=(*T)->lchild;//Ҫ�������������������뵽˫�׽�����������,ͬʱʹ���ڵ��Ϊԭ����������������
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
    case 1://˵����3����㹲�ߵ�ʱ�����һ�ε�������ת���ɻָ�ƽ��
        lc->bf=(*T)->bf=0;//����ע���Ⱥ����,һ�����ȸı�ƽ��������ȥ��ת,�������ԭ�ȸ��ڵ㴦��ƽ�����ӵò�������
        Right_rotate(T);
        break;
    case -1://˵����LR�͵�
        rc=lc->rchild;
        switch(rc->bf)
        {
        case 1:
            lc->bf=0;//����ԭ�ȵ�������������ȫ��ƽ��
            (*T)->bf=-1;//��С��ƽ����������ƫ
            break;
        case -1:
            lc->bf=1;//ԭ�ȵ�������������ƫ
            (*T)->bf=0;//ԭ�ȵ���С��ƽ���������ȫ��ƽ��
            break;
        case 0://��С��ƽ���������������������Ҷ�ӽ��,����ת����������㶼������ȫ��ƽ��
            lc->bf=(*T)->bf=0;
        }
        rc->bf=0;//����rc��󶼻��Ϊ����ֲ������ĸ��ڵ���һ�����ȫ��ƽ��,û�ҵ�����ȫƽ������
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
/*void BSTree_creat_insert(Bit_avl *T,Data x)//��ƽ������������ڱȽ�
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

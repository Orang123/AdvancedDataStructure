#include<stdio.h>//说明运行时不能做完加法后直接做乘法需要销毁后重新创建多项式再做乘法(因为做完加法后原多项式指针域已发生变化),但可以先做乘法再做加法
#include<stdlib.h>
typedef struct poly_link//多项式的结构声明
{
    int coef;//系数
    int expon;//指数
    poly_link *next;//下一个指针域
}*poly_node;
void Creat_polylink(poly_link *head)//多项式的创建
{
    poly_node *p=&head->next;//p是定义为指向指针类型的指针变量 ,注意头指针中的coef用来表示多项式的项数
    int result,coef,expon;
    while(1)
    {
        printf("请输入该项的系数和指数:");
        result=scanf("%d%d",&coef,&expon);
        if(result==EOF) break;
        *p=(poly_link *)malloc(sizeof(poly_link));
        (*p)->coef=coef,(*p)->expon=expon;
        head->coef++;
        p=&(*p)->next;//让p指向p的下一个指针域的地址
    }
    *p=NULL;
}
void adjust_polylink(poly_link *p)//把多项式按照指数从小到大依次链接 ,指数重复项合并
{
    poly_link *head=p,*node=p->next,*pt,*tmp1,*tmp2;
    bool adjust;//用来判断多项式指数是否为最大项
    head->coef=0;
    head->next=NULL;
    while(node)
    {
        pt=head;
        adjust=false;
        while(pt->next)
        {
            if(node->expon==pt->next->expon)//指数相等的项合并
            {
                pt->next->coef+=node->coef;
                tmp1=node;
                node=node->next;
                free(tmp1);//注意刚才合并的那个node已经没用了,为了避免memory leak, 选择在这里将其回收
                adjust=true;//这里将不必再执行将这一项链接到新多项式的末尾
                break;
            }
            else if(node->expon<pt->next->expon)//将指数较小的项放到前面
            {
                tmp1=pt->next;
                tmp2=node->next;
                pt->next=node;
                node->next=tmp1;
                node=tmp2;
                adjust=true;
                head->coef++;
                break;
            }
            pt=pt->next;
        }
        if(adjust==false)//将指数最大的项作为最后一项
        {
            pt->next=node;
            tmp1=node;
            node=node->next;
            tmp1->next=NULL;
            head->coef++;
        }
    }
}
poly_node polylink_add(poly_link *p,poly_link *pt)//两个多项式的合并
{
    poly_link *head=p;
    while(p->next)
        p=p->next;
    p->next=pt->next;
    free(pt);
    adjust_polylink(head);
    return head;
}
poly_link *polylink_multiply(poly_link *p,poly_link *pt)//两个多项式相乘
{
    poly_link *head=(poly_link *)malloc(sizeof(poly_link)),*tmp=pt;
    poly_node *node=&head->next;
    while(p)
    {
        while(pt)
        {
            *node=(poly_link *)malloc(sizeof(poly_link));
            (*node)->coef=p->coef*pt->coef;
            (*node)->expon=p->expon+pt->expon;
            node=&(*node)->next;
            pt=pt->next;
        }
        pt=tmp;
        p=p->next;
    }
    *node=NULL;
    adjust_polylink(head);//对新合成的多项式进行一遍整理
    return head;
}
void print(poly_link *p,int num)//进行多项式的输出
{
    printf("该多项式%d的项数为:%d\n",num,p->coef);
    printf("该多项式%d为:",num);
    p=p->next;
    printf("f(x)=%d*x^%d",p->coef,p->expon);
    while(p->next)
    {
        p=p->next;
        printf("+%d*x^%d",p->coef,p->expon);
    }
    putchar('\n');
}
void delete_polylink(poly_link *p)//销毁多项式
{
    poly_link *tmp;
    while(p)
    {
        tmp=p;
        p=p->next;
        free(tmp);
    }
}
int main()
{
    poly_link head1,head2,*head3;
    head1.coef=0,head2.coef=0;
    int order,k;
    while(1)
    {
        printf("请输入你想要进行的操作指令:");
        k=scanf("%d",&order);
        if(k==EOF) break;
        switch(order)
        {
        case 0:
            printf("创建多项式1:\n");
            Creat_polylink(&head1);
            printf("创建多项式2:\n");
            Creat_polylink(&head2);
            printf("所创建的多项式1和多项式2为:\n");
            printf("多项式1:\n");print(&head1,1);
            printf("多项式2:\n");print(&head2,2);break;
        case 1:
            printf("将多项式1和多项式2相加\n:");
            head3=polylink_add(&head1,&head2);
            printf("相加后的多项式:\n");
            print(head3,3);break;
        case 2:
            printf("将多项式1和多项式2相乘:\n");
            head3=polylink_multiply(head1.next,head2.next);
            print(head3,3);break;
        case 3:
            printf("将相乘所得到的的多项式已销毁.\n");
            delete_polylink(&head1);
            delete_polylink(&head2);
            delete_polylink(head3);break;//由于head3是新申请的空间所以也要销毁
        case 4:
        	printf("将相加所得到的多项式已销毁.\n");
        	delete_polylink(head3);//head1,head2中的个别项已在adjust的过程成free
        }
    }
    return 0;
}

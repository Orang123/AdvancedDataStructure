#include<stdio.h>//˵������ʱ��������ӷ���ֱ�����˷���Ҫ���ٺ����´�������ʽ�����˷�(��Ϊ����ӷ���ԭ����ʽָ�����ѷ����仯),�����������˷������ӷ�
#include<stdlib.h>
typedef struct poly_link//����ʽ�Ľṹ����
{
    int coef;//ϵ��
    int expon;//ָ��
    poly_link *next;//��һ��ָ����
}*poly_node;
void Creat_polylink(poly_link *head)//����ʽ�Ĵ���
{
    poly_node *p=&head->next;//p�Ƕ���Ϊָ��ָ�����͵�ָ����� ,ע��ͷָ���е�coef������ʾ����ʽ������
    int result,coef,expon;
    while(1)
    {
        printf("����������ϵ����ָ��:");
        result=scanf("%d%d",&coef,&expon);
        if(result==EOF) break;
        *p=(poly_link *)malloc(sizeof(poly_link));
        (*p)->coef=coef,(*p)->expon=expon;
        head->coef++;
        p=&(*p)->next;//��pָ��p����һ��ָ����ĵ�ַ
    }
    *p=NULL;
}
void adjust_polylink(poly_link *p)//�Ѷ���ʽ����ָ����С������������ ,ָ���ظ���ϲ�
{
    poly_link *head=p,*node=p->next,*pt,*tmp1,*tmp2;
    bool adjust;//�����ж϶���ʽָ���Ƿ�Ϊ�����
    head->coef=0;
    head->next=NULL;
    while(node)
    {
        pt=head;
        adjust=false;
        while(pt->next)
        {
            if(node->expon==pt->next->expon)//ָ����ȵ���ϲ�
            {
                pt->next->coef+=node->coef;
                tmp1=node;
                node=node->next;
                free(tmp1);//ע��ղźϲ����Ǹ�node�Ѿ�û����,Ϊ�˱���memory leak, ѡ�������ｫ�����
                adjust=true;//���ｫ������ִ�н���һ�����ӵ��¶���ʽ��ĩβ
                break;
            }
            else if(node->expon<pt->next->expon)//��ָ����С����ŵ�ǰ��
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
        if(adjust==false)//��ָ����������Ϊ���һ��
        {
            pt->next=node;
            tmp1=node;
            node=node->next;
            tmp1->next=NULL;
            head->coef++;
        }
    }
}
poly_node polylink_add(poly_link *p,poly_link *pt)//��������ʽ�ĺϲ�
{
    poly_link *head=p;
    while(p->next)
        p=p->next;
    p->next=pt->next;
    free(pt);
    adjust_polylink(head);
    return head;
}
poly_link *polylink_multiply(poly_link *p,poly_link *pt)//��������ʽ���
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
    adjust_polylink(head);//���ºϳɵĶ���ʽ����һ������
    return head;
}
void print(poly_link *p,int num)//���ж���ʽ�����
{
    printf("�ö���ʽ%d������Ϊ:%d\n",num,p->coef);
    printf("�ö���ʽ%dΪ:",num);
    p=p->next;
    printf("f(x)=%d*x^%d",p->coef,p->expon);
    while(p->next)
    {
        p=p->next;
        printf("+%d*x^%d",p->coef,p->expon);
    }
    putchar('\n');
}
void delete_polylink(poly_link *p)//���ٶ���ʽ
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
        printf("����������Ҫ���еĲ���ָ��:");
        k=scanf("%d",&order);
        if(k==EOF) break;
        switch(order)
        {
        case 0:
            printf("��������ʽ1:\n");
            Creat_polylink(&head1);
            printf("��������ʽ2:\n");
            Creat_polylink(&head2);
            printf("�������Ķ���ʽ1�Ͷ���ʽ2Ϊ:\n");
            printf("����ʽ1:\n");print(&head1,1);
            printf("����ʽ2:\n");print(&head2,2);break;
        case 1:
            printf("������ʽ1�Ͷ���ʽ2���\n:");
            head3=polylink_add(&head1,&head2);
            printf("��Ӻ�Ķ���ʽ:\n");
            print(head3,3);break;
        case 2:
            printf("������ʽ1�Ͷ���ʽ2���:\n");
            head3=polylink_multiply(head1.next,head2.next);
            print(head3,3);break;
        case 3:
            printf("��������õ��ĵĶ���ʽ������.\n");
            delete_polylink(&head1);
            delete_polylink(&head2);
            delete_polylink(head3);break;//����head3��������Ŀռ�����ҲҪ����
        case 4:
        	printf("��������õ��Ķ���ʽ������.\n");
        	delete_polylink(head3);//head1,head2�еĸ���������adjust�Ĺ��̳�free
        }
    }
    return 0;
}

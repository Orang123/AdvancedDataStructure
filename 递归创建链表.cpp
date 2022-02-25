#include<stdio.h>
#include<malloc.h>
typedef char Data;
typedef struct link
{
    Data e;
    link *next;
}node;
struct head_0
{
    int num;
    link *next;
};
int Creat_node(link **p,int num)
{
    Data x;
    scanf(" %c",&x);
    if(x=='@')
    {
        *p=NULL;
        return num-1;
    }
    else
    {
        //(*num)++;也可用指针进行自增操作相对简便些,这里只是为了训练自己的递归思维
        *p=(link *)malloc(sizeof(link));
        (*p)->e=x;
        num=Creat_node(&(*p)->next,num+1);
    }
    return num;
}
void print_node_Data(link *pt,int num)
{
    printf("The node 's num is %d.\n",num);
    printf("%c",pt->e);
    pt=pt->next;
    while(pt!=NULL)
    {
        printf("->%c",pt->e);
        pt=pt->next;
    }
}
void delete_node(link *p)
{
    link *temp;
    if(p!=NULL)
    {
        temp=p->next;
        free(p);
        delete_node(temp);
    }
    else
        return;
}
int main()
{
    link *head2=NULL;
    head_0 *head1=(head_0 *)malloc(sizeof(head_0));
    head1->next=head2;
    head1->num=0;
    head1->num=Creat_node(&head2,head1->num+1);
    print_node_Data(head2,head1->num);
    delete_node(head2);
    return 0;
}

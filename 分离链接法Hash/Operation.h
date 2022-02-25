#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#include<malloc.h>
#define tablesize 10
typedef int Data;
struct Listnode
{
    Data e;
    Listnode *next;
};
struct List
{
    int cursize;
    Listnode *Hashlist[tablesize];
};
void Init_list(List **p)
{
    *p=(List *)malloc(sizeof(List));
    (*p)->cursize=0;
    for(int i=0;i<tablesize;i++)
    {
        (*p)->Hashlist[i]=(Listnode *)malloc(sizeof(Listnode));
        (*p)->Hashlist[i]->e=0;
        (*p)->Hashlist[i]->next=NULL;
    }
}
Listnode *Search_node(List *p,int pos,Data key)
{
    Listnode *tmp=p->Hashlist[pos];
    while(tmp->next&&tmp->next->e!=key)
        tmp=tmp->next;
    return tmp;
}
void Insert_node(List *p,Data key)
{
    int pos=key%tablesize;
    Listnode *res=Search_node(p,pos,key);
    if(res->next==NULL)
    {
        Listnode *newnode=(Listnode *)malloc(sizeof(newnode));
        newnode->e=key;
        newnode->next=p->Hashlist[pos]->next;
        p->Hashlist[pos]->next=newnode;
        p->cursize++;
        p->Hashlist[pos]->e++;
    }
    else
        printf("This Hashlist already has had this key.\n");
}
void Delete_node(List *p,Data key)
{
    int pos=key%tablesize;
    Listnode *res=Search_node(p,pos,key);
    if(res->next)
    {
        Listnode *tmp=res->next;
        res->next=tmp->next;
        free(tmp);
        p->cursize--;
        p->Hashlist[pos]->e--;
    }
    else
        printf("This Hashlist doesn't have this node.\n");
}
void Output_Hashlist(List *p)
{
    printf("This Hashlist 's length is %d.\n",p->cursize);
    Listnode *tmp;
    for(int i=0;i<tablesize;i++)
    {
        tmp=p->Hashlist[i];
        if(tmp->e)
        {
            printf("邻接表第%d行的元素个数为%d.\n",i+1,tmp->e);
            tmp=tmp->next;
            while(tmp)
            {
                printf("%d ",tmp->e);
                tmp=tmp->next;
            }
            putchar('\n');
        }
        else
            printf("This line 's number is zero.\n");
    }
}
int Find(List *p,Data key,int &pos)
{
    pos=key%tablesize;
    Listnode *tmp=p->Hashlist[pos];
    int i;
    for(i=1;tmp->next&&tmp->next->e!=key;i++)
        tmp=tmp->next;
    return i;
}
#endif // OPERATION_H_INCLUDED

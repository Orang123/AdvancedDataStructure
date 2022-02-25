#ifndef OPERATION_H_INCLUDED//设置懒惰删除的目的是，某个元素被删除时还不影响之前插入的节点，标记为删除，在搜索某个节点时被当做占据该位置
#define OPERATION_H_INCLUDED
#define tablesize 19
#define R 17
typedef int Data;
enum flag {Empty,Legal,Deleted};
struct node
{
    Data e;
    flag df;
};
struct hashtable
{
    int cursize;
    node hashnode[tablesize];
};
void Init_table(hashtable *p)
{
    p->cursize=0;
    for(int i=0;i<tablesize;i++)
        p->hashnode[i].df=Empty;
}
int Search_node(hashtable *p,Data key,int pos)
{
    int res=R-key%R,tmp=pos;
    for(int i=1;p->hashnode[tmp].df!=Empty&&p->hashnode[tmp].e!=key;i++)//这里可能还是没有考虑到 Hash表填满了或那个循环链 都填满了元素的情况会陷入一种死循环
    {
        res*=i;
        tmp=(pos+res)%tablesize;
    }
    return tmp;
}
void Insert_node(hashtable *p,Data key)
{
    int pos=key%tablesize;
    int res=Search_node(p,key,pos);
    if(p->hashnode[res].df!=Legal)
    {
        p->hashnode[res].e=key;
        p->hashnode[res].df=Legal;
        p->cursize++;
    }
    else
        printf("This position which you insert is not legal.\n");
}
void Delete_node(hashtable *p,Data key)
{
    int pos=key%tablesize;
    int res=Search_node(p,key,pos);
    if(p->hashnode[res].df==Legal&&p->hashnode[res].e==key)
    {
        p->hashnode[res].df=Deleted;
        p->cursize--;
    }
    else
        printf("This hashtable doesn't have this key.\n");
}
void output_node(hashtable *p)
{
    printf("This hashtable 's key 's number is %d.\n",p->cursize);
    for(int i=0;i<tablesize;i++)
        if(p->hashnode[i].df==Legal)
           printf("%d ",p->hashnode[i].e);
    putchar('\n');
}
void Find(hashtable *p,Data key)
{
    int pos=key%tablesize;
    int res=Search_node(p,key,pos);
    if(p->hashnode[res].df==Legal)
        printf("This key 's position is %d.\n",res);
    else
        printf("This key already had been deleted.\n");

}
#endif // OPERATION_H_INCLUDED

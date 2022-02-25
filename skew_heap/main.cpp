#include<stdio.h>
#include"Operation.h"
int main()
{
    left_heap *T1=NULL,*T2=NULL;
    Data key;
    int k,floor=0;
    while(scanf("%d",&k)!=EOF)
    {
        switch(k)
        {
            case 1:scanf("%d",&key);
            T1=Insert_node(T1,key);break;
            case 2:
                T1=Delete_min(T1);break;
            case 3:
                Tree_print(T1,floor);break;
        }
    }
    while(scanf("%d",&k)!=EOF)
    {
        switch(k)
        {
            case 1:scanf("%d",&key);
            T2=Insert_node(T2,key);break;
            case 2:
                T2=Delete_min(T2);break;
            case 3:
                Tree_print(T2,floor);break;
        }
    }
    left_heap *T=merge1(T1,T2);
    Tree_print(T,floor);
    T=Delete_min(T);
    Tree_print(T,floor);
    return 0;
}

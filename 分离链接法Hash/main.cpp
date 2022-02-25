#include<stdio.h>
#include"Operation.h"
int main()
{
    List *p;
    Init_list(&p);
    Data key;
    int k,pos,x;
    while(scanf("%d",&k)!=EOF)
    {
        switch(k)
        {
            case 1:scanf("%d",&key);
            Insert_node(p,key);break;
            case 2:scanf("%d",&key);
            Delete_node(p,key);break;
            case 3:Output_Hashlist(p);break;
            case 4:scanf("%d",&key);
            x=Find(p,key,pos);printf("This key 's position is %d line %d position.\n",pos,x);break;
        }
    }
    return 0;
}

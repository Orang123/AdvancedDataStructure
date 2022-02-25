#include<stdio.h>
#include"Hash_operate.h"
int main()
{
    int *a,len,m,position;
    Hash *has=(Hash *)malloc(sizeof(Hash));
    while(scanf("%d%d",&len,&m)!=EOF)
    {
        a=(int *)malloc(sizeof(int)*len);
        for(int i=0; i<len; i++)
            scanf("%d",a+i);
        Creat_Hash2(has,len,a,m);
        int e;
        while(scanf("%d",&e)!=EOF)
        {
            position=search_Hash2(has,e);
            if(position!=-1)
                printf("The element 's position is %d.\n",position);
            else
                printf("No element.\n");
        }
        Display_Hash(has);
        Hash_ASL(has,m);
        while(scanf("%d",&e)!=EOF)
        {
        delete_Hash_element(has,e);
        Display_Hash(has);
        }
        while(scanf("%d",&e)!=EOF)
        {
        insert_Hash(has,e);
        Display_Hash(has);
        }
        free(a);
    }
    return 0;
}

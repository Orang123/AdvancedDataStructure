#include<stdio.h>
#include"Operation.h"
int main()
{
    hashtable p;
    Init_table(&p);
    Data key;
    int k;
    while(scanf("%d",&k)!=EOF)
    {
        switch(k)
        {
        case 1:scanf("%d",&key);
            Insert_node(&p,key);break;
        case 2:scanf("%d",&key);
        Delete_node(&p,key);break;
        case 3:output_node(&p);break;
        case 4:scanf("%d",&key);
        Find(&p,key);break;
        }
    }
    return 0;
}

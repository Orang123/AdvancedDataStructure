#include<stdio.h>
#include"Operation.h"
int main()
{
    Binqueue *T1,*T2,*T3;
    Init_Binqueue(&T1);
    Init_Binqueue(&T2);
    Init_Binqueue(&T3);
    T2->cursize=1;
    Data key;
    while(scanf("%d",&key)!=EOF)
    {
        Init_Binnode(&T2->Thetrees[0],key);
        Merge_queue(T1,T2);
    }
    Display_node(T1);
    while(scanf("%d",&key)!=EOF)
    {
        Init_Binnode(&T2->Thetrees[0],key);
        Merge_queue(T3,T2);
    }
    Display_node(T3);
    Merge_queue(T1,T3);
    Display_node(T1);
    int min_data;
    min_data=Delete_min(T1);
    printf("The min_data is %d.\n",min_data);
    Display_node(T1);
    Delete_Binqueue(T1);
    return 0;
}

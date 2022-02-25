#include<cstdio>
#include"lib.h"
int main(){
    Heap heap;
    heap.heap_len=0;
    Data e;
    while(scanf("%d",&e)!=EOF){
        insert_data(e,&heap);
    }
    print_heap_node(&heap);
    int val;
   while(1){
        val=delete_top_node(&heap);
        if(val!=-1)
            printf("test %d \n",val);
        else
            break;
    }
    print_heap_node(&heap);
    return 0;
}

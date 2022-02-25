#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#define heap_size 100
typedef int Data;

struct Heap{
    Data a[heap_size];
    int heap_len;
};

void insert_data(Data e,Heap *heap){
    if(heap->heap_len==0){
        heap->a[1]=e;
        heap->heap_len++;
    }
    else{
        heap->heap_len++;
        int i;
        for(i=heap->heap_len;i>=2&&heap->a[i/2]>e;i/=2){
            heap->a[i]=heap->a[i/2];
        }
        heap->a[i]=e;
    }
}

int delete_top_node(Heap *heap){
    if(heap->heap_len!=0){
        int tmp=heap->a[heap->heap_len];
        int val=heap->a[1];
        heap->heap_len--;
        int child=1;
        for(int i=2;i<=heap->heap_len;i*=2){
            if(i!=heap->heap_len&&heap->a[i]>heap->a[i+1])//i!=heap->heap_len因为此时已是堆的最大数量,没有i+1了
                i++;
            if(tmp<heap->a[i])
                break;
            heap->a[child]=heap->a[i];
            child=i;
        }
        heap->a[child]=tmp;
        return val;
    }
    return -1;
}

void print_heap_node(Heap *heap){
    for(int i=1;i<=heap->heap_len;i++)
        printf("%d ",heap->a[i]);
    putchar('\n');
}

#endif // LIB_H_INCLUDED

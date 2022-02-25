#include<stdio.h>
#include<malloc.h>
#include"sort_gather.h"
#include"Improve_Q_sort.h"
int main()
{
    int n,*a=NULL,*b=NULL,*c;
    while(scanf("%d",&n)!=EOF)
    {
        c=(int *)malloc(sizeof(int)*400);
        a=(int *)malloc(sizeof(int)*(n+1));
        b=(int *)malloc(sizeof(int)*n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",a+i);
            b[i-1]=a[i];
        }
        merge_sort(a,0,n-1);
        printf("The merge_sort's result is:");
        output_element2(a,n);
        for(int i=0;i<80;i++)
        {
            switch(i/10)
            {
                case 0:c[i]=0;break;
                case 1:c[i]=1+i;break;
                case 2:c[i]=2+i*4;break;
                case 3:c[i]=3+i*2;break;
                case 4:c[i]=4+i*6;break;
                case 5:c[i]=5+i*3;break;
                case 6:c[i]=6+i*8;break;
                case 7:c[i]=7+i*1;break;
            }
        }
        for(int i=80;i<=99;i++)
            c[i]=26+i;
        output_element2(c,100);
        Shell_sort(c,100);
        output_element2(c,100);
        Q_sort(c,0,99);
        printf("The quick_sort 's result:");
        output_element2(c,99);
        free(c);
        Shell_sort(b,n);
        printf("The Shell_sort 's result:");
        output_element2(b,n);
        Insert_sort(b,n);
        printf("The insert_sort 's result:");
        output_element2(b,n);
        free(b);
        printf("The Heap_sort 's result:");
        Heap_sort(a,n);
        output_element1(a,n);
        free(a);
    }
    return 0;
}

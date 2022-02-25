#ifndef SORT_GATHER_H_INCLUDED
#define SORT_GATHER_H_INCLUDED
#include<bits/stdc++.h>
using namespace std;
void bubble_sort(int *a,int len){
    for(int i=0;i<len;i++)
        for(int j=0;j<len-1-i;j++)
            if(a[j]<a[j+1])
                swap(a[j],a[j+1]);
}
void exchange_sort(int *a,int len){
    for(int i=0;i<len-1;i++){
        int k=i;
        for(int j=k+1;j<len;j++)
            if(a[k]>a[j])
                k=j;
        if(k!=i)
            swap(a[k],a[i]);
    }
}
void Adjust_Heap(int *a,int s,int len)//调整剩余元素为一个大顶堆
{
    int p=a[s];
    for(int i=2*s;i<=len;i*=2)
    {
        if(i<len&&a[i]<a[i+1])//取根节点的左孩子和右孩子中较大的作为根节点
            i++;
        if(a[i]<p)//如果根节点比这一节点的关键字大则,结束调整,这里并没有删除堆顶元素，只是将原先还入堆顶元素得到堆尾元素放置在合适的位置
            break;
        a[s]=a[i];//依次将整个堆向上推进
        s=i;
    }
    a[s]=p;//将根节点放入合适的位置
}
void Creat_Heap(int *a,int len)
{
    for(int i=len/2;i>=1;i--)//对完全二叉树进行一次初始化,使得每个根节点均大于其左孩子和右孩子
        Adjust_Heap(a,i,len);
}
void Heap_sort(int *a,int len)
{
    Creat_Heap(a,len);
    int temp;
    for(int i=len;i>=1;i--)
    {
        temp=a[1];//每次得出最大元素后将其放入完全二叉树的后面
        a[1]=a[i];
        a[i]=temp;
        Adjust_Heap(a,1,i-1);//只对前i-1个元素进行大顶堆的调整方便找出最大元素
    }
}
void output_element1(int *a,int n)
{
    printf("%d",a[n]);
    for(int i=n-1;i>=1;i--)
        printf("->%d",a[i]);
    putchar('\n');
}
void output_element2(int *b,int n)
{
    printf("%d",b[0]);
    for(int i=1;i<n;i++)
        printf("->%d",b[i]);
    putchar('\n');
}
void Insert_sort(int *b,int len)
{
    int temp;
    for(int i=1,j;i<len;i++)
        if(b[i]<b[i-1])
        {
            j=i;
            temp=b[j];
            while(j>0&&temp<b[j-1])
            {
                b[j]=b[j-1];
                j--;
            }
            b[j]=temp;
        }
}
void Shell_sort(int *b,int len)
{
    int temp;
    for(int gap=len/2;gap>=1;gap/=2)//设置步长,取决于数据规模,初始为数据量的一半,步长为1时最后一次调整,但此时序列已经大体上趋于标准序列了
        for(int i=gap,j;i<len;i++)
            if(b[i]>b[i-gap])
            {
                j=i;
                temp=b[j];
                while(j-gap>-1&&temp>b[j-gap])
                {
                    b[j]=b[j-gap];//如果比temp小的都会前移
                    j-=gap;
                }
                b[j]=temp;//将temp放入合适的位置
            }
}
int separate_array(int *a,int low,int high)
{
    int pivot=a[low];//将表的第一个元素作为枢轴元素
    while(low<high)
    {
        while(low<high&&a[high]>=pivot)//这里最好把等于号去掉,有利于产生两个等大的数组
            high--;
        if(low<high)//把比枢轴小的元素交换到枢轴的左边
        {
            a[low]=a[high];
            low++;
        }
        while(low<high&&a[low]<=pivot)
            low++;
        if(low<high)//把比枢轴大的元素交换到枢轴右边
        {
            a[high]=a[low];
            high--;
        }
        a[low]=pivot;//最后将枢轴元素再归位
    }
    return low;
}
void quick_sort(int *a,int low,int high)
{
    int pivot;
    if(low<high)//直到划分到只剩下一个元素的时候,不用划分就为标准序列
    {
        pivot=separate_array(a,low,high);//以枢轴为中心,使左边的元素都小于轴枢元素,右边元素都大于枢轴元素
        quick_sort(a,low,pivot-1);//将左边到枢轴的序列再重新递归划分
        quick_sort(a,pivot+1,high);//将枢轴到右边的序列再重新递归划分
    }
}
int temp[100];
void merge_array(int *a,int low,int mid,int high)
{
    int i=low,j=mid+1,k=0;
    while(i<=mid&&j<=high)
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];//将较小的值放进临时数组tmp中
        else
            temp[k++]=a[j++];
    }
    while(i<=mid)//将剩余的元素放进临时数组temp中,这里可以有另一种办法直接将较大的放进原数组
        temp[k++]=a[i++];
    while(j<=high)
        temp[k++]=a[j++];
    for(i=low,k=0;i<=high;i++,k++)//将临时数组temp中已排好序的序列copy进原数组
        a[i]=temp[k];
}
void merge_sort(int *a,int low,int high)//还有小甲鱼的非递归算法,和零基础书上耗费高空间,节约时间的办法
{
    int mid;
    if(low<high)//分治只剩一个元素时结束
    {
        mid=(low+high)/2;
        merge_sort(a,low,mid);//先分治分割
        merge_sort(a,mid+1,high);
        merge_array(a,low,mid,high);//分治完进行归并
    }
}
#endif // SORT_GATHER_H_INCLUDED

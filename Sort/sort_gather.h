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
void Adjust_Heap(int *a,int s,int len)//����ʣ��Ԫ��Ϊһ���󶥶�
{
    int p=a[s];
    for(int i=2*s;i<=len;i*=2)
    {
        if(i<len&&a[i]<a[i+1])//ȡ���ڵ�����Ӻ��Һ����нϴ����Ϊ���ڵ�
            i++;
        if(a[i]<p)//������ڵ����һ�ڵ�Ĺؼ��ִ���,��������,���ﲢû��ɾ���Ѷ�Ԫ�أ�ֻ�ǽ�ԭ�Ȼ���Ѷ�Ԫ�صõ���βԪ�ط����ں��ʵ�λ��
            break;
        a[s]=a[i];//���ν������������ƽ�
        s=i;
    }
    a[s]=p;//�����ڵ������ʵ�λ��
}
void Creat_Heap(int *a,int len)
{
    for(int i=len/2;i>=1;i--)//����ȫ����������һ�γ�ʼ��,ʹ��ÿ�����ڵ�����������Ӻ��Һ���
        Adjust_Heap(a,i,len);
}
void Heap_sort(int *a,int len)
{
    Creat_Heap(a,len);
    int temp;
    for(int i=len;i>=1;i--)
    {
        temp=a[1];//ÿ�εó����Ԫ�غ��������ȫ�������ĺ���
        a[1]=a[i];
        a[i]=temp;
        Adjust_Heap(a,1,i-1);//ֻ��ǰi-1��Ԫ�ؽ��д󶥶ѵĵ��������ҳ����Ԫ��
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
    for(int gap=len/2;gap>=1;gap/=2)//���ò���,ȡ�������ݹ�ģ,��ʼΪ��������һ��,����Ϊ1ʱ���һ�ε���,����ʱ�����Ѿ����������ڱ�׼������
        for(int i=gap,j;i<len;i++)
            if(b[i]>b[i-gap])
            {
                j=i;
                temp=b[j];
                while(j-gap>-1&&temp>b[j-gap])
                {
                    b[j]=b[j-gap];//�����tempС�Ķ���ǰ��
                    j-=gap;
                }
                b[j]=temp;//��temp������ʵ�λ��
            }
}
int separate_array(int *a,int low,int high)
{
    int pivot=a[low];//����ĵ�һ��Ԫ����Ϊ����Ԫ��
    while(low<high)
    {
        while(low<high&&a[high]>=pivot)//������ðѵ��ں�ȥ��,�����ڲ��������ȴ������
            high--;
        if(low<high)//�ѱ�����С��Ԫ�ؽ�������������
        {
            a[low]=a[high];
            low++;
        }
        while(low<high&&a[low]<=pivot)
            low++;
        if(low<high)//�ѱ�������Ԫ�ؽ����������ұ�
        {
            a[high]=a[low];
            high--;
        }
        a[low]=pivot;//�������Ԫ���ٹ�λ
    }
    return low;
}
void quick_sort(int *a,int low,int high)
{
    int pivot;
    if(low<high)//ֱ�����ֵ�ֻʣ��һ��Ԫ�ص�ʱ��,���û��־�Ϊ��׼����
    {
        pivot=separate_array(a,low,high);//������Ϊ����,ʹ��ߵ�Ԫ�ض�С������Ԫ��,�ұ�Ԫ�ض���������Ԫ��
        quick_sort(a,low,pivot-1);//����ߵ���������������µݹ黮��
        quick_sort(a,pivot+1,high);//�����ᵽ�ұߵ����������µݹ黮��
    }
}
int temp[100];
void merge_array(int *a,int low,int mid,int high)
{
    int i=low,j=mid+1,k=0;
    while(i<=mid&&j<=high)
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];//����С��ֵ�Ž���ʱ����tmp��
        else
            temp[k++]=a[j++];
    }
    while(i<=mid)//��ʣ���Ԫ�طŽ���ʱ����temp��,�����������һ�ְ취ֱ�ӽ��ϴ�ķŽ�ԭ����
        temp[k++]=a[i++];
    while(j<=high)
        temp[k++]=a[j++];
    for(i=low,k=0;i<=high;i++,k++)//����ʱ����temp�����ź��������copy��ԭ����
        a[i]=temp[k];
}
void merge_sort(int *a,int low,int high)//����С����ķǵݹ��㷨,����������ϺķѸ߿ռ�,��Լʱ��İ취
{
    int mid;
    if(low<high)//����ֻʣһ��Ԫ��ʱ����
    {
        mid=(low+high)/2;
        merge_sort(a,low,mid);//�ȷ��ηָ�
        merge_sort(a,mid+1,high);
        merge_array(a,low,mid,high);//��������й鲢
    }
}
#endif // SORT_GATHER_H_INCLUDED

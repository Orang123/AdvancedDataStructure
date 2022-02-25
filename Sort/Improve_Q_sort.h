#ifndef IMPROVE_Q_SORT_H_INCLUDED
#define IMPROVE_Q_SORT_H_INCLUDED
void swap_element(int *a,int i,int j)
{
    int temp;
    temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}
int separate_seqlist(int *a,int low,int high,int *left_len,int *right_len)
{
    int mid=low+(high-low)/2;//当时一直出错可能是这里错了
    /*三数取中法*/
    if(a[mid]>a[high])
        swap_element(a,mid,high);
    if(a[low]>a[high])
        swap_element(a,low,high);
    if(a[low]<a[mid])
        swap_element(a,low,mid);
    int start=low,end=high;
    int pivot=a[low],left=low,right=high;
    while(low<high)
    {
        while(low<high&&a[high]>=pivot)
        {
            if(a[high]==pivot)
            {
                swap_element(a,high,right);
                (*right_len)++;
                right--;
            }
            high--;
        }
        if(low<high)
        {
            a[low]=a[high];
            low++;
        }
        while(low<high&&a[low]<=pivot)
        {
            if(a[low]==pivot)
            {
                swap_element(a,low,left);
                (*left_len)++;
                left++;
            }
            low++;
        }
        if(low<high)
        {
            a[high]=a[low];
            high--;
        }
        a[low]=pivot;
    }
    int i,j;
    i=start,j=low-1;
    while(i<left&&a[j]!=pivot)
    {
        swap_element(a,i,j);
        i++;
        j--;
    }
    i=low+1,j=end;
    while(j>right&&a[i]!=pivot)
    {
        swap_element(a,i,j);
        i++;
        j--;
    }
    return low;
}
void Q_sort(int *a,int low,int high)
{
    int pivot,left_len,right_len;
    if(low<high)
    {
        if(high-low>=7)
        {
            while(low<high)
            {
                left_len=0,right_len=0;
                pivot=separate_seqlist(a,low,high,&left_len,&right_len);
                Q_sort(a,low,pivot-1-left_len);
                //Q_sort(a,pivot+1+right_len,high);
                low=pivot+1+right_len;
            }
        }
        else
            Insert_sort(a+low,high-low+1);
    }
}


#endif // IMPROVE_Q_SORT_H_INCLUDED

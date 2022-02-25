#ifndef HASH_OPERATE_H_INCLUDED//线性探测再散列容易产生二次聚集,但只要哈希表不满,就一定能找到一个不冲突的哈希地址,而二次探测再散列和伪随机探测再散列则不一定。
#define HASH_OPERATE_H_INCLUDED//二次探测存在的问题也比较多,比如如果是负数取余发生数组下标越界,还有正负数替换所多产生的冲突
#include<stdlib.h>//而随机数序列本身又存在着周期的问题,要想周期较大得考虑本身所设立的随机种子还有问题的规模,一般只要比32768远小很多应该还是蛮合理的,如果数据量大于32768那么就会产生无法消除的冲突
typedef int Datatype;
struct Data
{
    Datatype key;
    int conflict;//查找次数,冲突=查找次数-1；
};
struct Hash
{
    Data *addr;
    int tablesize;//哈希表长
    int cursize;//实际元素个数
};//其实可以一个元素一个元素的插入
void Creat_Hash1(Hash *has,int n,int *a,int m)//线性探测再散列
{
    has->addr=(Data *)malloc(sizeof(Data)*m);
    int n_len=n;
    for(int i=0;i<m;i++)
    {
        has->addr[i].key=-1;
        has->addr[i].conflict=0;
    }
    int d,d0;
    for(int i=0;i<n;i++)
    {
        d0=d=a[i]%m;
        if(has->addr[d].key==-1)
        {
            has->addr[d].key=a[i];
            has->addr[d].conflict=1;
        }
        else
        {
            int sum=1;
            do
            {
                d=(d+1)%m;
                sum++;
                if(d==d0)
                {
                    printf("The Hash 's length is not enough.\n");
                    n_len--;
                    goto loop;
                }
            }
            while(has->addr[d].key!=-1);
            has->addr[d].key=a[i];
            has->addr[d].conflict=sum;
        }
    }
loop:
    has->cursize=n_len;
    has->tablesize=m;
}
void Creat_Hash2(Hash *has,int n,int *a,int m)//随机序列再散列
{
    int seed,n_len=0;
    scanf("%d",&seed);
    srand(seed);
    has->addr=(Data *)malloc(sizeof(Data)*(m+1));//这里多分配一个地址是为了查找那种没有的元素准备的
    for(int i=0;i<m+1;i++)
    {
        has->addr[i].key=-1;
        has->addr[i].conflict=0;
    }
    int d,d0;
    for(int i=0;i<n;i++)
    {
        if(n_len==m)
        {
            printf("The Hash 's space is full.\n");
            break;
        }
        d0=d=a[i]%m;
        if(has->addr[d].key==-1)
        {
            has->addr[d].key=a[i];
            has->addr[d].conflict=1;
            n_len++;
        }
        else
        {
            int sum=1,k;
            do
            {
                k=rand()%m;
                d=(d0+k)%m;
                /*if(d==d0&&)//这里其实由于数据量很小所以不必考虑随机数发生器产生的随机数无法找到合理的地址，真正当n,m很大时会有产生不到的空闲地址的情况
                {
                    printf("The random does not produce reasonable position.\n");这里其实是进行了二次取余了，而且也不能用d=d0因为k的随机结果会出现相同的两个数但却不见得是一个周期的完成,即rand内部并不一定是一个周期
                    n_len--;
                    flag=false;
                    break;
                }真要实现的话可以手写了个rand可以用指针传递每次产生的next值,与第一次设置的种子对比判断是否一个周期的完成,如果一个周期的确过早完成可以再重新设立随机种子,不过只能当n,m数据量很大时才能看到那个周期提早结束的时候*/
                sum++;
            }
            while(has->addr[d].key!=-1);
            has->addr[d].key=a[i];
            has->addr[d].conflict=sum;
            n_len++;
        }
    }
    has->cursize=n_len;
    has->tablesize=m;
}
void insert_Hash(Hash *has,Datatype e)
{
    int m,d,d0;
    m=has->tablesize;
    d0=d=e%m;
    if(has->addr[d].key==-1)
    {
        has->addr[d].key=e;
        has->addr[d].conflict=1;
        has->cursize++;
    }
    else
    {
        int sum=1;
        bool flag=true;
            do
            {
                d=(d+1)%m;
                sum++;
                if(d==d0)
                {
                    printf("The Hash 's length is not enough.\n");
                    flag=false;
                    break;
                }
            }
            while(has->addr[d].key!=-1);
            if(flag)
            {
                has->addr[d].key=e;
                has->addr[d].conflict=sum;
                has->cursize++;
            }
    }
}
int search_Hash2(Hash *has,Datatype e)
{
    int d,d0,m=has->tablesize,k;
    d0=d=e%m;
    while(has->addr[d].key!=-1)
    {
        if(has->addr[d].key==e)
            return d;
        else
        {
            k=rand()%m;
            d=(d0+k)%(m+1);
        }
    }
    return -1;
}
int search_Hash1(Hash *has,Datatype e)
{
    int d,d0,m=has->tablesize;
    d0=d=e%m;
    while(has->addr[d].key!=-1)
    {
        if(has->addr[d].key==e)
            return d;
        else
            d=(d+1)%m;
        if(d==d0)
            return -1;
    }
    return -1;
}
void Hash_ASL(Hash *has,int m)
{
    float average=0;
    for(int i=0;i<m;i++)
        average+=has->addr[i].conflict;
    average/=has->cursize;
    printf("The hash's table 's average length is %.1f.\n",average);
}
void Display_Hash(Hash *has)
{
    int m=has->tablesize;
    int n=has->cursize;
    printf("The Hash 's space is %d,the element 's number is %d.\n",m,n);
    for(int i=0;i<m;i++)
        if(has->addr[i].key!=-1)
              printf("The element 's address is %d,and its key is %d,its conflict is %d.\n",i,has->addr[i].key,has->addr[i].conflict);
}
void delete_Hash_element(Hash *has,Datatype e)
{
    int position;
    position=search_Hash2(has,e);
    if(position!=-1)
    {
        has->addr[position].key=-1;
        has->addr[position].conflict=0;
        has->cursize--;
    }
    else
        printf("No element.\n");
}
#endif // HASH_OPERATE_H_INCLUDED

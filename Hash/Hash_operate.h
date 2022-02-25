#ifndef HASH_OPERATE_H_INCLUDED//����̽����ɢ�����ײ������ξۼ�,��ֻҪ��ϣ����,��һ�����ҵ�һ������ͻ�Ĺ�ϣ��ַ,������̽����ɢ�к�α���̽����ɢ����һ����
#define HASH_OPERATE_H_INCLUDED//����̽����ڵ�����Ҳ�Ƚ϶�,��������Ǹ���ȡ�෢�������±�Խ��,�����������滻��������ĳ�ͻ
#include<stdlib.h>//����������б����ִ��������ڵ�����,Ҫ�����ڽϴ�ÿ��Ǳ�����������������ӻ�������Ĺ�ģ,һ��ֻҪ��32768ԶС�ܶ�Ӧ�û����������,�������������32768��ô�ͻ�����޷������ĳ�ͻ
typedef int Datatype;
struct Data
{
    Datatype key;
    int conflict;//���Ҵ���,��ͻ=���Ҵ���-1��
};
struct Hash
{
    Data *addr;
    int tablesize;//��ϣ��
    int cursize;//ʵ��Ԫ�ظ���
};//��ʵ����һ��Ԫ��һ��Ԫ�صĲ���
void Creat_Hash1(Hash *has,int n,int *a,int m)//����̽����ɢ��
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
void Creat_Hash2(Hash *has,int n,int *a,int m)//���������ɢ��
{
    int seed,n_len=0;
    scanf("%d",&seed);
    srand(seed);
    has->addr=(Data *)malloc(sizeof(Data)*(m+1));//��������һ����ַ��Ϊ�˲�������û�е�Ԫ��׼����
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
                /*if(d==d0&&)//������ʵ������������С���Բ��ؿ��������������������������޷��ҵ�����ĵ�ַ��������n,m�ܴ�ʱ���в��������Ŀ��е�ַ�����
                {
                    printf("The random does not produce reasonable position.\n");������ʵ�ǽ����˶���ȡ���ˣ�����Ҳ������d=d0��Ϊk���������������ͬ����������ȴ��������һ�����ڵ����,��rand�ڲ�����һ����һ������
                    n_len--;
                    flag=false;
                    break;
                }��Ҫʵ�ֵĻ�������д�˸�rand������ָ�봫��ÿ�β�����nextֵ,���һ�����õ����ӶԱ��ж��Ƿ�һ�����ڵ����,���һ�����ڵ�ȷ������ɿ��������������������,����ֻ�ܵ�n,m�������ܴ�ʱ���ܿ����Ǹ��������������ʱ��*/
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

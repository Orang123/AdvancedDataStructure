#include<stdio.h>
#include"BSToperator.h"
int main()
{
    BST *T=NULL;
    Data x;
    int floor=0;
    while(scanf("%d",&x)!=EOF)
        BSTree_insert(&T,x);
        //BSTree_creat_insert(&T,x);
    Inorder_traversal(T);
    putchar('\n');
    Tree_print(T,floor);
    putchar('\n');
    scanf("%d",&x);
    search_delete_node(&T,x);//����û�в�ȡֱ�ӷ���Ҫɾ�����ĵ�ַ����ʱָ��,��Ҫ����Ϊ�������㴫�ݸ�delete��ֻ���޸���ʱָ���ֵ(�ڶ���ָ�봫����),û�������޸Ľ���ָ��
    Inorder_traversal(T);
    putchar('\n');
    return 0;
}

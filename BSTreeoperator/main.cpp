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
    search_delete_node(&T,x);//这里没有采取直接返回要删除结点的地址给临时指针,主要是因为这样就算传递给delete你只会修改临时指针的值(在二级指针传递下),没法真正修改结点的指向
    Inorder_traversal(T);
    putchar('\n');
    return 0;
}

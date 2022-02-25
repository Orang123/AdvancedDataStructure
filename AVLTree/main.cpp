#include<stdio.h>
#include"AVL_operate.h"
int main()
{
    AVL *T=NULL;
    Data e;
    int taller,floor=0;
    while(scanf("%d",&e)!=EOF)
    {
        Creat_AVL_Tree(&T,e,taller);
        //BSTree_creat_insert(&T,e);
        printf("Inorder_traversal:");
        Inorder_traversal(T);
        putchar('\n');
        printf("Tree_print:\n");
        Tree_print(T,floor);
        putchar('\n');
    }
    printf("      \n");
    Tree_print(T,floor);
    return 0;
}

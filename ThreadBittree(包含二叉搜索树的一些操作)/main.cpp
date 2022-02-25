#include<stdio.h>
#include"LinkBittree.h"
int main()
{
    int floor=1,count;
    //Data x;
    Bit_tree *T=NULL;
    Bit_tree *T0=NULL;
    int result;
    printf("The Bit_tree T will be created.\n");
    Creat_Bit_tree(&T);
    printf("The Bit_tree T0 will be created.\n");
    Creat_Bit_tree(&T0);
    printf("Whether is Bit_tree T similar to Bit_tree T0 ?\n");
    result=judge_similar_Bit_tree(T,T0);
    if(result)
        printf("The result is Yes.\n");
    else
        printf("The result is No.\n");
    printf("Tree_print:\n");
    Tree_print(T,floor);
    putchar('\n');
    printf("Level_print:\n");
    Level_print(T);
    putchar('\n');
    printf("Preorder_traversal 's result:\n");
    Preorder_traversal1(T,floor);
    printf("Not recursion Preorder_traversal 's result:\n");
    Preorder_traversal2(T);
    putchar('\n');
    printf("Inorder_traversal 's result:\n");
    Inorder_traversal1(T,floor);
    putchar('\n');
    printf("Not recursion Inorder_traversal 's result:\n");
    Inorder_traversal2(T);
    putchar('\n');
    printf("postorder_traversal 's result:\n");
    postorder_traversal1(T,floor);
    putchar('\n');
    printf("Not recursion postorder_traversal 's result:\n");
    postorder_traversal2(T);
    putchar('\n');
    count=leaf_num(T);
    printf("Leaf 's number is %d\n",count);
    count=Not_leaf_num(T);
    printf("No leaf 's number is %d\n",count);
    count=Tree_deep(T);
    printf("Tree 's deep is %d\n",count);
    Bit_tree *top=NULL;
    Inorder_Threading(T,&top);
    Bit_tree *temp=NULL;
    printf("Inorder_Traverse 's result:\n");
    //scanf(" %c",&x);
    Inorder_Traverse_Thread(top);
    //printf("%p\n",temp);
    temp=Insearch_pre(T->lchild);
    printf("%c\n",temp->e);
    temp=Insearch_post(T->rchild);
    printf("%c\n",temp->e);
    delete_Thread_Bit_tree(top);//这里二叉树线索化后,由于首尾相接,所以free的时候可能会把同一个内存单元释放2次,这里已经将删除操作改为按照线索化顺序删除结点
    free(top);
    return 0;
}

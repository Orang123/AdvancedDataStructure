#include<stdio.h>
#include<malloc.h>
#include"Operation.h"
int main()
{
    CB_tree *T;
    Creat_CB_tree(&T);
    int floor;
    printf("The CB_tree 's deep is:");
    floor=CB_tree_Deep(T);
    printf("%d\n",floor);
    printf("The Pretraverse_CB_tree 's result:\n");
    Pretraverse_CB_tree(T,Display_CB_tree);
    putchar('\n');
    printf("The Posttraverse_CB_tree 's result:\n");
    Posttraverse_CB_tree(T,Display_CB_tree);
    putchar('\n');
    Delete_CB_tree(T);
    return 0;
}

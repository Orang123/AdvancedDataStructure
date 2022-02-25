#include<stdio.h>
#include<malloc.h>
typedef char Data;
struct stack
{
    Data operator_;
    stack *next;
};
struct stack_
{
    float operand;
    stack_ *next;
};
void push_stack(stack *top,Data e)
{
    stack *temp=(stack *)malloc(sizeof(stack));
    temp->next=top->next;
    top->next=temp;
    temp->operator_=e;
}
void push_stack_(stack_ *top,int e)
{
    stack_ *temp=(stack_ *)malloc(sizeof(stack_));
    temp->next=top->next;
    top->next=temp;
    temp->operand=e;
}
void out_stack(stack *top)
{
    if(top->next==NULL)
        printf("The stack is empty.\n");
    else
    {
        stack *temp=top->next;
        top->next=temp->next;
        free(temp);
    }
}
void out_stack_(stack_ *top)
{
    if(top->next==NULL)
        printf("The stack is empty.\n");
    else
    {
        stack_ *temp=top->next;
        top->next=temp->next;
        free(temp);
    }
}
int get_topstack(stack *top,Data *e)
{
    if(top->next==NULL) return 0;
    *e=top->next->operator_;
}
void convert_expression(stack *p,Data *initial,Data *result)
{
    int j=0;
    Data e;
    for(int i=0;initial[i]!='\0';i++)
    {
        switch(initial[i])
        {
        case '(':
            push_stack(p,initial[i]);
            break;
        case ')':
            while(get_topstack(p,&e)&&e!='(')
            {
                result[j++]=e;
                out_stack(p);
            }
            out_stack(p);
            break;
        case '+':
        case '-':
            while(get_topstack(p,&e)&&e!='(')
            {
                result[j++]=e;
                out_stack(p);
            }
            push_stack(p,initial[i]);
            break;
        case '*':
        case '/':
            while(get_topstack(p,&e)&&(e=='*'||e=='/'))
            {
                out_stack(p);
                result[j++]=e;
            }
            push_stack(p,initial[i]);
            break;
        case ' ':
            break;
        default:
            while(initial[i]>='0'&&initial[i]<='9')
                result[j++]=initial[i++];
            result[j++]=' ';
            i--;
        }
    }
    while(p->next)
    {
        get_topstack(p,&e);
        result[j++]=e;
        out_stack(p);
    }
    result[j]='\0';
}
void compute_expression(Data *express)
{
    stack_ top,*p;
    top.next=NULL;
    float x1,x2,temp;
    for(int i=0;express[i]!='\0';i++)
    {
        if(express[i]>='0'&&express[i]<='9')
        {
            temp=0;
            while(express[i]!=' ')
                temp=temp*10+express[i++]-'0';
            push_stack_(&top,temp);
        }
        else
        {
            switch(express[i])
            {//不能在switch内case外的地方运算,反正不起作用
            case '+':
                p=top.next;
                x1=p->operand;
                x2=p->next->operand;
                out_stack_(&top);
                out_stack_(&top);
                push_stack_(&top,x1+x2);
                break;
            case '-':
                p=top.next;
                x1=p->operand;
                x2=p->next->operand;
                out_stack_(&top);
                out_stack_(&top);
                push_stack_(&top,x2-x1);
                break;
            case '*':
                p=top.next;
                x1=p->operand;
                x2=p->next->operand;
                out_stack_(&top);
                out_stack_(&top);
                push_stack_(&top,x2*x1);
                break;
            case '/':
                p=top.next;
                x1=p->operand;
                x2=p->next->operand;
                out_stack_(&top);
                out_stack_(&top);
                push_stack_(&top,x2/x1);
                break;
            }
        }
    }
    printf("The postfix expression 's result is:%f",top.next->operand);
    out_stack_(&top);
}
int main()
{
    stack opstack;
    opstack.next=NULL;
    Data initial[50],result[50];//这里其实也可以以链表的形式出现
    printf("Please input nifix expression which you want to compute:");
    scanf("%s",initial);
    convert_expression(&opstack,initial,result);
    printf("The postfix expression is ");
    puts(result);
    compute_expression(result);
    return 0;
}

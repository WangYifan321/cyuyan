#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int n;
    char a;
    char b;
    char c;
}ElementType;
typedef struct node{
    ElementType data[1000];
    int top;
}*stack;
stack create(){
    stack s= (stack)malloc(sizeof(struct node));
    s->top=-1;
    return s;
}
int isEmpty(stack s){
    if(s->top==-1){
        return 1;
    }else{
        return 0;
    }
}
void push(stack s,ElementType x){
    s->data[++(s->top)]=x;

}
ElementType pop(stack s){
    return (s->data[(s->top)--]);
}
void hannuo(int pan){
    ElementType temp,topush;
    stack s = create();
    temp.a='A';
    temp.b='B';
    temp.c='C';
    temp.n=pan;
    push(s,temp);
    while(isEmpty(s)!=1){
       temp=pop(s);
       if(temp.n==1){
           printf("%c->%c\n",temp.a,temp.c);

       }else{
           topush.n=temp.n-1;
           topush.a=temp.b;
           topush.b=temp.a;
           topush.c=temp.c;
           push(s,topush);
           topush.n=1;
           topush.a=temp.a;
           topush.b=temp.b;
           topush.c=temp.c;
           push(s,topush);
           topush.n=temp.n-1;
           topush.a=temp.a;
           topush.b=temp.c;
           topush.c=temp.b;
           push(s,topush);
       }

    }

}
int main(){
    int x;
    if(scanf("%d",&x)){};
    hannuo(x);
    return 0;
}


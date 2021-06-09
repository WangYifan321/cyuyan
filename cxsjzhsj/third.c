#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct	Node
{
    int	data;
    struct Node *next;
};

void Insert (struct Node *l, int x);
void Destory (struct Node *l);
void Print (struct Node *l);
struct Node * Back(struct Node* l);
struct Node * NewNode()
{
     struct Node *p;
     p = (struct Node *) malloc (sizeof (struct Node));
     if (p == NULL) { 
        printf ("Error : out of memory\n");
        exit (-1);
     }
     return p;
}

int main ()
{
    struct Node *la = NewNode();//正整数的链表
    struct Node *lb = NewNode();//负整数的链表

    la->next = NULL;
    lb->next = NULL;
    int	x;
    printf("请输入数字，以0结束,以空格或回车间隔");
    scanf ("%d", &x);
    while(x!=0){
       if(x>0){
         Insert(la, x);
       }else{
         Insert(lb, x);
       }
       scanf ("%d", &x);
    }
    Print(la);
    printf("逆置为：");
    Print(Back(la));
    Print(lb);
    printf("逆置为：");
    Print(Back(lb));

    Destory(la);
    Destory(lb);
    return 0;
}
void Insert (struct Node *l, int x)
{
    struct Node *q= NewNode ();
    q->data = x;
    struct Node *p = l;
    while (p->next && x > p->next ->data)
        p = p->next;
    q->next = p ->next ;
    p->next = q;
}
void Destory (struct Node *l)
{
    while (l)
    {
        struct Node *q = l->next;
        free (l); 
        l = q;
    }
}
void Print (struct Node *l)
{
    l = l ->next;
    if (l)  
    {
        printf ("%d", l->data);
        l = l->next;
    }
    while (l)
    {
        printf ("->%d", l->data);
        l = l->next;
    }
    printf ("\n");
}
struct Node * Back(struct Node* l){
    struct Node *p;
    struct Node *q;
    p=l->next;
    l->next=NULL;
    while(p){
        q=p;
        p=p->next;
        q->next=l->next;
        l->next=q;
    }
    return l;

}
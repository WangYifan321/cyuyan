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
struct Node* Merge(struct Node *l1,struct Node *l2);
struct Node * NewNode()
{
     struct Node *p;
     p = (struct Node *) malloc (sizeof (struct Node));
     if (p == NULL) { 
        printf ("Error : out of memory\n");
        exit (-1); 
     }
     p->data=0;
     p->next=NULL;
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
    
    while(scanf ("%d", &x)!=EOF){
       if(x>0){
         Insert(la, x);
       }else{
         Insert(lb, x);
       }
    }
    Print(la);
    Print(lb);
    Print(Merge(lb,la));
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
struct Node * Merge (struct Node *l1,struct Node *l2){//负，正
    struct Node *p;
    p=l1->next;
    while(1){
        if(p == NULL){
         return l2;
        }else{
            if(p->next == NULL){
                 p->next=l2->next;
                 break;
            }
        }
        p=p->next;
    }

    return l1;
}
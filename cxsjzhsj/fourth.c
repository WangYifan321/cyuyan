#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
struct	Node
{
    int	data;
    struct Node *next;
};

void Insert (struct Node *l, int x);
void Destory (struct Node *l);
void Print (struct Node *l);
void Split(struct Node* l);
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
    struct Node *la = NewNode();

    la->next = NULL;
    int	x;
    printf("请输入数字，以0结束,以空格或回车间隔");
    scanf ("%d", &x);
    while(x!=0){
       Insert(la,x);
       scanf ("%d", &x);
    }
    //Print(la);
    Split(la);
    Destory(la);
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
void Split(struct Node* l)
{
    struct Node* p=l;
    struct Node* ra=l;
    
    struct Node* q = NewNode();
    q->next=NULL;
    struct Node* ql = q;
    p=l->next;
    l->next=NULL;
    while(p){
            if(abs(p->data) %2 == 0){
             ql->next=p;
             ql=ql->next;
            }else{
             l->next=p;
             l=l->next;
            }
        p=p->next;
    }
    l->next=NULL;
    ql->next=NULL;
    Print(ra);
    Print(q);
}

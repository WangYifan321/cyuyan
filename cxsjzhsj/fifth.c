#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct	Node
{
    int	data;
    struct Node *next;
};
struct Node * Append (struct Node* p,int x);
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
     int m,n,x;
     struct Node* p=NULL;
     printf("请输入总人数、报数值：\n");
     scanf("%d %d",&m,&n);
     for(int i=1;i<=m;i++){
         p=Append(p,i);
     }
     //
     struct Node* t = p->next;
     int y=n%m;//取余操作，减少循环的次数
     if(y==0){
         y=10;
     }
     y--;
     int yy=y;//暂存y值
     while(p!=p->next){
         
         while(y--){//指针后移
             t=t->next;
             p=p->next;
         }
         y=yy;
         printf("%4d ",t->data);
         p->next=t->next;//去掉该节点
         free(t);
         t=p->next;
     }
     printf("%4d",p->data);
     free(p);
     return 0;
     
}
struct Node* Append(struct Node* p,int x){
    if(p==NULL){
     struct Node *q = NewNode();
     q->data=x;
     q->next=q;
     p=q;
    }else{
        struct Node *q = NewNode();
        q->data=x;
        q->next=p->next;
        p->next=q;
        p=q;
    }
    return p;
}
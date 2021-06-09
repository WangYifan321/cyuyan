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
     int m,n,k;
     struct Node* p=NULL;//第一次的单向循环链表
     struct Node* p1=NULL;
     printf("请输入M、N、K：\n");
     scanf("%d %d %d",&m,&n,&k);
     for(int i=1;i<=m;i++){
         p=Append(p,i);
     }
     //
     struct Node* t = p->next;
     int y=n%m;//取余操作，减少循环的次数
     y--;
     int yy=y;//暂存y值
     while(p!=p->next){
         
         while(y--){//指针后移
             t=t->next;
             p=p->next;
         }
         y=yy;
         p1=Append(p1,t->data);
         p->next=t->next;//去掉该节点
         free(t);
         t=p->next;
     }
     p1=Append(p1,t->data);
     free(p);
     //第二次约瑟夫环开始
     struct Node* t1 = p1->next;
     int y1=k%m;//取余操作，减少循环的次数
     y1--;
     int yy1=y1;//暂存y值
     while(p1!=p1->next){
         
         while(y1--){//指针后移
             t1=t1->next;
             p1=p1->next;
         }
         y1=yy1;
         printf("%d ",t1->data);
         p1->next=t1->next;//去掉该节点
         free(t1);
         t1=p1->next;
     }
         printf("%d",t1->data);
     free(p1);
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
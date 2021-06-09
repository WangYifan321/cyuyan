#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct	Node
{
    int	data;
    struct Node *next;
};
struct Node* circle(struct Node* p,int n,int m);
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
     int m,n[10000],i=0;
     struct Node* p=NULL;//第一次的单向循环链表
     printf("请输入M和报数密码，报数密码以0结束：\n");
     scanf("%d",&m);
     scanf("%d",&n[0]);
     while(n[i]!=0){
         i++;
         scanf("%d",&n[i]);
     }//输入密码
     for(int j=1;j<=m;j++){
         p=Append(p,j);
     }
     //
     for(int j=0;j<=i-2;j++){
         p=circle(p,n[j],m);
     }
     //第二次约瑟夫环开始
     struct Node* p1=p;
     struct Node* t1 = p1->next;
     int y1=n[i-1]%m;//取余操作，减少循环的次数
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
struct Node* circle(struct Node* p,int n,int m){//除最后一个密码之外，前几个密码的约瑟夫环操作在此执行
     struct Node* p1=NULL;
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
     return p1;
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
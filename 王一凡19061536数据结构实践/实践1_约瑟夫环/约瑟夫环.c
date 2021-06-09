#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
struct node{
    int password,num;
    struct node *next,*prior;
};
typedef struct node *Node;
//初始化双向循环链表
Node Init(){
    Node head;
    head = (Node)malloc(sizeof(struct node));
    head->next=head;
    head->prior=head;
    return head;
}
//向链表中存入数据
void createlist(Node L,int n){
    Node s,r;
    r=L;
    int i,x;
    scanf("%d",&x);//输入第一个密码
    r->password=x;
    r->num=1;
    for(i=2;i<=n;i++){
        scanf("%d",&x);//输入每个人的密码
        s=(Node)malloc(sizeof(struct node));
        s->password=x;//依次输入每个人的密码，并且放到链表中
        s->num=i;
        s->prior=r;
        s->next=r->next;
        r->next->prior=s;
        r->next=s;
        r=s;
    }
}
//循环链表的输出，元素出列
void printflist(Node L,int t){
    Node p;
    p=L;
    int m,i,k=0,sum;
    printf("请输入初始密码：");
    scanf("%d",&m);//m为初始密码
    printf("出列顺序为：");
    while(p->next!=p){
       sum=t-k; //sum为剩余的人数
       if(m>sum)
       m=m % sum; //减少循环的次数
       //判断链表的寻找方向，提高查找的效率
       if(m<=sum/2){
         for(i=1;i<m;i++){
             p=p->next;
         }
         printf("%d ",p->num);//输出数据
         m=p->password;//更新报数值
         p->prior->next=p->next;//从链表中删除
         p->next->prior=p->prior;
         L=p->next;
         free(p);
         p=L;
       }else{
         m=sum-m+1;//从右往左开始查找
         for(i=1;i<=m;i++){
             p=p->prior;

         }
         printf("%d ",p->num);
         m=p->password;
         p->prior->next=p->next;
         p->next->prior=p->prior;
         L=p->next;
         free(p);
         p=L;
       }
       k++;
    }
    printf("%d",p->num);
    printf("\n");
}
int main(){
    Node L;
    L=Init();
    int x,m;
    printf("请输入人数：\n");
    scanf("%d",&x);
    printf("请输入每个人的密码：\n");
    createlist(L,x);
    printflist(L,x);
    Sleep(1000);
    return 0;

}
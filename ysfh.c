
#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
int date,num;                    //记录密码和序号
struct Node *next,*prior;  //前继指针和后续指针
}Node;
 
//双向链表初始化
Node *Inslist()
{
Node *head;
head=(Node *)malloc(sizeof(Node));
head->next=head;
head->prior=head;
return head;
}
 
//录入数据
void createlist(Node *L,int n)
{
Node *s,*r;
int i,x;
r=L;
scanf("%d",&x);           //输入密码
r->date=x;
r->num=1;
for(i=2;i<=n;i++){
        scanf("%d",&x);   //录入每个人的密码
        s=(Node *)malloc(sizeof(Node));
        s->date=x;
        s->num=i;           //初始化每个人的序号
        s->prior = r;        //插入新的结点
        s->next = r->next;
        r->next->prior= s;
        r->next= s;
        r=s;
}
}
 
//双向循环链表的输出
void printflist(Node *L,int t)
{
Node *p;
p=L;
int m,i,sum,k=0;
printf("输入报数值m：");
scanf("%d",&m);
while(p->next!=p){
            sum=t-k;                       //sum为剩余人数
            while(m-sum>0) 
            m=m-sum;
            if(m<=sum/2){             //判断链表寻找方向，提高查找效率
            for(i=1;i<m;i++){
                p=p->next;
            }
            printf("%d ",p->num);
            m=p->date;
            p->prior->next=p->next;
            p->next->prior=p->prior;
            L=p->next;
            free(p);
            p=L;
    }
    else{
            m=sum-m+1;
            for(i=1;i<=m;i++){
                p=p->prior;
            }
            printf("%d ",p->num);
            m=p->date;
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
int main(void)
{
Node *L;
int x,m;
L=Inslist();
printf("输入几个数:\n");
scanf("%d",&x);
printf("输入数据\n");
createlist(L,x);
printf("输出数据\n");
printflist(L,x);
system("pause");
return 0;
}
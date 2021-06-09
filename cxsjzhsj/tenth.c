#include<stdio.h>
#include<stdlib.h>
//栈---->顺序存储结构
struct node{
    int b[2000];
    int top;
};
typedef struct node *stack;
stack init(){
    stack s;
    s=(stack)malloc(sizeof(struct node));
    s->top=-1;
    return s;
}
void push(stack s,int c){
    s->top++;
    s->b[s->top]=c;
}
int pop(stack s){
    int i = s->b[s->top];
    s->top--;
    return i;
}
//队列---->顺序存储结构
struct node2{
    int b[2000];
    int front;
    int rear;
};
typedef struct node2 *queue;
queue init2(){
    queue q;
    q=(queue)malloc(sizeof(struct node));
    q->front=0;
    q->rear=-1;
    return q;
}
void in(queue q,int c){
    q->rear++;
    q->b[q->rear]=c;
}
int out(queue q){
    int i = q->b[q->front];
    q->front++;
    return i;
}
//队列------>链式存储结构
typedef struct QNode{
	int data;
	struct QNode *next;
}QNode, *QueueNode;

typedef struct{
	QueueNode front; //队头指针 
	QueueNode rear; //队尾指针 
}LinkQueue;
//当front==rear时队列为空
LinkQueue* initQueue()
{
    LinkQueue *Q = (LinkQueue*)malloc(sizeof(LinkQueue));
	Q->front = Q->rear = (QueueNode)malloc(sizeof(QNode));
	Q->front->next = NULL;
	return Q;
	
}

//进队
void enQueue(LinkQueue *Q, int e)
{
	QueueNode p = (QueueNode)malloc(sizeof(QNode));
	if(!p){
        p = (QueueNode)malloc(sizeof(QNode));
    }
    p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}
//出队
int deQueue(LinkQueue *Q)
{
 
	QueueNode p;
	p = Q->front->next;
	int a = p->data;
	Q->front->next = p->next;
	return a;
}
//栈 -------->链式存储结构

typedef struct lineStack{
    int data;
    struct lineStack * next;
}lineStack;
lineStack* push2(lineStack * stack,int a){
    lineStack * line=(lineStack*)malloc(sizeof(lineStack));
    line->data=a;
    line->next=stack;
    stack=line;
    return stack;
}
lineStack*  pop2(lineStack * stack){
        lineStack * p=stack;
        stack=stack->next;
        printf("%d ",p->data);
        return stack;
    

}

int main(){
    stack s1=init();
    queue q = init2();
    LinkQueue *Q = initQueue();
    lineStack* stack = NULL;
    int x;
    printf("请输入正、负数，以0结束：");
    scanf("%d",&x);
    printf("顺序存储结构输出：\n");
    while(x!=0){
        if(x>0){
          push(s1,x);
          stack=push2(stack,x);
        }else{
          in(q,x);
          enQueue(Q,x);
        }
        scanf("%d",&x);
    }
    while(s1->top!=-1){
      printf("%d ",pop(s1));
      }
      printf("\n");
    if(q->rear>0){
    while(q->front!=q->rear){
        printf("%d ",out(q));

    }
    printf("%d\n",q->b[q->front]);
    }
    printf("----------------------------------\n");
    printf("链式存储结构输出：\n"); 
    QueueNode qq=   Q->front->next;
    while(Q->front->next!=NULL){
        printf("%d ",deQueue(Q));
    }
    printf("\n");
    while(stack!=NULL){
        stack=pop2(stack);
    }
    return 0;
}
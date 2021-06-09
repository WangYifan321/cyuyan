#include <stdio.h>
#include <malloc.h>

struct	Node
{
    int	data;
    struct Node *next;
};

//将元素插入有序单链表中，插入后仍然有序
void Insert (struct Node *la, int x);
//销毁单链表
void Destory (struct Node *la);
//打印单链表
void Print (struct Node *la);
//动态分配一个结点，返回结点指针
//分配失败时，简化程序，退出运行
struct Node *NewNode ()
{
     struct Node *p;
     p = (struct Node *) malloc (sizeof (struct Node));
     if (p == NULL) { //分配失败
        printf ("Error : out of memory\n");
        exit (-1); //简化程序，退出运行
     }
     return p;
}

int main ()
{
    //建立带头节点的单链表
    struct Node *la = NewNode ();
    la->next = NULL;

    int	x;
    printf ("请输入若干个需要插入的正整数，非正整数代表输入结束:\n");
    scanf ("%d", &x);
    while (x >0)
    {
        //将元素插入有序单链表中，插入后仍然有序
        Insert (la, x);
        scanf ("%d", &x);
    }
    //打印单链表
    Print (la);
    //销毁单链表，避免内存泄漏
    Destory (la);
    return 0;
}
//将元素插入有序单链表中，插入后仍然有序
void Insert (struct Node *la, int x)
{
    //申请结点
    struct Node *q= NewNode ();
    q->data = x;
    //查找合适插入位置
    struct Node *p = la;
    while (p->next && x > p->next ->data)
        p = p->next; //往后移一位置
    //将结点插入p所指结点后
    q->next = p ->next ;
    p->next = q;
}
//销毁单链表
void Destory (struct Node *la)
{
    while (la)
    {
        struct Node *q = la->next;
        free (la); //释放指针所指结点
        la = q;
    }
}
//打印单链表
void Print (struct Node *la)
{
    //头结点无数据
    la = la ->next;
    if (la)  //数据比-〉多一个
    {
        printf ("%d", la->data);
        la = la->next;
    }
    while (la)
    {
        printf ("->%d", la->data);
        la = la->next;
    }
    printf ("\n");
}

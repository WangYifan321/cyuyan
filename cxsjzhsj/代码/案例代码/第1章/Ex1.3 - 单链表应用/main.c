#include <stdio.h>
#include <malloc.h>

struct	Node
{
    int	data;
    struct Node *next;
};

//��Ԫ�ز������������У��������Ȼ����
void Insert (struct Node *la, int x);
//���ٵ�����
void Destory (struct Node *la);
//��ӡ������
void Print (struct Node *la);
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node *NewNode ()
{
     struct Node *p;
     p = (struct Node *) malloc (sizeof (struct Node));
     if (p == NULL) { //����ʧ��
        printf ("Error : out of memory\n");
        exit (-1); //�򻯳����˳�����
     }
     return p;
}

int main ()
{
    //������ͷ�ڵ�ĵ�����
    struct Node *la = NewNode ();
    la->next = NULL;

    int	x;
    printf ("���������ɸ���Ҫ��������������������������������:\n");
    scanf ("%d", &x);
    while (x >0)
    {
        //��Ԫ�ز������������У��������Ȼ����
        Insert (la, x);
        scanf ("%d", &x);
    }
    //��ӡ������
    Print (la);
    //���ٵ����������ڴ�й©
    Destory (la);
    return 0;
}
//��Ԫ�ز������������У��������Ȼ����
void Insert (struct Node *la, int x)
{
    //������
    struct Node *q= NewNode ();
    q->data = x;
    //���Һ��ʲ���λ��
    struct Node *p = la;
    while (p->next && x > p->next ->data)
        p = p->next; //������һλ��
    //��������p��ָ����
    q->next = p ->next ;
    p->next = q;
}
//���ٵ�����
void Destory (struct Node *la)
{
    while (la)
    {
        struct Node *q = la->next;
        free (la); //�ͷ�ָ����ָ���
        la = q;
    }
}
//��ӡ������
void Print (struct Node *la)
{
    //ͷ���������
    la = la ->next;
    if (la)  //���ݱ�-����һ��
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

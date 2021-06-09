#include <stdio.h>
#include "SeqList.h"

//ͨ��������������SeqList�Ļ���������ӡ���Ա�
void Print (struct SeqList list)
{
    printf ("(");
    Position pos = BeginPosition(list);
    if (pos != EndPosition(list)) {
        printf ("%d", GetElem (list, pos));
        pos = NextPosition(list, pos);
    }
    while (pos != EndPosition(list)) {
        printf (",%d", GetElem (list, pos));
        pos = NextPosition(list, pos);
    }
    printf (")\n");
}

int main()
{
    int i;
    struct SeqList  list = Create (1);       //����һ�������Ա�
    Print (list);  //��ӡ���Ա�
    for (i = 1; i <=5; ++i)//β��ѭ������i
        InsertBefore (&list, EndPosition(list), i);
    Print (list);
    Position pos = LocateElem(list, 3); //����Ԫ��3
    if (pos != EndPosition(list))
        Delete (&list, pos); //���ҵ�Ԫ��ʱ��ɾ��Ԫ��
    InsertBefore (&list, BeginPosition(list), 8); //ͷ������Ԫ��8
    Print (list);
    Destroy (&list); //�������Ա������ڴ�й©
    return 0;
}

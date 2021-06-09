#include <stdio.h>
#include "List.h"

//通过抽象数据类型List的基本操作打印线性表
void Print (struct List list)
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
    struct List  list = Create ();       //创建一个空线性表
    Print (list);  //打印线性表
    for (i = 1; i <=5; ++i)//尾部循环插入i
        InsertBefore (&list, EndPosition(list), i);
    Print (list);
    Position pos = LocateElem(list, 3); //查找元素3
    if (pos != EndPosition(list))
        Delete (&list, pos); //查找到元素时，删除元素
    InsertBefore (&list, BeginPosition(list), 8); //头部插入元素8
    Print (list);
    Destroy (&list); //销毁线性表，避免内存泄漏
    return 0;
}

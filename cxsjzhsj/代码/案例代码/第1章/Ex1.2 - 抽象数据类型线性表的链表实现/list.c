#include <stdlib.h>
#include <assert.h>
#include "List.h"

//1. 创建空线性表
//空表管理的单链表只有一个头结点，失败时首尾指针为NULL
struct List Create ()
{
    struct List list;
    //申请一个结点
    list.pHead = list.pTail = (struct Node *)malloc (sizeof (struct Node));
    if (list.pHead != NULL)
        list.pHead->next = NULL; //后续无结点
    return list;
}
//2. 线性表清空。
//释放链表中除头结点外所有结点
void Clear (struct List *pList)
{
    struct Node *p = pList->pHead->next; //从头结点后结点开始删除
    while (p != NULL) {     //直到最后
        struct Node *q = p; //记住要释放结点
        p = p->next;        //准备释放下一个
        free (q);           //释放结点，释放后不可再访问结点
    }
    pList->pHead->next = NULL; //头结点后已无结点
    pList->pTail = pList->pHead;
}
//3. 销毁一个线性表，不再使用，释放所有结点。
//传入链首指针变量的地址，销毁单链表
void Destroy (struct List *pList)
{
    Clear (pList);                        //单链表清空
    free (pList->pHead);                  //释放最后剩余的头结点
    pList->pHead = pList->pTail = NULL;   //将线性表中指针变量置空
}
//4. 根据已有线性表，复制一个内容相同的新线性表
//传入原线性表，复制原线性表中链表作为新线性表的链表，
//返回复制后新线性表，失败时返回线性表的头指针为NULL，
struct List Copy (struct List srcList)
{
    struct List destList;
    destList = Create (); //创建带头结点的空单链表
    if (destList.pHead == NULL)
        return destList;  //创建失败时直接返回
    struct Node  *p;
    p = srcList.pHead->next; //跳过原链表头结点
    while (p != NULL) {//循环处理原链表
        struct Node *s;
        s = (struct Node *)malloc (sizeof (struct Node));//分配新结点
        if (s == NULL) {
            Destroy (&destList); //申请失败时销毁线性表，避免内存泄漏
            return destList;
        }
        s->data = p->data; //复制元素
        destList.pTail->next = s; //挂在新链表最后
        s->next = NULL; //后面无结点
        destList.pTail = s;       //最后一个结点已变化
        p = p->next;    //准备复制下个结点
    }
    return destList; //返回复制完的线性表
}
//5. 线性表判空。
//判断线性表是否为空表，若是则返回1，否则返回0
int IsEmpty (struct List list)
{
    return (list.pHead->next == NULL); //头结点后无结点
}
//6. 线性表求长度。
//返回线性表中数据元素的个数
int Length (struct List list)
{
    int iCount = 0;
    struct Node *p = list.pHead->next; //从头结点后结点开始计数
    while (p != NULL) {     //直到最后
        ++iCount;
        p = p->next;        //临时变量移至下一结点
    }
    return iCount;
}
//7. 获取起始位置。
//返回线性表中代表第一个元素的位置，空表返回EndPosition (L)
Position BeginPosition (struct List list)
{
    return list.pHead;
}
//8. 获取结束位置。
//返回代表线性表结束的位置
Position  EndPosition (struct List list)
{
    return list.pTail;
}
//9. 迭代下一位置。
//返回线性表中p有效位置的下个位置，主要用于循环遍历线性表
Position NextPosition (struct List list, Position  pos)
{
    return pos->next;
}
//10. 获取元素位置。
//返回线性表代表第i个元素所在位置，1≤i≤n（设线性表的表长为n）
Position LocatePosition (struct List list, int i)
{
    Position  pos = list.pHead; //从头结点开始
    while (--i> 0 && pos->next != NULL) {//计数完成或直到结束位置
        pos = pos->next;        //移至下一结点
    }
    return pos;
}
//11. 定位元素位置。
//根据数据元素e查找它在线性表中出现的位置，若存在，则返回它的有效位置；
//否则返回EndPosition (L)
Position LocateElem (struct List list, DataElem e)
{
    Position  pos = list.pHead; //从头结点开始
    while (pos->next != NULL && pos->next->data != e) {
        pos = pos->next;        //移至下一结点
    }
    return pos; //返回元素所在结点的前一个结点指针
}
//12. 获取元素。
//返回线性表L中pos有效位置的数据元素
DataElem GetElem (struct List list, Position  pos)
{
    assert (pos != EndPosition (list)); //断言，包含头文件assert.h
    return pos->next->data;
}
//13. 获取元素。
//将线性表中pos有效位置的数据元素设置为e
void SetElem (struct List list, Position  pos, DataElem e)
{
    assert (pos != EndPosition (list)); //断言，包含头文件assert.h
    pos->next->data = e;
}
//14. 插入元素。
//在线性表的pos位置前插入一新的数据元素，
//pos为EndPosition (L)时添加在尾部，线性表长度加1
//成功时返回1，失败时返回0
int InsertBefore (struct List *pList, Position  pos, DataElem e)
{
    struct Node *s = (struct Node *)malloc (sizeof (struct Node));//分配新结点
    if (s == NULL)
        return 0;
    s->data = e;
    s->next = pos->next; //插入在pos所指结点后
    pos->next = s;
    if (pList->pTail == pos)
        pList->pTail = s; //插入在线性表最后时，调整尾结点指针
    return 1;
}
//15. 删除元素。
//删除线性表中pos有效位置所在数据元素，线性表的表长减1
void Delete (struct List *pList, Position  pos)
{
    assert (pos != EndPosition (*pList)); //断言，包含头文件assert.h
    struct Node *s = pos->next; //待删除结点
    pos->next = s->next;        //链表中删除结点
    free (s);                 //释放结点
    if (pList->pTail == s)
        pList->pTail = pos; //删除线性表最后一个结点时，调整尾结点指针
}

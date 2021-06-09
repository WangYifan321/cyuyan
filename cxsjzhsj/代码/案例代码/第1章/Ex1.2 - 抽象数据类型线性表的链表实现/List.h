#ifndef __LSIT_H_INCLUDED_
#define __LSIT_H_INCLUDED_
typedef  int DataElem;    //假设元素类型为整形

//链表结点类型
struct Node {
    DataElem  data;
    struct Node *next;
};

//线性表类型
struct List {
    struct Node *pHead;
    struct Node *pTail;
};
typedef  struct Node *  Position;    //线性表中位置类型

//1. 创建空线性表
//空表管理的单链表只有一个头结点，失败时首尾指针为NULL
struct List Create ();
//2. 线性表清空。
//释放链表中除头结点外所有结点
void Clear (struct List *pList);
//3. 销毁一个线性表，不再使用，释放所有结点。
//传入链首指针变量的地址，销毁单链表
void Destroy (struct List *pList);
//4. 根据已有线性表，复制一个内容相同的新线性表
//传入原线性表，复制原线性表中链表作为新线性表的链表，
//返回复制后新线性表，失败时返回线性表的头指针为NULL，
struct List Copy (struct List srcList);
//5. 线性表判空。
//判断线性表是否为空表，若是则返回1，否则返回0
int IsEmpty (struct List list);
//6. 线性表求长度。
//返回线性表中数据元素的个数
int Length (struct List list);
//7. 获取起始位置。
//返回线性表中代表第一个元素的位置，空表返回EndPosition (L)
Position BeginPosition (struct List list);
//8. 获取结束位置。
//返回代表线性表结束的位置
Position  EndPosition (struct List list);
//9. 迭代下一位置。
//返回线性表中p有效位置的下个位置，主要用于循环遍历线性表
Position NextPosition (struct List list, Position  pos);
//10. 获取元素位置。
//返回线性表代表第i个元素所在位置，1≤i≤n（设线性表的表长为n）
Position LocatePosition (struct List list, int i);
//11. 定位元素位置。
//根据数据元素e查找它在线性表中出现的位置，若存在，则返回它的有效位置；
//否则返回EndPosition (L)
Position LocateElem (struct List list, DataElem e);
//12. 获取元素。
//返回线性表L中pos有效位置的数据元素
DataElem GetElem (struct List list, Position  pos);
//13. 获取元素。
//将线性表中pos有效位置的数据元素设置为e
void SetElem (struct List list, Position  pos, DataElem e);
//14. 插入元素。
//在线性表的pos位置前插入一新的数据元素，
//pos为EndPosition (L)时添加在尾部，线性表长度加1
//成功时返回1，失败时返回0
int InsertBefore (struct List *pList, Position  pos, DataElem e);
//15. 删除元素。
//删除线性表中pos有效位置所在数据元素，线性表的表长减1
void Delete (struct List *pList, Position  pos);
#endif // __LSIT_H_INCLUDED_

#ifndef __SEQLIST_H_INCLUDED_
#define __SEQLIST_H_INCLUDED_
typedef  int DataElem;    //假设元素类型为整形

//线性表类型
struct SeqList {
    DataElem *pDatas;   //存放元素表的缓冲区指针
    int       iLength;  //线性表长度
    int       iSize;    //缓冲区大小
};
typedef  DataElem *  Position;    //线性表中位置类型

//1. 创建空线性表
//建立一个最多可存放iSize个元素的线性表，建立时为空表，失败时缓冲区指针为NULL
struct SeqList Create (int iSize);
//2. 线性表清空。
//元素个数置为0
void Clear (struct SeqList *pSeqList);
//3. 销毁一个线性表，不再使用，释放缓冲区。
void Destroy (struct SeqList *pSeqList);
//4. 根据已有线性表，复制一个内容相同的新线性表
//返回复制后新线性表，失败时返回线性表的头指针为NULL，
struct SeqList Copy (struct SeqList srcSeqList);
//5. 线性表判空。
int IsEmpty (struct SeqList list);
//6. 线性表求长度。
int Length (struct SeqList list);
//7. 获取起始位置。
//返回线性表中代表第一个元素的位置，空表返回EndPosition (L)
Position BeginPosition (struct SeqList list);
//8. 获取结束位置。
//返回代表线性表结束的位置
Position  EndPosition (struct SeqList list);
//9. 迭代下一位置。
//返回线性表中p有效位置的下个位置，主要用于循环遍历线性表
Position NextPosition (struct SeqList list, Position  pos);
//10. 获取元素位置。
//返回线性表代表第i个元素所在位置，1≤i≤n（设线性表的表长为n）
Position LocatePosition (struct SeqList list, int i);
//11. 定位元素位置。
//根据数据元素e查找它在线性表中出现的位置，若存在，则返回它的有效位置；
//否则返回EndPosition (L)
Position LocateElem (struct SeqList list, DataElem e);
//12. 获取元素。
//返回线性表L中pos有效位置的数据元素
DataElem GetElem (struct SeqList list, Position  pos);
//13. 获取元素。
//将线性表中pos有效位置的数据元素设置为e
void SetElem (struct SeqList list, Position  pos, DataElem e);
//14. 插入元素。
//在线性表的pos位置前插入一新的数据元素，
//pos为EndPosition (L)时添加在尾部，线性表长度加1
//成功时返回1，失败时返回0
int InsertBefore (struct SeqList *pSeqList, Position  pos, DataElem e);
//15. 删除元素。
//删除线性表中pos有效位置所在数据元素，线性表的表长减1
void Delete (struct SeqList *pSeqList, Position  pos);
#endif // __SEQLIST_H_INCLUDED_

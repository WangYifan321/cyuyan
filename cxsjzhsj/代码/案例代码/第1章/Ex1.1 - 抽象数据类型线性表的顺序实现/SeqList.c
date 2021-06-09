#include <stdlib.h>
#include <assert.h>
#include "SeqList.h"
//1. 创建空线性表
//建立一个最多可存放iSize个元素的空线性表，失败时缓冲区指针为NULL
struct SeqList Create (int iSize)
{
    struct SeqList list;
    //申请存放线性表元素的连续内存空间
    list.pDatas = (DataElem *)malloc (iSize * sizeof (DataElem));
    list.iLength = 0;
    list.iSize = iSize;
    if (list.pDatas == NULL) {//申请不到空间
        list.iSize = 0;
    }
    return list;
}
//2. 线性表清空
//元素个数置为0
void Clear (struct SeqList *pSeqList)
{
    pSeqList->iLength = 0;
}
//3. 销毁一个线性表，不再使用，释放缓冲区
void Destroy (struct SeqList *pSeqList)
{
    free (pSeqList->pDatas);                  //释放缓冲区
    pSeqList->pDatas = NULL;
    pSeqList->iSize = 0;
}
//4. 根据已有线性表，复制一个内容相同的新线性表
//返回复制后新线性表，失败时返回线性表的头指针为NULL，
struct SeqList Copy (struct SeqList srcSeqList)
{
    struct SeqList destSeqList;
    destSeqList = Create (srcSeqList.iSize); //创建一个具有相同大小缓冲区的空线性表
    if (destSeqList.pDatas == NULL)
        return destSeqList;  //创建失败时直接返回
    int i;
    for (i = 0; i < srcSeqList.iLength; ++i) //复制所有元素
        destSeqList.pDatas [i] = srcSeqList.pDatas [i];
    destSeqList.iLength = i; //设置线性表长度
    return destSeqList; //返回复制完的线性表
}

//5. 线性表判空。
int IsEmpty (struct SeqList list)
{
    return (list.iLength == 0);
}
//6. 线性表求长度。
int Length (struct SeqList list)
{
    return list.iLength;
}
//7. 获取起始位置。
//返回线性表中代表第一个元素的位置，空表返回EndPosition (L)
Position BeginPosition (struct SeqList list)
{
    return list.pDatas;
}
//8. 获取结束位置。
//返回代表线性表结束的位置
Position  EndPosition (struct SeqList list)
{
    return list.pDatas + list.iLength;
}
//9. 迭代下一位置。
//返回线性表中p有效位置的下个位置，主要用于循环遍历线性表
Position NextPosition (struct SeqList list, Position  pos)
{
    return pos+1;
}
//10. 获取元素位置。
//返回线性表代表第i个元素所在位置，1≤i≤n（设线性表的表长为n）
Position LocatePosition (struct SeqList list, int i)
{
    if (i >= 1 && i <= list.iLength)
        return list.pDatas + (i - 1);
    return list.pDatas + list.iLength; //超出范围，返回结束位置
}
//11. 定位元素位置
//根据数据元素e查找它在线性表中出现的位置，若存在，则返回它的有效位置；
//否则返回EndPosition (L)
Position LocateElem (struct SeqList list, DataElem e)
{
    int  i;
    for (i = 0; i < list.iLength; ++i)
        if (list.pDatas [i] == e) //查找到
            return list.pDatas + i;
    return list.pDatas + list.iLength; //超出范围，返回结束位置
}
//12. 获取元素
//返回线性表L中pos有效位置的数据元素
DataElem GetElem (struct SeqList list, Position  pos)
{
    assert (pos != EndPosition (list)); //断言，包含头文件assert.h
    return *pos;
}
//13. 设置元素
//将线性表中pos有效位置的数据元素设置为e
void SetElem (struct SeqList list, Position  pos, DataElem e)
{
    assert (pos != EndPosition (list)); //断言，包含头文件assert.h
    *pos = e;
}
//14. 插入元素。
//在线性表的pos位置前插入一新的数据元素，
//pos为EndPosition (L)时添加在尾部，线性表长度加1
//成功时返回1，失败时返回0
int InsertBefore (struct SeqList *pSeqList, Position  pos, DataElem e)
{
    if (pSeqList->iSize == pSeqList->iLength) {//空间已满，先扩充空间
        struct SeqList newSeqList = Create (2 * pSeqList->iSize); //建立2倍空间的临时线性表
        if (newSeqList.pDatas == NULL) {
            return 0; //申请不到空间，操作失败
        }
        int i;
        for (i = 0; i < pSeqList->iLength; ++i) //复制所有元素
            newSeqList.pDatas [i] = pSeqList->pDatas [i];
        newSeqList.iLength = i; //设置线性表长度
        pos = newSeqList.pDatas + (pos - pSeqList->pDatas); //原pos必须更新
        Destroy(pSeqList);       //销毁原线性表，板卡它的缓冲区，避免内存泄漏
        *pSeqList = newSeqList;  //用扩充空间后线性表代替原线性表
    }
    assert (pSeqList->iSize > pSeqList->iLength); //线性表内存空间必有空余
    Position  lastPos = pSeqList->pDatas+pSeqList->iLength; //线性表后空余位置
    while (pos != lastPos) { //从后往前循环后移，直到到达指定位置
        *lastPos = *(lastPos-1); //元素后移一个位置
        --lastPos;               //准备处理前一位置元素
    }
    *pos = e;           //将元素存入已空出位置
    ++pSeqList->iLength; //调整线性表长度
    return 1;
}
//15. 删除元素。
//删除线性表中pos有效位置所在数据元素，线性表的表长减1
void Delete (struct SeqList *pSeqList, Position  pos)
{
    Position  endPos = EndPosition (*pSeqList);
    assert (pos != endPos); //断言，包含头文件assert.h
    ++pos; //后移一位置
    while (pos!= endPos) {
        *(pos - 1) = *pos; //后一位置元素前移
        ++pos;           //准备后移下一个元素
    }
    --pSeqList->iLength; //调整线性表长度
}

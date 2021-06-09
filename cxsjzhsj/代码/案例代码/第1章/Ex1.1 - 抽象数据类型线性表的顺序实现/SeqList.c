#include <stdlib.h>
#include <assert.h>
#include "SeqList.h"
//1. ���������Ա�
//����һ�����ɴ��iSize��Ԫ�صĿ����Ա�ʧ��ʱ������ָ��ΪNULL
struct SeqList Create (int iSize)
{
    struct SeqList list;
    //���������Ա�Ԫ�ص������ڴ�ռ�
    list.pDatas = (DataElem *)malloc (iSize * sizeof (DataElem));
    list.iLength = 0;
    list.iSize = iSize;
    if (list.pDatas == NULL) {//���벻���ռ�
        list.iSize = 0;
    }
    return list;
}
//2. ���Ա����
//Ԫ�ظ�����Ϊ0
void Clear (struct SeqList *pSeqList)
{
    pSeqList->iLength = 0;
}
//3. ����һ�����Ա�����ʹ�ã��ͷŻ�����
void Destroy (struct SeqList *pSeqList)
{
    free (pSeqList->pDatas);                  //�ͷŻ�����
    pSeqList->pDatas = NULL;
    pSeqList->iSize = 0;
}
//4. �����������Ա�����һ��������ͬ�������Ա�
//���ظ��ƺ������Ա�ʧ��ʱ�������Ա��ͷָ��ΪNULL��
struct SeqList Copy (struct SeqList srcSeqList)
{
    struct SeqList destSeqList;
    destSeqList = Create (srcSeqList.iSize); //����һ��������ͬ��С�������Ŀ����Ա�
    if (destSeqList.pDatas == NULL)
        return destSeqList;  //����ʧ��ʱֱ�ӷ���
    int i;
    for (i = 0; i < srcSeqList.iLength; ++i) //��������Ԫ��
        destSeqList.pDatas [i] = srcSeqList.pDatas [i];
    destSeqList.iLength = i; //�������Ա���
    return destSeqList; //���ظ���������Ա�
}

//5. ���Ա��пա�
int IsEmpty (struct SeqList list)
{
    return (list.iLength == 0);
}
//6. ���Ա��󳤶ȡ�
int Length (struct SeqList list)
{
    return list.iLength;
}
//7. ��ȡ��ʼλ�á�
//�������Ա��д����һ��Ԫ�ص�λ�ã��ձ���EndPosition (L)
Position BeginPosition (struct SeqList list)
{
    return list.pDatas;
}
//8. ��ȡ����λ�á�
//���ش������Ա������λ��
Position  EndPosition (struct SeqList list)
{
    return list.pDatas + list.iLength;
}
//9. ������һλ�á�
//�������Ա���p��Чλ�õ��¸�λ�ã���Ҫ����ѭ���������Ա�
Position NextPosition (struct SeqList list, Position  pos)
{
    return pos+1;
}
//10. ��ȡԪ��λ�á�
//�������Ա�����i��Ԫ������λ�ã�1��i��n�������Ա�ı�Ϊn��
Position LocatePosition (struct SeqList list, int i)
{
    if (i >= 1 && i <= list.iLength)
        return list.pDatas + (i - 1);
    return list.pDatas + list.iLength; //������Χ�����ؽ���λ��
}
//11. ��λԪ��λ��
//��������Ԫ��e�����������Ա��г��ֵ�λ�ã������ڣ��򷵻�������Чλ�ã�
//���򷵻�EndPosition (L)
Position LocateElem (struct SeqList list, DataElem e)
{
    int  i;
    for (i = 0; i < list.iLength; ++i)
        if (list.pDatas [i] == e) //���ҵ�
            return list.pDatas + i;
    return list.pDatas + list.iLength; //������Χ�����ؽ���λ��
}
//12. ��ȡԪ��
//�������Ա�L��pos��Чλ�õ�����Ԫ��
DataElem GetElem (struct SeqList list, Position  pos)
{
    assert (pos != EndPosition (list)); //���ԣ�����ͷ�ļ�assert.h
    return *pos;
}
//13. ����Ԫ��
//�����Ա���pos��Чλ�õ�����Ԫ������Ϊe
void SetElem (struct SeqList list, Position  pos, DataElem e)
{
    assert (pos != EndPosition (list)); //���ԣ�����ͷ�ļ�assert.h
    *pos = e;
}
//14. ����Ԫ�ء�
//�����Ա��posλ��ǰ����һ�µ�����Ԫ�أ�
//posΪEndPosition (L)ʱ�����β�������Ա��ȼ�1
//�ɹ�ʱ����1��ʧ��ʱ����0
int InsertBefore (struct SeqList *pSeqList, Position  pos, DataElem e)
{
    if (pSeqList->iSize == pSeqList->iLength) {//�ռ�������������ռ�
        struct SeqList newSeqList = Create (2 * pSeqList->iSize); //����2���ռ����ʱ���Ա�
        if (newSeqList.pDatas == NULL) {
            return 0; //���벻���ռ䣬����ʧ��
        }
        int i;
        for (i = 0; i < pSeqList->iLength; ++i) //��������Ԫ��
            newSeqList.pDatas [i] = pSeqList->pDatas [i];
        newSeqList.iLength = i; //�������Ա���
        pos = newSeqList.pDatas + (pos - pSeqList->pDatas); //ԭpos�������
        Destroy(pSeqList);       //����ԭ���Ա��忨���Ļ������������ڴ�й©
        *pSeqList = newSeqList;  //������ռ�����Ա����ԭ���Ա�
    }
    assert (pSeqList->iSize > pSeqList->iLength); //���Ա��ڴ�ռ���п���
    Position  lastPos = pSeqList->pDatas+pSeqList->iLength; //���Ա�����λ��
    while (pos != lastPos) { //�Ӻ���ǰѭ�����ƣ�ֱ������ָ��λ��
        *lastPos = *(lastPos-1); //Ԫ�غ���һ��λ��
        --lastPos;               //׼������ǰһλ��Ԫ��
    }
    *pos = e;           //��Ԫ�ش����ѿճ�λ��
    ++pSeqList->iLength; //�������Ա���
    return 1;
}
//15. ɾ��Ԫ�ء�
//ɾ�����Ա���pos��Чλ����������Ԫ�أ����Ա�ı���1
void Delete (struct SeqList *pSeqList, Position  pos)
{
    Position  endPos = EndPosition (*pSeqList);
    assert (pos != endPos); //���ԣ�����ͷ�ļ�assert.h
    ++pos; //����һλ��
    while (pos!= endPos) {
        *(pos - 1) = *pos; //��һλ��Ԫ��ǰ��
        ++pos;           //׼��������һ��Ԫ��
    }
    --pSeqList->iLength; //�������Ա���
}

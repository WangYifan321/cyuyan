#include <stdlib.h>
#include <assert.h>
#include "List.h"

//1. ���������Ա�
//�ձ����ĵ�����ֻ��һ��ͷ��㣬ʧ��ʱ��βָ��ΪNULL
struct List Create ()
{
    struct List list;
    //����һ�����
    list.pHead = list.pTail = (struct Node *)malloc (sizeof (struct Node));
    if (list.pHead != NULL)
        list.pHead->next = NULL; //�����޽��
    return list;
}
//2. ���Ա���ա�
//�ͷ������г�ͷ��������н��
void Clear (struct List *pList)
{
    struct Node *p = pList->pHead->next; //��ͷ�����㿪ʼɾ��
    while (p != NULL) {     //ֱ�����
        struct Node *q = p; //��סҪ�ͷŽ��
        p = p->next;        //׼���ͷ���һ��
        free (q);           //�ͷŽ�㣬�ͷź󲻿��ٷ��ʽ��
    }
    pList->pHead->next = NULL; //ͷ�������޽��
    pList->pTail = pList->pHead;
}
//3. ����һ�����Ա�����ʹ�ã��ͷ����н�㡣
//��������ָ������ĵ�ַ�����ٵ�����
void Destroy (struct List *pList)
{
    Clear (pList);                        //���������
    free (pList->pHead);                  //�ͷ����ʣ���ͷ���
    pList->pHead = pList->pTail = NULL;   //�����Ա���ָ������ÿ�
}
//4. �����������Ա�����һ��������ͬ�������Ա�
//����ԭ���Ա�����ԭ���Ա���������Ϊ�����Ա������
//���ظ��ƺ������Ա�ʧ��ʱ�������Ա��ͷָ��ΪNULL��
struct List Copy (struct List srcList)
{
    struct List destList;
    destList = Create (); //������ͷ���Ŀյ�����
    if (destList.pHead == NULL)
        return destList;  //����ʧ��ʱֱ�ӷ���
    struct Node  *p;
    p = srcList.pHead->next; //����ԭ����ͷ���
    while (p != NULL) {//ѭ������ԭ����
        struct Node *s;
        s = (struct Node *)malloc (sizeof (struct Node));//�����½��
        if (s == NULL) {
            Destroy (&destList); //����ʧ��ʱ�������Ա������ڴ�й©
            return destList;
        }
        s->data = p->data; //����Ԫ��
        destList.pTail->next = s; //�������������
        s->next = NULL; //�����޽��
        destList.pTail = s;       //���һ������ѱ仯
        p = p->next;    //׼�������¸����
    }
    return destList; //���ظ���������Ա�
}
//5. ���Ա��пա�
//�ж����Ա��Ƿ�Ϊ�ձ������򷵻�1�����򷵻�0
int IsEmpty (struct List list)
{
    return (list.pHead->next == NULL); //ͷ�����޽��
}
//6. ���Ա��󳤶ȡ�
//�������Ա�������Ԫ�صĸ���
int Length (struct List list)
{
    int iCount = 0;
    struct Node *p = list.pHead->next; //��ͷ�����㿪ʼ����
    while (p != NULL) {     //ֱ�����
        ++iCount;
        p = p->next;        //��ʱ����������һ���
    }
    return iCount;
}
//7. ��ȡ��ʼλ�á�
//�������Ա��д����һ��Ԫ�ص�λ�ã��ձ���EndPosition (L)
Position BeginPosition (struct List list)
{
    return list.pHead;
}
//8. ��ȡ����λ�á�
//���ش������Ա������λ��
Position  EndPosition (struct List list)
{
    return list.pTail;
}
//9. ������һλ�á�
//�������Ա���p��Чλ�õ��¸�λ�ã���Ҫ����ѭ���������Ա�
Position NextPosition (struct List list, Position  pos)
{
    return pos->next;
}
//10. ��ȡԪ��λ�á�
//�������Ա�����i��Ԫ������λ�ã�1��i��n�������Ա�ı�Ϊn��
Position LocatePosition (struct List list, int i)
{
    Position  pos = list.pHead; //��ͷ��㿪ʼ
    while (--i> 0 && pos->next != NULL) {//������ɻ�ֱ������λ��
        pos = pos->next;        //������һ���
    }
    return pos;
}
//11. ��λԪ��λ�á�
//��������Ԫ��e�����������Ա��г��ֵ�λ�ã������ڣ��򷵻�������Чλ�ã�
//���򷵻�EndPosition (L)
Position LocateElem (struct List list, DataElem e)
{
    Position  pos = list.pHead; //��ͷ��㿪ʼ
    while (pos->next != NULL && pos->next->data != e) {
        pos = pos->next;        //������һ���
    }
    return pos; //����Ԫ�����ڽ���ǰһ�����ָ��
}
//12. ��ȡԪ�ء�
//�������Ա�L��pos��Чλ�õ�����Ԫ��
DataElem GetElem (struct List list, Position  pos)
{
    assert (pos != EndPosition (list)); //���ԣ�����ͷ�ļ�assert.h
    return pos->next->data;
}
//13. ��ȡԪ�ء�
//�����Ա���pos��Чλ�õ�����Ԫ������Ϊe
void SetElem (struct List list, Position  pos, DataElem e)
{
    assert (pos != EndPosition (list)); //���ԣ�����ͷ�ļ�assert.h
    pos->next->data = e;
}
//14. ����Ԫ�ء�
//�����Ա��posλ��ǰ����һ�µ�����Ԫ�أ�
//posΪEndPosition (L)ʱ�����β�������Ա��ȼ�1
//�ɹ�ʱ����1��ʧ��ʱ����0
int InsertBefore (struct List *pList, Position  pos, DataElem e)
{
    struct Node *s = (struct Node *)malloc (sizeof (struct Node));//�����½��
    if (s == NULL)
        return 0;
    s->data = e;
    s->next = pos->next; //������pos��ָ����
    pos->next = s;
    if (pList->pTail == pos)
        pList->pTail = s; //���������Ա����ʱ������β���ָ��
    return 1;
}
//15. ɾ��Ԫ�ء�
//ɾ�����Ա���pos��Чλ����������Ԫ�أ����Ա�ı���1
void Delete (struct List *pList, Position  pos)
{
    assert (pos != EndPosition (*pList)); //���ԣ�����ͷ�ļ�assert.h
    struct Node *s = pos->next; //��ɾ�����
    pos->next = s->next;        //������ɾ�����
    free (s);                 //�ͷŽ��
    if (pList->pTail == s)
        pList->pTail = pos; //ɾ�����Ա����һ�����ʱ������β���ָ��
}

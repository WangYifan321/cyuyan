#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "UBigNumber.h"

//�����޷��Ŵ���
struct UBigNumber InputUBN ()
{
    struct UBigNumber result;
    _InitUBN(&result);

    char ch;
    //�����������ַ�
    do
        ch = getchar ();
    while (ch < '0' || ch > '9');
    while (ch >= '0' && ch <= '9')
    {
        _AppendDigit (&result, ch - '0'); //���1λ
        ch = getchar ();
    }
    _Normalize(&result);
    return result;
}
//��ӡ�޷��Ŵ���
void PrintUBN (struct UBigNumber ubn)
{
    assert (ubn.digitCount > 0 && ubn.pHead->next != NULL); //���� �� ������1λ����
    struct Node *la = ubn.pHead->next; //ͷ��������ݣ�����
    while (la)
    {
        printf ("%d", la->digit);
        la = la->next;
    }
}
//�����޷��Ŵ������
struct UBigNumber AddUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    struct UBigNumber result, *pResult = &result;
    _InitUBN(pResult);
    int iCarry = 0; //��λ����ʼ0
    struct Node *p1, *p2;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)   //������ͬλ����
    {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10; //�½�λ
        digit %= 10;         //��ǰ���λ
        _AppendFrontDigit (pResult, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
        p2 = p2->prev;
    }
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead)  //�ڶ�����ʣ��λ����
    {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) //����λ����
        _AppendFrontDigit (pResult, iCarry);
    return result;
}
//�����޷��Ŵ������ͷſռ�
void DestoryUBN (struct UBigNumber *pUBN)
{
    while (pUBN->pHead != NULL)  //��պ�Ӧ��ֻʣһ��ͷ���
    {
        struct Node *p =  pUBN->pHead;  //��ɾ�����
        pUBN->pHead = p->next;          //βָ��ǰ��
        free (p);                       //�ͷŽ��
    }
}
//������ʾ�޷��Ŵ����ô�ͷ���˫����
void _InitUBN (struct UBigNumber *pUBN)
{
    struct Node *p = _NewNode ();
    pUBN->pHead = pUBN->pTail = p; //��ͷ���
    p->next = p->prev = NULL;
    pUBN->digitCount = 0; //λ��0
}
//�޷��Ŵ���β�����һλ��
void _AppendDigit (struct UBigNumber *pUBN, int digit)
{
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0)//ԭֻ��һ����λ0
    {
        pUBN->pTail->digit = digit; //λ�����䣬��ֵΪ0
        return;
    }
    struct Node *p = _NewNode ();  //�����½��
    p->digit = digit;              //���ý����ֵ
    p->next = NULL;                //�޸�˫������ӳ�Ϊ��β�����
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;             //�޸�λ��
}
//�޷��Ŵ���ǰ���һλ��
void _AppendFrontDigit (struct UBigNumber *pUBN, int digit)
{
    struct Node *p = _NewNode (); //�����½��
    p->digit = digit;             //���ý����ֵ
    p->next = pUBN->pHead->next;  //�޸�˫���������ͷ����
    if (p->next != NULL)
        p->next->prev = p;
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead)
        pUBN->pTail = p;          //ԭ��ֻ��ͷ���ʱ���½��Ҳ��β���
    ++pUBN->digitCount;           //�޸�λ��
}
//�޷��Ŵ����淶��ʾ��ȥ����λ����0�����ٺ�һλ����
void _Normalize (struct UBigNumber *pUBN)
{
    if (pUBN->digitCount == 0)
        _AppendDigit (pUBN, 0);
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0)  //ȥ����λ�����0
    {
        struct Node *p;
        p = pUBN->pHead->next; //��ɾ���Ľ��
        pUBN->pHead->next = p->next; //����������ɾ��
        p->next->prev = pUBN->pHead; //����������ɾ��
        free (p);                       //�ͷŽ��
        --pUBN->digitCount;          //����λ��
    }
}
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node *_NewNode ()
{
    struct Node *p;
    p = (struct Node *) malloc (sizeof (struct Node));
    if (p == NULL)   //����ʧ��
    {
        printf ("Error : out of memory\n");
        exit (-1); //�򻯳����˳�����
    }
    return p;
}

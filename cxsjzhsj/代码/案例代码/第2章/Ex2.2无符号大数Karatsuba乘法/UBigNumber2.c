#include <stdio.h>
#include <assert.h>
#include "UBigNumber.h"

//�����޷��Ŵ������
struct UBigNumber SubUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    struct UBigNumber result;
    _InitUBN(&result);
    int iCarry = 0; //��λ����ʼ0
    struct Node *p1, *p2;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead)   //������ͬλ����
    {
        int digit = p1->digit - p2->digit + iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;         //��ǰ���λ
            iCarry = -1; //�½�λ
        }
        _AppendFrontDigit (&result, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
        p2 = p2->prev;
    }
    assert (p2 == pB->pHead);
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit + iCarry;
        iCarry = 0;
        if (digit < 0)
        {
            digit += 10;         //��ǰ���λ
            iCarry = -1; //�½�λ
        }
        _AppendFrontDigit (&result, digit); //�����������λ
        p1 = p1->prev; //׼������ǰһλ
    }
    assert (iCarry == 0);
    _Normalize(&result);
    return result;
}
//�����޷��Ŵ������
struct UBigNumber MultiplyUBN (struct UBigNumber *pA, struct UBigNumber *pB)
{
    //�ݹ���ֹ����
    if (pB->digitCount == 1)
        return _MultiplyDigit (pA, pB->pTail->digit);
    else if (pA->digitCount == 1)
        return _MultiplyDigit (pB, pA->pTail->digit);
    // �����ֳ���
    int m = pA->digitCount;
    int n = pB->digitCount;

    int h = (m> n?m:n) / 2;
    /* ���Ϊa, b, c, d */
    struct UBigNumber a, b, c, d;

    a = _FetchSub (pA, 0, m - h); //��m-hλ
    b = _FetchSub (pA, m - h, m); //��hλ
    c = _FetchSub (pB, 0, n - h);  //��m-hλ
    d = _FetchSub (pB, n - h, n);  //��hλ
    // ����z2, z0, z1, �˴��ĳ˷�ʹ�õݹ�
    struct UBigNumber z0, z1, z2;

    z2 = MultiplyUBN (&a, &c); //z2 = a * c;
    z0 = MultiplyUBN (&b, &d); //z0 = b * d;
    struct UBigNumber  t1, t2, t3,t4,t5, result;
    t1 = AddUBN(&a, &b);    //t1 = a+b
    t2 = AddUBN(&c, &d);     //t2 = c+d
    //���ٸ�����ʹ�õ��޷��Ŵ���
    DestoryUBN (&a);
    DestoryUBN (&b);
    DestoryUBN (&c);
    DestoryUBN (&d);
    t3 = MultiplyUBN (&t1, &t2); //t3 = (a+b)*(c+d)
    t4 = AddUBN(&z0, &z2);   //t4 = z0 + z2
    z1 = SubUBN(&t3, &t4);   //z1 = (a+b)*(c+d) - z2 - z0

    int i;
    for (i= 0; i < 2 *h; ++i) //z2 *= (10^(2*h))
        _AppendDigit (&z2, 0);
    for (i= 0; i < h; ++i) //z1 *= (10 ^ h)
        _AppendDigit (&z1, 0);
    t5 = AddUBN(&z2, &z1); //t5= z2*10^2h + z1 * 10^h
    result = AddUBN(&t5, &z0); //result = z2*10^2h + z1 * 10^h +z0

    DestoryUBN (&z0);
    DestoryUBN (&z1);
    DestoryUBN (&z2);
    DestoryUBN (&t1);
    DestoryUBN (&t2);
    DestoryUBN (&t3);
    DestoryUBN (&t4);
    DestoryUBN (&t5);
    return result;
}

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit (struct UBigNumber *pA, int digit2)
{
    struct UBigNumber result;
    _InitUBN (&result);
    if (digit2 == 0)
    {
        _AppendDigit (&result, 0);
        return result;
    }

    int iCarry = 0; //��λ����ʼ0
    struct Node *p1;
    p1 = pA->pTail; //�ӵ�λ��ʼ����
    while (p1 != pA->pHead)   //��һ����ʣ��λ����
    {
        int digit = p1->digit * digit2 + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        _AppendFrontDigit (&result, digit);
        p1 = p1->prev;
    }
    if (iCarry != 0) //����λ����
        _AppendFrontDigit (&result, iCarry);
    return result;
}

//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
struct UBigNumber _FetchSub (struct UBigNumber *pA, int start, int end)
{
    struct UBigNumber result;
    _InitUBN (&result);
    int i = 0;
    struct Node *p = pA->pHead->next;
    while (i < start && p != NULL)
    {
        p = p->next;
        ++i;
    }
    while (i < end && p != NULL)
    {
        _AppendDigit (&result, p->digit); //�����β��
        p = p->next;
        ++i;
    }
    _Normalize (&result);
    return result;
}

#ifndef UBIGNUMBER_H_INCLUDED
#define UBIGNUMBER_H_INCLUDED

struct	Node
{
    int	digit; //����
    struct Node *next, *prev; //ǰ����ָ��
};
//�޷��Ŵ����ṹ��
struct UBigNumber
{
    int     digitCount; //λ��
    struct Node *pHead, *pTail; //ָ��ͷ��㣬β���
};
//���к������صĴ���ռ�õ��ڴ���Դ�ɺ��������߸����ͷ�
//�����޷��Ŵ���
struct UBigNumber InputUBN ();
//��ӡ�޷��Ŵ���
void PrintUBN (struct UBigNumber ubn);
//�����޷��Ŵ������
struct UBigNumber AddUBN (struct UBigNumber *pA, struct UBigNumber *pB);
//�����޷��Ŵ������ͷſռ�
void DestoryUBN (struct UBigNumber *pA);

//���к������޷��Ŵ�������������
//������ʾ�޷��Ŵ����ô�ͷ���˫����
void _InitUBN (struct UBigNumber *pUBN);
//�޷��Ŵ���β�����һλ��
void _AppendDigit (struct UBigNumber *pUBN, int digit);
//�޷��Ŵ���ǰ�����һλ��
void _AppendFrontDigit (struct UBigNumber *pUBN, int digit);
//�޷��Ŵ����淶��ʾ��ȥ����λ����0�����ٺ�һλ����
void _Normalize (struct UBigNumber *pUBN);
//��̬����һ����㣬���ؽ��ָ��
//����ʧ��ʱ���򻯳����˳�����
struct Node *_NewNode ();

//�����޷��Ŵ������
struct UBigNumber SubUBN (struct UBigNumber *pA, struct UBigNumber *pB);
//�����޷��Ŵ������
struct UBigNumber MultiplyUBN (struct UBigNumber *pA, struct UBigNumber *pB);

//�޷��Ŵ�����1λ��
struct UBigNumber _MultiplyDigit (struct UBigNumber *pA, int digit);
//�����޷��Ŵ�����[start, end)������������ɵ��޷��Ŵ���
//������Χ�������ֺ��ԣ����Ժ������в�����ʱ����0
struct UBigNumber _FetchSub (struct UBigNumber *pA, int start, int end);
#endif // UBIGNUMBER_H_INCLUDED

#ifndef __LSIT_H_INCLUDED_
#define __LSIT_H_INCLUDED_
typedef  int DataElem;    //����Ԫ������Ϊ����

//����������
struct Node {
    DataElem  data;
    struct Node *next;
};

//���Ա�����
struct List {
    struct Node *pHead;
    struct Node *pTail;
};
typedef  struct Node *  Position;    //���Ա���λ������

//1. ���������Ա�
//�ձ����ĵ�����ֻ��һ��ͷ��㣬ʧ��ʱ��βָ��ΪNULL
struct List Create ();
//2. ���Ա���ա�
//�ͷ������г�ͷ��������н��
void Clear (struct List *pList);
//3. ����һ�����Ա�����ʹ�ã��ͷ����н�㡣
//��������ָ������ĵ�ַ�����ٵ�����
void Destroy (struct List *pList);
//4. �����������Ա�����һ��������ͬ�������Ա�
//����ԭ���Ա�����ԭ���Ա���������Ϊ�����Ա������
//���ظ��ƺ������Ա�ʧ��ʱ�������Ա��ͷָ��ΪNULL��
struct List Copy (struct List srcList);
//5. ���Ա��пա�
//�ж����Ա��Ƿ�Ϊ�ձ������򷵻�1�����򷵻�0
int IsEmpty (struct List list);
//6. ���Ա��󳤶ȡ�
//�������Ա�������Ԫ�صĸ���
int Length (struct List list);
//7. ��ȡ��ʼλ�á�
//�������Ա��д����һ��Ԫ�ص�λ�ã��ձ���EndPosition (L)
Position BeginPosition (struct List list);
//8. ��ȡ����λ�á�
//���ش������Ա������λ��
Position  EndPosition (struct List list);
//9. ������һλ�á�
//�������Ա���p��Чλ�õ��¸�λ�ã���Ҫ����ѭ���������Ա�
Position NextPosition (struct List list, Position  pos);
//10. ��ȡԪ��λ�á�
//�������Ա�����i��Ԫ������λ�ã�1��i��n�������Ա�ı�Ϊn��
Position LocatePosition (struct List list, int i);
//11. ��λԪ��λ�á�
//��������Ԫ��e�����������Ա��г��ֵ�λ�ã������ڣ��򷵻�������Чλ�ã�
//���򷵻�EndPosition (L)
Position LocateElem (struct List list, DataElem e);
//12. ��ȡԪ�ء�
//�������Ա�L��pos��Чλ�õ�����Ԫ��
DataElem GetElem (struct List list, Position  pos);
//13. ��ȡԪ�ء�
//�����Ա���pos��Чλ�õ�����Ԫ������Ϊe
void SetElem (struct List list, Position  pos, DataElem e);
//14. ����Ԫ�ء�
//�����Ա��posλ��ǰ����һ�µ�����Ԫ�أ�
//posΪEndPosition (L)ʱ�����β�������Ա��ȼ�1
//�ɹ�ʱ����1��ʧ��ʱ����0
int InsertBefore (struct List *pList, Position  pos, DataElem e);
//15. ɾ��Ԫ�ء�
//ɾ�����Ա���pos��Чλ����������Ԫ�أ����Ա�ı���1
void Delete (struct List *pList, Position  pos);
#endif // __LSIT_H_INCLUDED_

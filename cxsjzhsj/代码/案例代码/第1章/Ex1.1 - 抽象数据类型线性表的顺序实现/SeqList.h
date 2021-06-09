#ifndef __SEQLIST_H_INCLUDED_
#define __SEQLIST_H_INCLUDED_
typedef  int DataElem;    //����Ԫ������Ϊ����

//���Ա�����
struct SeqList {
    DataElem *pDatas;   //���Ԫ�ر�Ļ�����ָ��
    int       iLength;  //���Ա���
    int       iSize;    //��������С
};
typedef  DataElem *  Position;    //���Ա���λ������

//1. ���������Ա�
//����һ�����ɴ��iSize��Ԫ�ص����Ա�����ʱΪ�ձ�ʧ��ʱ������ָ��ΪNULL
struct SeqList Create (int iSize);
//2. ���Ա���ա�
//Ԫ�ظ�����Ϊ0
void Clear (struct SeqList *pSeqList);
//3. ����һ�����Ա�����ʹ�ã��ͷŻ�������
void Destroy (struct SeqList *pSeqList);
//4. �����������Ա�����һ��������ͬ�������Ա�
//���ظ��ƺ������Ա�ʧ��ʱ�������Ա��ͷָ��ΪNULL��
struct SeqList Copy (struct SeqList srcSeqList);
//5. ���Ա��пա�
int IsEmpty (struct SeqList list);
//6. ���Ա��󳤶ȡ�
int Length (struct SeqList list);
//7. ��ȡ��ʼλ�á�
//�������Ա��д����һ��Ԫ�ص�λ�ã��ձ���EndPosition (L)
Position BeginPosition (struct SeqList list);
//8. ��ȡ����λ�á�
//���ش������Ա������λ��
Position  EndPosition (struct SeqList list);
//9. ������һλ�á�
//�������Ա���p��Чλ�õ��¸�λ�ã���Ҫ����ѭ���������Ա�
Position NextPosition (struct SeqList list, Position  pos);
//10. ��ȡԪ��λ�á�
//�������Ա�����i��Ԫ������λ�ã�1��i��n�������Ա�ı�Ϊn��
Position LocatePosition (struct SeqList list, int i);
//11. ��λԪ��λ�á�
//��������Ԫ��e�����������Ա��г��ֵ�λ�ã������ڣ��򷵻�������Чλ�ã�
//���򷵻�EndPosition (L)
Position LocateElem (struct SeqList list, DataElem e);
//12. ��ȡԪ�ء�
//�������Ա�L��pos��Чλ�õ�����Ԫ��
DataElem GetElem (struct SeqList list, Position  pos);
//13. ��ȡԪ�ء�
//�����Ա���pos��Чλ�õ�����Ԫ������Ϊe
void SetElem (struct SeqList list, Position  pos, DataElem e);
//14. ����Ԫ�ء�
//�����Ա��posλ��ǰ����һ�µ�����Ԫ�أ�
//posΪEndPosition (L)ʱ�����β�������Ա��ȼ�1
//�ɹ�ʱ����1��ʧ��ʱ����0
int InsertBefore (struct SeqList *pSeqList, Position  pos, DataElem e);
//15. ɾ��Ԫ�ء�
//ɾ�����Ա���pos��Чλ����������Ԫ�أ����Ա�ı���1
void Delete (struct SeqList *pSeqList, Position  pos);
#endif // __SEQLIST_H_INCLUDED_

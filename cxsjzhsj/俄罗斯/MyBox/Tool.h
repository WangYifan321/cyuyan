#pragma once
class Tool
{
private:
	int _data[4][4];//4*4�ķ����������
	int _type;		//����˹��������ͱ���

public:
	Tool(int type);	//���캯��,����û��ʹ�ö�̬���䣬����������������ֱ�Ӹ��ơ���ֵ��
	const int GetType() const;	//��ȡTool������
	const int & ElementAt(int i, int j) const; //��ȡС������ֵ
	Tool Roll();	//�Է��������̬�任
};


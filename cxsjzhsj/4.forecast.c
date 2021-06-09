#include <stdio.h>
#include <stdlib.h>
#define bool int
#define false 0
#define true 1

struct Data
{
	double x; //���
	double y; //�۸�
};

struct Data data[100]; //�洢����
int dataNum;		   //������Ŀ
double a, b;		   //Y = a + bX
double sumXY;		   //x * y�����
double sumX;		   //x�����
double sumY;		   //y�����
double sumXX;		   //x * x�����

//���ݶ���
bool inputs()
{

	char fname[256]; //�ļ���
	printf("�����������ݵ��ļ�����");
	scanf("%s", fname);
	printf("\n������ĿdataNum��\n");
	scanf("%d", &dataNum);

	FILE *fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("���ܴ�������ļ�\n");
		return false;
	}
	for (int i = 0; i < dataNum; i++)
	{
		fscanf(fp, "%lf,%lf", &data[i].x, &data[i].y);
	}
	fclose(fp);
	return true;
}

//��ʼ��
void init()
{
	a = b = sumXY = sumX = sumY = sumXX = 0;
}

//���Իع�
void lineReg()
{

	for (int i = 0; i < dataNum; i++)
	{
		sumXY += data[i].x * data[i].y;
		sumX += data[i].x;
		sumY += data[i].y;
		sumXX += data[i].x * data[i].x;
	}

	b = (sumXY * dataNum - sumX * sumY) / (sumXX * dataNum - sumX * sumX);
	a = sumY / dataNum - b * sumX / dataNum;

	printf("Y=%.2lfX+%.2lf\n", b, a);
}

//���
void outputs()
{

	double x;
	double y;
	printf("�����뷿�ӵ��������λ��ƽ���ף���");
	scanf("%lf", &x);
	y = a + b * x;
	printf("Ԥ�Ʒ���Ϊ��%.2lfԪ\n", y);
}

int main()
{

	if (inputs() == false)
	{
		return 0;
	}
	init();
	lineReg();
	outputs();
	system("pause");
	return 0;
}
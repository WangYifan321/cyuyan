#include <stdio.h>
#include <stdlib.h>
#define bool int
#define false 0
#define true 1

struct Data
{
	double x; //面积
	double y; //价格
};

struct Data data[100]; //存储数据
int dataNum;		   //样本数目
double a, b;		   //Y = a + bX
double sumXY;		   //x * y的求和
double sumX;		   //x的求和
double sumY;		   //y的求和
double sumXX;		   //x * x的求和

//数据读入
bool inputs()
{

	char fname[256]; //文件名
	printf("请输入存放数据的文件名：");
	scanf("%s", fname);
	printf("\n样本数目dataNum：\n");
	scanf("%d", &dataNum);

	FILE *fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("不能打开输入的文件\n");
		return false;
	}
	for (int i = 0; i < dataNum; i++)
	{
		fscanf(fp, "%lf,%lf", &data[i].x, &data[i].y);
	}
	fclose(fp);
	return true;
}

//初始化
void init()
{
	a = b = sumXY = sumX = sumY = sumXX = 0;
}

//线性回归
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

//输出
void outputs()
{

	double x;
	double y;
	printf("请输入房子的面积（单位：平方米）：");
	scanf("%lf", &x);
	y = a + b * x;
	printf("预计房价为：%.2lf元\n", y);
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
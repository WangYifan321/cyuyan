#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define bool int
#define false 0
#define true 1
#define K 3                        	//�ص���Ŀ
#define dimNum 4                   	//ά��
#define MAX_ROUNDS 100                         //�������ĵ�������

//�洢�β�����ݵĽṹ��
struct Iris {
	double sepalLength;             	//���೤��
	double sepalWidth;              	//������
	double petalLength;             	//���곤��
	double petalWidth;              	//������
	int clusterID;                  	//���ڴ�Ÿõ������Ĵ�Ⱥ���
};

int isContinue;                                 //�ж��Ƿ��������
struct Iris iris[150];                         //��¼�β��������
struct Iris clusterCenter[K];     	//�洢����
struct Iris centerCalc[K];      	//����������
int dataNum;                                     //���ݼ��е����ݼ�¼����
int clusterCenterInitIndex[K];    	//��¼ÿ���������ʹ�õ����ݵ�ı��
double distanceFromCenter[K];    	//��¼�㵽���ĵľ���
int dataSizePerCluster[K];        	//ÿ����Ⱥ��ĸ���

//���ݶ���
bool Inputs() {
	char fname[256];//�ļ���
	char name[20]; //�洢�β��������
	printf("�����������ݵ��ļ�����");
	scanf("%s", fname);
	printf("\n������ĿdataNum��\n");
	scanf("%d", &dataNum);
	FILE *fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("���ܴ�������ļ�\n");
		return false;
	}
	for (int i = 0; i < dataNum; i++) {
		fscanf(fp, "%lf,%lf,%lf,%lf,%s", &iris[i].sepalLength, &iris[i].sepalWidth, &iris[i].petalLength, &iris[i].petalWidth, name);
		iris[i].clusterID = -1; //cluster id ��ֵΪ-1
	}
	fclose(fp);
	return true;
}

//��ʼ����Ⱥ
void InitialCluster() {
	int random; //���������ı���
	//��K�����ĵı�ų�ʼ��Ϊ-1
		for (int i = 0; i < K; i++) {
			clusterCenterInitIndex[i] = -1;
	}
	//�������K�����ı�ţ������ظ���
	for (int i = 0; i < K; i++) {
		random = rand() % (dataNum - 1);  //�������0��dataNum -1֮����������
		int j = 0;
		//��ǰi�����ı�Ž��бȶԣ��ж��Ƿ����ظ�
		while (j < i) {
			if (random == clusterCenterInitIndex[j]) {
				random = rand() % (dataNum - 1);
				j = 0;
			}
			else {
				j++;
			}
		}
		clusterCenterInitIndex[i] = random;   //���õ�i�����ĵı��
	}
	//ȷ��K�����ı�ź󣬽���������iris�ж�Ӧ��ŵ����ݸ�ֵ�����Ľṹ������clusterCenter
	for (int i = 0; i < K; i++) {
		clusterCenter[i].sepalLength = iris[clusterCenterInitIndex[i]].sepalLength;
		clusterCenter[i].sepalWidth = iris[clusterCenterInitIndex[i]].sepalWidth;
		clusterCenter[i].petalLength = iris[clusterCenterInitIndex[i]].petalLength;
		clusterCenter[i].petalWidth = iris[clusterCenterInitIndex[i]].petalWidth;
		clusterCenter[i].clusterID = i;    //������ı������Ϊi
		//��iris�и����ĵ���������Ϊi
		iris[clusterCenterInitIndex[i]].clusterID = i;
	}
}

//����һ���㵽һ�����ĵľ���
void CalDistance2OneCenters(int pointID, int centerID) {
	double x1 = pow((iris[pointID].sepalLength - clusterCenter[centerID].sepalLength), 2.0);
	double x2 = pow((iris[pointID].sepalWidth - clusterCenter[centerID].sepalWidth), 2.0);
	double x3 = pow((iris[pointID].petalLength - clusterCenter[centerID].petalLength), 2.0);
	double x4 = pow((iris[pointID].petalWidth - clusterCenter[centerID].petalWidth), 2.0);
	distanceFromCenter[centerID] = sqrt(x1 + x2 + x3 + x4);
}

//����һ���㵽�������ĵľ���
void CalDistance2AllCenters(int pointID) {
	for (int i = 0; i < K; i++) {
		CalDistance2OneCenters(pointID, i);   //����һ���㵽һ�����ĵľ���
	}
}

//��һ���㻮�ֵ���������Ĵ�Ⱥ
void Partition4OnePoint(int pointID) {
	int minIndex = 0;//��¼������������ı��
	//�����̾��룬�����¾�����������ı��
	double minValue = distanceFromCenter[0];
	for (int i = 0; i < K; i++) {
		if (distanceFromCenter[i] < minValue) {
			minValue = distanceFromCenter[i];
			 minIndex = i;
		}
	}
	//�������������Ϊ����������ڵ�����
	iris[pointID].clusterID = clusterCenter[minIndex].clusterID;
}

//ÿһ�־��࣬��Ҫ�����е㶼���ֵ���������Ĵ�Ⱥ��
void Partition4AllPointOneCluster() {
	for (int i = 0; i < dataNum; i++) {
		if (iris[i].clusterID != -1) {
			continue; //�����������ģ�����Ҫ���ִ�Ⱥ
		}
		else {
			CalDistance2AllCenters(i);    //�����i���㵽�������ĵľ���
			Partition4OnePoint(i);         //����i���㻮�ֵ���������Ĵ�Ⱥ
		}
	}
}

//�Ƚ��¾�����ֵ�Ĳ���������ȵģ���ֹͣ��������
void CompareNewOldClusterCenter() {
	isContinue = 0;       //��ʼ����Ǳ���isContinue��ֵΪ0; 0��ʾֹͣ���࣬1��ʾ��������
	for (int i = 0; i < K; i++) {
		if (centerCalc[i].sepalLength != clusterCenter[i].sepalLength || centerCalc[i].sepalWidth != clusterCenter[i].sepalWidth || centerCalc[i].petalLength != clusterCenter[i].petalLength || centerCalc[i].petalWidth != clusterCenter[i].petalWidth) {
			isContinue = 1;//�����һ������ֵ��ͬ���ͽ�isContinue ��ֵ����Ϊ1����ʾ��Ҫ��������
			break;          //����ѭ��
		}
	}
}

//���¼����µ�����
void CalClusterCenter() {
	//��ʼ����������飬�������и�Ԫ��ֵΪ0
	memset(centerCalc, 0, sizeof(centerCalc));
	memset(dataSizePerCluster, 0, sizeof(dataSizePerCluster));
	//�ֱ��ÿ����Ⱥ�ڵ�ÿ������ĸ�������ͣ�������ÿ����Ⱥ�ڵ�ĸ���
	for (int i = 0; i < dataNum; i++) {
		centerCalc[iris[i].clusterID].sepalLength += iris[i].sepalLength;
		centerCalc[iris[i].clusterID].sepalWidth += iris[i].sepalWidth;
		centerCalc[iris[i].clusterID].petalLength += iris[i].petalLength;
		centerCalc[iris[i].clusterID].petalWidth += iris[i].petalWidth;
		dataSizePerCluster[iris[i].clusterID]++;
	}
	//����ÿ����Ⱥ�ڵ���ĸ�����ֵ�ľ�ֵ��Ϊ�µ�����
	for (int i = 0; i < K; i++) {
		if (dataSizePerCluster[i] != 0) {
			centerCalc[i].sepalLength = centerCalc[i].sepalLength / (double)dataSizePerCluster[i];
			centerCalc[i].sepalWidth = centerCalc[i].sepalWidth / (double)dataSizePerCluster[i];
			centerCalc[i].petalLength = centerCalc[i].petalLength / (double)dataSizePerCluster[i];
			centerCalc[i].petalWidth = centerCalc[i].petalWidth / (double)dataSizePerCluster[i];
			printf("cluster %d point cnt:%d\n", i, dataSizePerCluster[i]);//���ÿ����Ⱥ������
			printf("cluster %d center��sepalLength:%.2lf, sepalwidth:%.2lf, petalLength:%.2lf, petalWidth:%.2lf\n", i, centerCalc[i].sepalLength, centerCalc[i].sepalWidth, centerCalc[i].petalLength, centerCalc[i].petalWidth);
		}
		else {
			printf(" cluster %d count is zero\n", i);
		}
	}

	//�Ƚ��¾�����ֵ�Ĳ���������ȣ���ֹͣ��������
	CompareNewOldClusterCenter();

	//���µ����ĵ�ֵ�������Ľṹ����
	for (int i = 0; i < K; i++) {
		clusterCenter[i].sepalLength = centerCalc[i].sepalLength;
		clusterCenter[i].sepalWidth = centerCalc[i].sepalWidth;
		clusterCenter[i].petalLength = centerCalc[i].petalLength;
		clusterCenter[i].petalWidth = centerCalc[i].petalWidth;
		clusterCenter[i].clusterID = i;
	}

	//���¼����µ����ĺ�Ҫ����Ϊÿһ������о��࣬�������ݼ������е��clusterID��Ҫ����Ϊ-1
	for (int i = 0; i < dataNum; i++) {
		iris[i].clusterID = -1;
	}
}

//KMeans�㷨���Ĵ���
void KMeans() {
	int rounds;
	for (rounds = 0; rounds < MAX_ROUNDS; rounds++) {
		printf("\nRounds��%d            \n", rounds + 1);//��ʾ�������
		Partition4AllPointOneCluster();     //��ÿ���㻮�ֵ���������Ĵ�Ⱥ
		CalClusterCenter();                 //���¼����µ�����
		if (isContinue == 0) {              //�ж��Ƿ��������
			printf("\n���� %d �ξ���, ������ɣ�\n", rounds + 1);
			break;   //��������
		}
	}
}


int main() {
	if (Inputs() == false) {     //�ж��������������Ƿ�ɹ�
		return 0;
	}
	InitialCluster();
	KMeans();
	system("pause");
	return 0;
}
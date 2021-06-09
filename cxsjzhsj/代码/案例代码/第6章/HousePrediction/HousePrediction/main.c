#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define Data 380                     //ѵ��������Ŀ
#define TestData 126                 //Ԥ��������Ŀ
#define In 13                        //�������Ԫ����
#define Out 1                        //�������Ԫ����
#define Neuron 40                    //��������Ԫ����
#define TrainC 40000                 //ѵ������
#define WAlta 0.1                    //Ȩֵw��ѧϰ��
#define VAlta 0.2                    //Ȩֵv��ѧϰ��  
double d_in[Data][In];               //�洢Data��������ÿ��������In�����룬Out�����
double d_out[Data][Out];
double t_in[TestData][In];           //�洢TestData��������ÿ��������In�����룬Out�����
double t_out[TestData][Out];
double pre[TestData][Out];           //�洢Ԥ��������ʵ�����
double v[Neuron][In];                //�洢����㵽�������Ȩֵ
double y[Neuron];                    //�洢����������
double w[Out][Neuron];                  //�洢�����㵽������Ȩֵ
double Maxin[In], Minin[In];            //�洢���������������Сֵ
double Maxout[Out], Minout[Out];        //�洢���������������Сֵ
double OutputData[Out];                 //�洢����������
double dw[Out][Neuron], dv[Neuron][In]; //�洢Ȩֵw��v��������
double mse;                             //�洢�������
double rmse;                            //�洢���������

//ѵ���������ݶ���
void ReadData() {
	FILE *fp1, *fp2;
	char ch;       //ÿ������֮����'��'�������һ���ַ��������洢'��'
	if ((fp1 = fopen("in.txt", "rb")) == NULL) {
		printf("���ܴ�in.txt�ļ�\n");
		exit(0);
	}
	//��ȡѵ�����������������������
		for (int i = 0; i < Data; i++) {
			for (int j = 0; j < In; j++) {
				if (j != 0) {
					fscanf(fp1, "%c", &ch);
			}
			fscanf(fp1, "%lf", &d_in[i][j]);
		}
	}
	fclose(fp1);
	if ((fp2 = fopen("out.txt", "rb")) == NULL) {
		printf("���ܴ�out.txt�ļ�\n");
		exit(0);
	}
	for (int i = 0; i < Data; i++) {
		for (int j = 0; j < Out; j++) {
			fscanf(fp2, "%lf", &d_out[i][j]);
		}
	}
	fclose(fp2);
}

/*���ݹ�һ��������ʼ��������*/
void InitBPNetwork() {
	//�Ե�ǰʱ���Ӧ��intֵΪ����������
	srand((int)time(0));
	//�ҵ�ÿһά�����ݵ����ֵ����Сֵ
	for (int i = 0; i < In; i++) {
		Minin[i] = Maxin[i] = d_in[0][i];
		for (int j = 0; j < Data; j++) {
			Maxin[i] = Maxin[i] > d_in[j][i] ? Maxin[i] : d_in[j][i];
			Minin[i] = Minin[i] < d_in[j][i] ? Minin[i] : d_in[j][i];
		}
	}
	//�ҵ�������ݷ��۵����ֵ����Сֵ
	for (int i = 0; i < Out; i++) {
		Minout[i] = Maxout[i] = d_out[0][i];
		for (int j = 0; j < Data; j++) {
			Maxout[i] = Maxout[i] > d_out[j][i] ? Maxout[i] : d_out[j][i];
			Minout[i] = Minout[i] < d_out[j][i] ? Minout[i] : d_out[j][i];
		}
	}
	//ʹ�������С��һ����������
	for (int i = 0; i < In; i++) {
		for (int j = 0; j < Data; j++) {
			d_in[j][i] = (d_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	//ʹ�������С��һ���������
	for (int i = 0; i < Out; i++) {
		for (int j = 0; j < Data; j++) {
			d_out[j][i] = (d_out[j][i] - Minout[i]) / (Maxout[i] - Minout[i]);
		}
	}
	//ʹ�����ֵ��ʼ��������ĸ�Ȩֵ������㵽�������Ȩ�أ�
	for (int i = 0; i < Neuron; i++) {
		for (int j = 0; j < In; j++) {
			v[i][j] = rand() * 2.0 / RAND_MAX - 1;  //Ȩ��ȡ[-1,1]֮��
			dv[i][j] = 0;
		}
	}
	//ʹ�����ֵ��ʼ��������ĸ�Ȩֵ�������㵽������Ȩ�أ�
	for (int i = 0; i < Out; i++) {
		for (int j = 0; j < Neuron; j++) {
			w[i][j] = rand() * 2.0 / RAND_MAX - 1;  //Ȩ��ȡ[-1,1]֮��
			dw[j][i] = 0;
		}
	}
}

//ǰ�򴫲�
void ComputO(int var) {
	double sum;   //����ۼӺ�
	//����������ÿ����Ԫ�����
	for (int i = 0; i < Neuron; i++) {
		sum = 0;
		for (int j = 0; j < In; j++) {
			sum += v[i][j] * d_in[var][j];
		}
		y[i] = 1 / (1 + exp(-1 * sum));
	}
	//���������ÿ����Ԫ�����
	for (int i = 0; i < Out; i++) {
		sum = 0;
		for (int j = 0; j < Neuron; j++) {
			sum += w[i][j] * y[j];
		}
		OutputData[i] = 1 / (1 + exp(-1 * sum));
	}
}

//���򴫲�����Ȩֵ
void BackUpdate(int var) {
	double t;
	//�����������ÿ����Ԫ
	for (int i = 0; i < Neuron; i++) {
		t = 0;
		//�����������������֮��ĸ�Ȩֵ
		for (int j = 0; j < Out; j++) {
			dw[j][i] = WAlta * (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * y[i];
			w[j][i] += dw[j][i];
			t += (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * w[j][i];
		}
		//�����������������֮��ĸ�Ȩֵ
		for (int j = 0; j < In; j++) {
			dv[i][j] = VAlta * t * y[i] * (1 - y[i]) * d_in[var][j];
			v[i][j] += dv[i][j];
		}
	}
}

//ѵ��������
void TrainNetwork() {
	int count = 1;					      //��¼ѵ������
	do {
		mse = 0;					      //�������ֵ����Ϊ0
		//�������ѵ��������һ��ѵ��
		for (int i = 0; i < Data; i++) {
			ComputO(i);				      //ǰ�򴫲�
			BackUpdate(i);			      //���򴫲�������������Ȩֵ
			//���㵥�����������
			for (int j = 0; j < Out; j++) {
				double tmp1 = OutputData[j] * (Maxout[0] - Minout[0]) + Minout[0];
				double tmp2 = d_out[i][j] * (Maxout[0] - Minout[0]) + Minout[0];
				mse += (tmp1 - tmp2) * (tmp1 - tmp2);  //�ۼ�ƽ�����
			}
		}
		mse = mse / Data * Out;		          //������������
		//ÿ��1000��ѵ������ʾһ��ѵ�����Ա�۲�
		if (count % 1000 == 0) {
			printf("%d  %lf\n", count, mse);
		}
		count++;					          //�ۼ�ѵ������
	} while (count <= TrainC && mse >= 1);  //����ѵ�������򾫶ȴﵽҪ�������ѵ��
	printf("ѵ������\n");
}

//������ģ������
void TestNetwork() {
	FILE *fp;
	char ch;
	//�򿪱���������ݼ����ļ�
		if ((fp = fopen("test.txt", "rb")) == NULL) {
			printf("���ܴ�test.txt�ļ�\n");
			exit(0);
	}
	//����������ݼ�
	for (int i = 0; i < TestData; i++) {
		for (int j = 0; j < In + Out; j++) {
			if (j != 0) {
				fscanf(fp, "%c", &ch);
			}
			if (j < In) {
				fscanf(fp, "%lf", &t_in[i][j]);
			}
			else {
				fscanf(fp, "%lf", &t_out[i][j - In]);
			}
		}
	}
	fclose(fp);	//�ر��ļ�
	double sum;
	//�������ݹ�һ������
	for (int i = 0; i < In; i++) {
		for (int j = 0; j < TestData; j++) {
			t_in[j][i] = (t_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	//����ÿһ������������Ԥ����
	for (int k = 0; k < TestData; k++) {
		//�������������
		for (int i = 0; i < Neuron; i++) {
			sum = 0;
			for (int j = 0; j < In; j++) {
				sum += v[i][j] * t_in[k][j];
			}
			y[i] = 1 / (1 + exp(-1 * sum));
		}
		//����������Ԥ����
		sum = 0;
		for (int j = 0; j < Neuron; j++) {
			sum += w[0][j] * y[j];
		}
		//Ԥ��������һ����ԭ
		pre[k][0] = 1 / (1 + exp(-1 * sum)) * (Maxout[0] - Minout[0]) + Minout[0];
		//���Ԥ��ֵ��ʵ��ֵ
		printf("��ţ�%d Ԥ��ֵ��%.2lf ʵ��ֵ��%.2lf\n", k + 1, pre[k][0], t_out[k][0]);
	}
	//������������
	rmse = 0.0;
	for (int k = 0; k < TestData; k++) {
		rmse += (pre[k][0] - t_out[k][0]) * (pre[k][0] - t_out[k][0]);
	}
	rmse = sqrt(rmse / TestData);
	//������ָ����鿴���Ծ���
	printf("rmse��%.4lf\n", rmse);
}

int main(int argc, char const *argw[]) {
	ReadData();       	//����ѵ�����ݼ�
	InitBPNetwork();  	//���ݹ�һ�����������������Ȩֵ�ĳ�ʼ��
	TrainNetwork();   	//ѵ��������
	TestNetwork();	//������ģ������
	return 0;
}
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int data[10000]={0};
int fz[1000000]={0};
void BubbleSort(int a[],int n);
void SelectSort(int a[],int n);
void InsertionSort(int a[],int n);

void MergerSort(int a[],int b[],int high,int low);
void Merge(int a[],int low,int m,int high,int b[]);

void QuickSort(int a[],int low,int high);
int QuickPass(int a[],int low,int high);

//希尔排序
void ShellSort(int *arr, int size);
void check();
void CountSort(int *a, int n);
int main(){
     /*int a[5]={23,43,32,12,0};
     int b[5];
     ShellSort(a,5);
     for(int i=0;i<5;i++){
         printf("%d ",a[i]);

     }*/
     check();
     return 0;
}
void check(){
     FILE *f;
     char ch;
     int count=0;
     clock_t start, stop; //clock_t为clock()函数返回的变量类型
     double duration;
     if((f=fopen("D:\\csjjg\\程序设计综合实践\\排序\\data.txt","r"))==NULL){
         printf("fail to read!");
         exit(1);
     }
     while(!feof(f)){
         ch=fgetc(f);
         while(ch>='0' && ch<='9'){
             data[count]=(ch-'0')+data[count]*10;
             ch=fgetc(f);
             
         }
         count++;
     }
    start=clock();
    CountSort(data,10000);
    //BubbleSort(data,1000);
    //SelectSort(data,1000);
    //InsertionSort(data,1000);
    //MergerSort(data,fz,999,0);
    //QuickSort(data,0,999);
    //ShellSort(data,1000);
 /*FILE *fp = NULL;
    
    fp = fopen("D:\\csjjg\\程序设计综合实践\\排序\\data2.txt","a");//在指定目录下创建.txt文件
	for(int i = 0 ; i < 100000 ; i ++) //产生随机数 
	{
        fprintf(fp,"%d\n",data[i]); //把随机数写进文件
    }
    fclose(fp); //关闭文件
*/
    stop=clock();
    duration=(double)(stop-start)/CLK_TCK; //CLK_TCK为clock()函数的时间单位，即时钟打点
    printf("%f\n",duration);

}
void CountSort(int *a, int n)
{
	int i, j, k;
	for (i = 0; i<n; i++)
		fz[a[i]]++;    /*例如，R[i].key为6时，C[6]++，C[R[i].key]是R[i].key出现的次数*/
	k = 0;
	for (j = 0; j <=n; j++)    /*考察每一个j*/
	for (i = 1; i <= fz[j]; i++)   /*j=R[j].key出现过C[j]个，此即是排序的结果*/
		a[k++] = j;
}
void BubbleSort(int a[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            int flag;
           if(a[j]>a[j+1]){
             flag=a[j];
             a[j]=a[j+1];
             a[j+1]=flag;
           }
        }
    }
}

void SelectSort(int a[],int n){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<a[i]){
                min=j;
            }
        }
        int flag;
        flag=a[i];
        a[i]=a[min];
        a[min]=flag;

    }
}

void InsertionSort(int a[],int n){
    for(int i=1;i<n;i++){
       int x=a[i];
       int j=i-1;
       while(j>=0 && a[j]>x){
           a[j+1]=a[j];
           j--;
       }
       a[j+1]=x;
    }
}

//归并
void MergerSort(int a[],int b[],int high,int low){
    if(low>=high){
        return ;//规模不超过1，不需要排序
    }
    int m= (low + high)/2;
    MergerSort(a,b,m,low);//前一半子序列排序
    MergerSort(a,b,high,m+1);//后一半子序列排序
    Merge(a,low,m,high,b);//归并两段有序子序列
    for(int i=low;i<=high;i++){//移动回原数组
        a[i]=b[i];
    }

}
void Merge(int a[],int low,int m,int high,int b[]){
    int i=low;//前段有序子序列起点
    int j=m+1;//后段有序子序列起点
    int k=i;//归并结果起始下标
    while(i<=m && j<=high){
        if(a[i]<a[j]){
            b[k++]=a[i++];
        }else{
            b[k++]=a[j++];
        }
    }
    while(i<=m){
        b[k++]=a[i++];
    }   
    while(j<=high){
        b[k++]=a[j++];
    } 
}
//快速排序
void QuickSort(int a[],int low,int high){
    if (low>=high)
    {
        return;
    }
    int pivot=QuickPass(a,low,high);
    QuickSort(a,low,pivot-1);
    QuickSort(a,pivot+1,high);

    }
int QuickPass(int a[],int low,int high){
    int x=a[low];
    while(low<high){
        while(low<high && x<=a[high])
        high--;
        if(low==high){
            break;
        }
        a[low++]=a[high];
        while(low<high && x>=a[low])
        low++;
        if(low==high){
            break;
        }
        a[high--]=a[low];

    }
    a[low]=x;
    return low;
}

//希尔排序

void ShellSort(int *a, int len)
{
    int i, j, k, tmp, gap;  // gap 为步长
    for (gap = len / 2; gap > 0; gap /= 2) {  // 步长初始化为数组长度的一半，每次遍历后步长减半,
    	for (i = 0; i < gap; ++i) { // 变量 i 为每次分组的第一个元素下标 
	        for (j = i + gap; j < len; j += gap) { //对步长为gap的元素进行直插排序，当gap为1时，就是直插排序
	            tmp = a[j];  // 备份a[j]的值
	            k = j - gap;  // j初始化为i的前一个元素（与i相差gap长度）
	            while (k >= 0 && a[k] > tmp) {
	                a[k + gap] = a[k]; // 将在a[i]前且比tmp的值大的元素向后移动一位
	                k -= gap;
	            }
	            a[k + gap] = tmp; 
	        }
	    }
    }
}
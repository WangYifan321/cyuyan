#include<stdio.h>
int a[100];

void CountSort(int *a, int n)
{
	int i, j, k;
	int C[101] = { 0 };  /*用于计数的C数组的所有元素初值为0*/
	for (i = 0; i<n; i++)
		C[a[i]]++;    /*例如，R[i].key为6时，C[6]++，C[R[i].key]是R[i].key出现的次数*/
	k = 0;
	for (j = 0; j <=100; j++)    /*考察每一个j*/
	for (i = 1; i <= C[j]; i++)   /*j=R[j].key出现过C[j]个，此即是排序的结果*/
		a[k++] = j;
}
int  main(){
    int b[13]={1,2,3,4,4,4,4,4,4,4,44,4,4};
    CountSort(b,13);
    for(int i=0;i<13;i++){
        printf("%d\n",b[i]);
    }
    return 0;
}
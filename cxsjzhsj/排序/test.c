#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
 
int main()
{
	srand(time(NULL));//先种种子 
	int i,j,s=0;
	FILE *fp = NULL;
    
    fp = fopen("D:\\csjjg\\程序设计综合实践\\排序\\data.txt","a");//在指定目录下创建.txt文件
	for(i = 0 ; i < 10000 ; i ++) //产生随机数 
	{
		j = rand()%100000 ;
        fprintf(fp,"%d\n",j); //把随机数写进文件
    }
    fclose(fp); //关闭文件
    return 0;
	}
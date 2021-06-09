#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void maxmin(int d[],int left,int right,int *max,int *min);
int main(){
    int d[10000];
    int i=0;
    while(scanf("%d",&d[i])!=EOF){
        i++;
    }
    int max,min;
    maxmin(d,0,i-1,&max,&min);
    printf("%d,%d",min,max);
    return 0;
     
}
void maxmin(int d[],int left,int right,int *max,int *min){
    int max1,min1;
    if(left == right){
        *max=d[left];
        *min=d[left];
    }else if(left == right-1){
        if(d[left]>d[right]){
            *max=d[left];
            *min=d[right];
        }else{
            *max=d[right];
            *min=d[left];
        }

    }else{
        int mid = (left + right)/2;
        maxmin(d,left,mid,max,min);
        maxmin(d,mid+1,right,&max1,&min1);
        if(*max<max1){
            *max=max1;
        }
        if(*min>min1){
            *min=min1;
        }

    }
}
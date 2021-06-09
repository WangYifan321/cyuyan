#include<stdio.h>
int main(){
    int d,p;//钻石数，人数
    scanf("%d %d",&d,&p);
    if(p == 0){
        printf("0");
    }else if(p == 3){
        printf("%d",d-1);

    }else{
        printf("%d",d-p/2-1);
    }
}
#include<stdio.h>
int main(){
    int i;
    int flag;
    scanf("%d",&i);
    while(i--){
    char a[500],b[500];
    scanf(" %s %s",a,b);
    int len;
    for(len=0;a[len]!='\0';len++){

    }
    int len2;
    for(len2=0;b[len2]!='\0';len2++){

    }
    int len3 = len;
    while(len3--){
        if(len3 != len-1){
                    char p = a[0];
        for(int q=0;q<len-1;q++){
           a[q] = a[q+1];
        }
        a[len-1] = p;//除了第一次都要旋转字符串
        }
        int x=0,y=0;
        flag=0;
        while(x<=len2 && y<=len){
            if(b[x]==a[y]){++x;++y;}
            else{x=x-y+2;y=1;}
        }
        if(y>len){
             flag=1;
            printf("YES\n");
           
            break;
        }//bf算法
        }
      if(flag == 0){
        printf("NO\n");
      }
    }
    
    return 0;
}
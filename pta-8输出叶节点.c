#include<stdio.h>
#include<stdlib.h>
struct node{
    int left;
    int right;
}t[20];
int main(){
    int n,check[11]={0};
    scanf("%d",&n);
    char x1,x2;
    getchar();
    for(int i=0;i<n;i++){
       scanf("%c %c",&x1,&x2);
        if(x1 == '-'){
            t[i].left = -1;
            
        }else{
            t[i].left = x1 - '0';
            check[t[i].left] = 1;//为各个输入的点做个标记，最后没有输入标记的点即为根节点
        }
        if(x2 == '-'){
            t[i].right = -1;
        }else{
            t[i].right = x2 - '0';
            check[t[i].right] = 1;
        }
        getchar();
    }
      int root;
      for(int i =0 ;i<n;i++){
          if(check[i] == 0){
              root = i;
              break;

          }
      }
      int a[20],l,f;
      a[0] = root;
      l++;
      f=0;
      while(f!=(n-1)){
        if(t[a[f]].left!=-1){
            a[l] = t[a[f]].left;
            l++;
        }
        if(t[a[f]].right!=-1){
            a[l] = t[a[f]].right;
            l++;
        }
        f++;
      }
    int flag=0;
    for(int i = 0;i<n;i++){
      if(t[a[i]].left == -1 && t[a[i]].right==-1){
         if(flag == 0){
             printf("%d",a[i]);
             flag=1;
         }else{
             printf(" %d",a[i]);
         }
      }
    }
}
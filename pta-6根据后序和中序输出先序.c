#include<stdio.h>
void getpre(int a[],int b[],int n){
    if(n<=0){
        return ;
    }
    int root = a[n-1];
    int i;
    for(i=0;i<n;i++){
        if(b[i] == root){
            break;
        }
    }
    printf(" %d",root);
    getpre(a,b,i);
    getpre(a+i,b+i+1,n-i-1);//n-i+1 右面还剩多少个元素

}
int main(){
    int n;
    scanf("%d",&n);
    int a[40],b[40];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    printf("Preorder:");
    getpre(a,b,n);
    printf("\n");
}
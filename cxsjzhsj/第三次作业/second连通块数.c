//dfs,bfs,并查集
//https://leetcode-cn.com/problems/number-of-islands/solution/number-of-islands-shen-du-you-xian-bian-li-dfs-or-/
#include<stdio.h>
void dfs(int m[][52],int flag[][52] ,int i,int j,int a,int b);

int  main(){
    int a,b;
    scanf("%d %d",&a,&b);
    int m[52][52];
    int flag[52][52]={0};
    for(int i=0;i<a;i++){
       for(int j=0;j<b;j++){
           scanf("%d",&m[i][j]);
       }
    }
    int count=0;
    for(int i=0;i<a;i++){
       for(int j=0;j<b;j++){
           if(flag[i][j]==0){
           dfs(m,flag,i,j,a,b);
           count++;
           }
       }
    }
    printf("%d",count);
}  
    void dfs(int m[][52],int flag[][52] ,int i,int j,int a,int b){
        if(i<0 || j<0 || i>=a || j>=b || flag[i][j]==1){
            return ;
        }
        flag[i][j]=1;
        if(m[i][j]==m[i+1][j])
        dfs(m,flag,i+1,j,a,b);
        if(m[i][j]==m[i][j+1])
        dfs(m,flag,i,j+1,a,b);
        if(m[i][j]==m[i-1][j])
        dfs(m,flag,i-1,j,a,b);
        if(m[i][j]==m[i][j-1])
        dfs(m,flag,i,j-1,a,b);
    }

#include<stdio.h>
# define MAX 1000000
int num[1001],sumnum[1001];//每个城市救援队的数目，到某一个点总的救援队的数目
int cnt[1001];//最短路径的条数
int a[1001][1001];
int pre[1001];
int flag[1001]={0};
int n,m,s,d;//城市个数，道路条数，始发点，终点

void Dijkstra(){
    flag[s]=1;
    for(int i =0;i<n;i++){
       int min = MAX;
       int f = -1;
       for(int j = 0;j<n;j++){
           if(flag[j]==0&&a[s][j]<min){
               min = a[s][j];
               f=j;
           }
       }
       if(f == -1)break;
       else 
       flag[f] = 1;
       for(int j = 0;j<n;j++){
           if(flag[j]==0&&a[s][f]+a[f][j]<a[s][j]){
               a[s][j] = a[f][j]+a[s][f];
               pre[j]=f;
               sumnum[j]=sumnum[f]+num[j];
               cnt[j] = cnt[f];
           }else if(flag[j]==0&&a[s][f]+a[f][j] == a[s][j]){
               cnt[j]=cnt[f]+cnt[j];
               if(sumnum[j]<sumnum[f]+num[j]){
                   pre[j]=f;
                   sumnum[j]=sumnum[f]+num[j];
               }
           }
       }

       
    }
}
int main(){
    scanf("%d %d %d %d",&n,&m,&s,&d);
    for(int i=0;i<n;i++){
        scanf("%d",&num[i]);
        sumnum[i] = num[i];
        cnt[i] = 1;
    }
    for(int i = 0;i<n;i++)
    for(int j = 0;j<n;j++){
        if(i!=j){
            a[i][j] = MAX;
        }
    }
    for(int i = 0;i<m;i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        a[x][y] = a[y][x] = z;
    }
    Dijkstra();
    printf("%d %d\n",cnt[d],sumnum[d]+num[s]);
    int path[1001];
    int j=d;
    int x=0;
    printf("%d ",s);
    while(pre[j]!=s){
        path[x++]=pre[j];
        j=pre[j];
    }
    for(int r = x-1;r>=0;r--){
        printf("%d ",path[r]);
    }
    printf("%d",d);

}
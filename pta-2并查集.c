#include<stdio.h>
    int fa[100000],rank[100000];

    void init(int n)
    {
        for(int j=1;j<=n;j++){
            fa[j]=j;
            rank[j]=1;
        }
    }
    //路径压缩
    int find(int x){
        if(x==fa[x]){
            return x;
        }else{
            fa[x]=find(fa[x]);
            return fa[x];
        }
    }
 /*   void merge(int i,int j){
        int x = find(i);
        int y = find(j);
        if(rank[x]<=rank[y]){
            fa[x]=y;
        }else{
            fa[y]=x;
        }
        if(rank[x]==rank[y] && x!=y){
            rank[y]++;
        }
    }*/
    void merge(int i,int j){
        int x = find(i);
        int y = find(j);
        if(x!=y){
            fa[x]=y;
            rank[y]+=rank[x];
        }
    }
    int main(){
        int m,n;
        scanf("%d %d",&n,&m);
        init(n);
                    int x;
        while(m--){

            scanf("%d",&x);
            int num[x+1];
            for(int i=1;i<=x;i++){
                scanf("%d",&num[i]);
            }
            for(int i=1;i<=x;i++){
                for(int j=i+1;j<x;j++){
                    merge(num[i],num[j]);
                }
            }
        }
        int max=0;
        for(int i=1;i<=n;i++){
            if(rank[i]>max){
                max=rank[i];
            }
        }
        printf("%d",max);

    }
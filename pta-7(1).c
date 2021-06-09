#include<stdio>
#include<iostream>
using namespace std;
#define inf 1000000
int a[1001][1001];
int cnt[1001],exs[1001]={0},cf[1001],ccf[1001],pre[1001];
//最短路径条数，各城市是否经过，各城市的救援队数量，到达该城市时所召集的所有救援队数量，到达该城市前经过的城市编号
int n,m,s,d;
int Dijkstra()
{
    cnt[s]=1;//开始时路径条数为1
    exs[s]=1;//当前在出发城市
    for(int i=0;i<n;i++){
        int min=inf,f=-1;
        for(int j=0;j<n;j++){
            if(exs[j]==0&&a[s][j]<min){//寻找下一个距离最短的城市
                min=a[s][j];
                f=j;//做好下一城市编号的标记
            }
        }
        if(f==-1)break;//与其他未经过的城市不连通，退出循环
        else exs[f]=1;//到达下一城市
        for(int j=0;j<n;j++){
            if(exs[j]==0&&a[s][j]>a[s][f]+a[f][j]){//到达某一城市的最短路径
                a[s][j]=a[s][f]+a[f][j];//最短路径更新
                pre[j]=f;//记录上一个城市编号
                cnt[j]=cnt[f];//拷贝到达上一个城市时的最短路径条数
                ccf[j]=ccf[f]+cf[j];//到达某城市召集的全部救援队数量
            }
            else if(exs[j]==0&&a[s][j]==a[s][f]+a[f][j]){//发现其他的最短路径
                cnt[j]=cnt[j]+cnt[f];//更新到达当前城市时的最短路径条数
                if(ccf[j]<ccf[f]+cf[j]){//最多救援队数量更新
                    pre[j]=f;//记录所经过的上一个城市编号
                    ccf[j]=ccf[f]+cf[j];//更新救援队总数
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m>>s>>d;
    for(int i=0;i<n;i++){
        cin>>cf[i];
        ccf[i]=cf[i];
        cnt[i]=1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j)a[i][j]=a[j][i]=inf;//初始化（双向图）
        }
    }
    for(int i=0;i<m;i++){
        int q,w,e;
        cin>>q>>w>>e;
        a[q][w]=a[w][q]=e;
    }
    Dijkstra();
    cout<<cnt[d]<<" "<<ccf[d]+cf[s]<<endl;
    int road[1001];
    int x=0,t=d;
    while(pre[t]!=0){//所经历的城市的从后往前的顺序
        road[x++]=pre[t];
        t=pre[t];
    }
    cout<<s;//出发地
    for(int i=x-1;i>=0;i--)
        cout<<" "<<road[i];
    cout<<" "<<d;//目的地
}
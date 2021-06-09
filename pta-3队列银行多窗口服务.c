#include<stdio.h>
typedef struct person
{
    int t,p;//到达时间和处理时间
}sq;
sq q[1005];
int main(){
    int n,l,r;
    scanf("%d",&n);
        l=r=0;//队头队尾
        for(int i=0;i<n;i++){
            scanf("%d %d",&q[r].t,&q[r].p);
            if(q[r].p>60){q[r].p=60;}
            r++;
        }
        int k;//一共有k个窗口
        scanf("%d",&k);
        int sum[15]={0},time[15]={0};//每个窗口的服务人数，窗口到什么时候空闲
        int sumwait=0,maxwait=0,wait=0;
        while(l<r){
            int flag=0,minn=9999,imin=0;
            for(int i=0;i<k;i++){
              if(q[l].t>=time[i]){
                  time[i]=q[l].p+q[l].t;
                  l++;//指向队列的下一个元素
                  sum[i]++;//窗口服务的人数加加
                  flag=1;
                  break;
              }
              if(minn>time[i]){
                  minn=time[i];
                  imin=i;
              }

            }
            if(!flag){
                wait=minn-q[l].t;
                if(maxwait<wait){
                    maxwait=wait;
                }
                sumwait+=wait;
                sum[imin]++;
                time[imin]=minn+q[l].p;
                l++;
            }
        }
        //求最大的完成时间
        int last=0;
        for(int i=0;i<k;i++){
            if(time[i]>last){last=time[i];}
        }
        printf("%.1lf %d %d\n",1.0*sumwait/n,maxwait,last);
        for(int i=0;i<k;i++){
            printf("%d",sum[i]);
            if(i==k-1)
                printf("\n");
                else printf(" ");
                
            
        }
    
    return 0;
}


#include<stdio.h>
#include<math.h>
struct node{
    int data,next;
}num[110000];
int main(){
    int pl,n;
    scanf("%d %d",&pl,&n);
    int a,b,c;
    for(int i = 0;i<n;i++){
        scanf("%d %d %d",&a,&b,&c);
        num[a].data = b;
        num[a].next = c;
    }
    int p1[100000],p2[100000],p3[100000]={0};
    int t1=0,t2=0;
    for(int i = 0; i < n; i++){
        int x=fabs(num[pl].data);
       if(p3[x] == 0){
          p3[x]=1;
          p1[t1++]=pl;
       }else{
          p2[t2++]=pl;
       }
       pl = num[pl].next;
       if(pl==-1){
           break;
       }
    }
    for(int i=0;i<t1;i++)
    {
        if(i==t1-1){
        printf("%05d %d -1\n",p1[i],num[p1[i]].data);
        }else{
           printf("%05d %d %05d\n",p1[i],num[p1[i]].data,p1[i+1]);
        }
    }
        for(int i=0;i<t2;i++)
    {
        if(i==t2-1){
        printf("%05d %d -1\n",p2[i],num[p2[i]].data);
        }else{
           printf("%05d %d %05d\n",p2[i],num[p2[i]].data,p2[i+1]);
        }
    }
    
}
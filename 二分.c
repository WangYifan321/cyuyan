#include<string>
#include<iostream>
#include<stack>
#include<map>
#include<vector>
using namespace std;
void fun1()
{
    //贪心模拟现实
    vector<deque<int>> h;
    int n,x;
    cin>>n;
    int t=n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        int k=-1;
        for(int j=0;j<h.size();j++){
            while(h[j][0]==t){h[j].pop_front();t--;}
            if(h[j].empty()) continue;
            if(x<h[j].back())
            k=k==-1?j:h[k].back()>h[j].back()?j:k;
        }
        if(k==-1)
        {
            for(int j=0;j<h.size();j++)
            if(h[j].empty()){
                k=j;
                break;
            }
        }
        if(k==-1)
        {
            h.push_back(deque<int>());
            k=h.size()-1; 
        }
        h[k].push_back(x);   
    }
    cout<<h.size()<<endl;
}
int BinarySearch(vector<int> &h,int x)
{
    int left=0,right=h.size()-1;
    int k;
    while(left<=right)
    {
        k=(left+right)/2;
        if(h[k]>x)
        {
            if(k==0||h[k-1]<x) return k?k:0;
            right=k-1;
        }
        else
        {
            left=k+1;
        }
    }
    throw "没有这玩意";
}
void fun2()
{
    //根据fun1其实能发现不需要pop_front,可以假装已经pop,最大值的头是不影响后面的输出的,且每次只需要看back，即每列最小值
    vector<int> h;
    int n,x;
    cin>>n;
    while(n--)
    {
        bool t=true;
        cin>>x;
        if(h.empty()) {h.push_back(x); continue;}
        if(x>h[h.size()-1]){h.push_back(x); continue;}
        h[BinarySearch(h,x)]=x;
    }
    cout<<h.size();
}
int main()
{
    fun2();
    return 0;
}
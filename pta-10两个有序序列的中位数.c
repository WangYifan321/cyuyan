#include<stdio.h>

int bin_search(int a[],int aleft,int aright,int b[],int bleft,int bright){
    int al = 0,ar = 0,bl = 0,br = 0;
    int aleft1 = aleft;
    int bleft1 = bleft;
    int aindex = (aleft+aright)/2,bindex = (bleft+bright)/2,amid=a[aindex],bmid=b[bindex];
    if(amid == bmid){
        return amid;
    }
    if(aleft>=aright && bleft>=bright){
        return amid>bmid ? bmid :amid;
    }
    if(amid < bmid){
        aleft = aindex;
        aright = aright;
        bleft = bleft;
        bright = bindex;
        if((aright-aleft1+1) % 2 == 0){
            aleft = aindex+1;
        }

    }else if(amid > bmid){
        aright = aindex;
        aleft = aleft;
        bleft = bindex;
        bright = bright;
        if((bright-bleft1+1) % 2 == 0){
            bleft = bindex +1;

        }
    }

    return bin_search(a,aleft,aright,b,bleft,bright);

}
int main(){
    int n;
    scanf("%d",&n);
    int a[100000]={0},b[100000]={0};
    for(int i = 0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int mid = bin_search(a,0,n-1,b,0,n-1);
    printf("%d\n",mid);
    return 0;
}
/*
#include<stdio.h>

int bin_search(int a[],int aleft,int aright,int b[],int bleft,int bright){
    int al = 0,ar = 0,bl = 0,br = 0;

    int aindex = (aleft+aright)/2,bindex = (bleft+bright)/2,amid=a[aindex],bmid=b[bindex];
    if(amid == bmid){
        return amid;
    }
    if(aleft>=aright && bleft>=bright){
        return amid>bmid ? bmid :amid;
    }
    if(amid < bmid){
        al = aindex;
        ar = aright;
        bl = bleft;
        br = bindex;
        if((bright-bleft+1) % 2 == 0){
            al = aindex+1;
        }

    }else if(amid > bmid){
        ar = aindex;
        al = aleft;
        bl = bindex;
        br = bright;
        if((aright-aleft+1) % 2 == 0){
            bl = bindex +1;

        }
    }

    return bin_search(a,al,ar,b,bl,br);

}
int main(){
    int n;
    scanf("%d",&n);
    int a[100000]={0},b[100000]={0};
    for(int i = 0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int mid = bin_search(a,0,n-1,b,0,n-1);
    printf("%d\n",mid);
    return 0;
}

*/
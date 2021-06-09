
#include<stdio.h>
int hanno(int n,char a,char b,char c){
	if(n==1){
		printf("%c -> %c\n",a,c);
	}else{
		hanno(n-1,a,c,b);
		hanno(1,a,b,c);
		hanno(n-1,b,a,c);
	}
	return 0;
}
int main(){
	int n;
	scanf("%d",&n);
	hanno(n,'a','b','c');
	return 0;
}

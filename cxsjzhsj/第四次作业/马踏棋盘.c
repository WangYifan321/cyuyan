#include <stdio.h>
#define X 8
#define Y 8
int road[X][Y];//存储某个点是第几步
int nextxy(int *x,int *y,int count)
{
	switch(count)
	{
	case 0:
		if(*x+2<X && *y-1>=0 && road[*x+2][*y-1]==0)
		{
			*x+=2;
			*y-=1;
			return 1;
		}
		break;
	case 1:
		if(*x+2<X && *y+1<Y && road[*x+2][*y+1]==0)
		{
			*x+=2;
			*y+=1;
			return 1;
		}
		break;
	case 2:
		if(*x+1<X && *y-2>=0 && road[*x+1][*y-2]==0)
		{
			*x+=1;
			*y-=2;
			return 1;
		}
		break;
	case 3:
		if(*x+1<X && *y+2<Y && road[*x+1][*y+2]==0)
		{
			*x+=1;
			*y+=2;
			return 1;
		}
		break;
	case 4:
		if(*x-2>=0 && *y-1>=0 && road[*x-2][*y-1]==0)
		{
			*x-=2;
			*y-=1;
			return 1;
		}
		break;
	case 5:
		if(*x-2>=0 && *y+1<Y && road[*x-2][*y+1]==0)
		{
			*x-=2;
			*y+=1;
			return 1;
		}
		break;
	case 6:
		if(*x-1>=0 && *y-2>=0 && road[*x-1][*y-2]==0)
		{
			*x-=1;
			*y-=2;
			return 1;
		}
		break;
	case 7:
		if(*x-1>=0 && *y+2<Y && road[*x-1][*y+2]==0)
		{
			*x-=1;
			*y+=2;
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}
 
//输出计算出来的走法，输出的矩阵元素值表示走的第road[i][j]步
void print()
{
	int i,j;
	for(i=0;i<X;++i)
	{
		for(j=0;j<Y;++j)
		{
			printf("%2d\t",road[i][j]);
		}
		printf("\n");
	}
	printf("\n"); 
}
 
//tag为标记变量,每走一步，tag+1
int TravelroadBoard(int x,int y,int tag)
{
	int x1=x,y1=y,flag=0;
        int count=0;  // 对现在的位置，每次从位置0出开始走
	road[x][y]=tag;
	if(tag==X*Y)
	{
		print();//打印棋盘
		return 1;
	}
	//确定成功走出第一步
	flag=nextxy(&x1,&y1,count);
	while(flag==0 && count<=7)
	{
		++count;  // 若行不通，则切换走的方向
		flag=nextxy(&x1,&y1,count);
	}
	while(flag)
	{
		 if(TravelroadBoard(x1,y1,tag+1))  // 成功走完全部
			 return 1;
		 // 未成功走完，换个方向重新开始走
		 x1=x;y1=y;
		 ++count;
		 flag=nextxy(&x1,&y1,count);
	     while(flag==0 && count<7)
	     {
		     ++count;
		     flag=nextxy(&x1,&y1,count);
	     }
	}
	if(flag==0)
	{
		road[x][y]=0;
	}
	return 0;
}
 
int main()
{
	int i,j;
	for(i=0;i<X;++i)
	{
		for(j=0;j<Y;++j)
			road[i][j]=0;
	}
	if(!TravelroadBoard(2,0,1))  //起始点(2,0)
	{
		printf("抱歉，马踏棋盘失败鸟~\n");
	}
	return 0;
}
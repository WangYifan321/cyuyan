#include <stdio.h >  
#include <process.h >

 /*定义符号常量*/
 #define  INT_MAX 10000
 #define  n 10

 int  cost[n][n]; /* 边的值*/
 int  shortest[n][n]; /* 两点间的最短距离*/
 int  path[n][n]; /* 经过的景点*/
 int startPoint, endPoint;
 int dfs_path[100], visited[100] = { 0 };
 int pathNumber = 0;
 int i,j; 
 char k; 
 int count = 0;

 void  introduce();
 int  shortestdistance();
 void  floyed(); 
 void  display( int  i, int  j);
void DFS(int nowPoint, int count);
int first(int x);
int next(int x,int now);

 void  main() 
 {

    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            cost[i][j]=INT_MAX; 
    cost[1][2]=cost[2][1]=2;
    cost[2][3]=cost[3][2]=1;
    cost[2][4]=cost[4][2]=2;
    cost[3][4]=cost[4][3]=4;
    cost[1][4]=cost[4][1]=5;
    cost[2][5]=cost[5][2]=3;
    cost[5][10]=cost[10][5]=8;
    cost[5][6]=cost[6][5]=2;
    cost[6][7]=cost[7][6]=1;
    cost[7][8]=cost[8][7]=3;
    cost[7][9]=cost[9][7]=3;
    cost[8][9]=cost[9][8]=4;
    cost[1][1]=cost[2][2]=cost[3][3]=cost[4][4]=cost[5][5]=0; 
    cost[6][6]=cost[7][7]=cost[8][8]=cost[9][9]=cost[10][10]=0;
 
        printf("----------------欢迎使用杭州电子科技大学导游系统!---------------- \n");
        printf("1.景点信息查询………请按 i (introduc)键 \n");
        printf("2.景点最短路径查询…请按 s (shortestdistance)键,景点所有路径查询请按a(allpath)键 \n");
        printf("3.退出系统……………请按 e (exit)键 \n");
        printf("学校景点列表: \n");
        printf("1:学校大门  \n");
        printf("2:行政楼    \n");
        printf("3:体育馆   \n");
        printf("4:一教    \n");
        printf("5:二教 \n");
        printf("5:二教 \n");
        printf("6:学活   \n");
        printf("7:六教   \n");
        printf("8:一餐    \n");
        printf("9:图书馆  \n");
        printf("10:美食城 \n");
        printf("请选择服务:\n");

        while(1){
                    scanf(" %c",&k); 
        switch(k) 
        { 
            case 'a':
	            printf("请输入要找到路径的起点和终点:");
                scanf("%d%d", &startPoint, &endPoint);
	            DFS(startPoint, count);
            case 'i':
                printf("进入景点信息查询:");
                introduce();
                printf("请继续输入i或s或e（退出）");
                break; 
            case 's':
                printf("进入最短路径查询:");
                shortestdistance();
                printf("请继续输入i或s或e（退出）");
                break; 
            case 'e':
                exit(0); 
            default:
                printf("输入信息错误！请输入字母i或s或e. ");
                break; 
        } 
    } 
 }
/*main*/

 void  introduce()
 {/*景点介绍*/
    int a;
    printf("您想查询哪个景点的详细信息?请输入景点编号:");
    scanf("%d",&a);
    switch(a)
    {
        case 1: 
            printf("1:学校大门 　　学校的正门，号称亚洲第一大校门，气势宏伟。 ");break;
        case 2: 
            printf("2:行政楼 　　校长、教务处等的办公所在地。 ");break; 
        case 3: 
            printf("3:体育馆 　　2020年击剑场馆，还包括排球场、篮球场、网球场。 ");break; 
        case 4: 
            printf("4:一教 　　计算机学院、通信学院所在地。 ");break; 
        case 5: 
            printf("5:二教 　　自动化学院、电子信息学院所在地。 ");break; 
        case 6: 
            printf("6:学活 　　学生的主要活动场所之一，包括校学生会、社联、吉协、羽毛球场地等等。 ");break; 
        case 7: 
            printf("7:六教 　　考研教室所在地、拥有大量的自习室，大多数基础学科的上课地。 ");break; 
        case 8: 
            printf("8:一餐 　　学校的清真餐厅，三楼为乒乓球场馆，价格实惠。 ");break; 
        case 9: 
            printf("9:图书馆 　　学校最高的楼。 ");break; 
        case 10: 
            printf("10:美食城 　　学校最大的食堂，环境优美，菜品丰厚，深受学生的欢迎。 ");break; 
        default:
            printf("景点编号输入错误！请输入1->10的数字编号！ "); break; 
    }
} 

 int  shortestdistance()
 {/*要查找的两景点的最短距离*/
    int i,j; 
    printf("请输入要查询的两个景点的编号(1->10的数字编号并用','间隔):");
    scanf("%d,%d",&i,&j);
    if(i>n||i<=0||j>n||j<0)
    {
        printf("输入信息错误！ ");
        printf("　　请输入要查询的两个景点的编号(1->10的数字编号并用','间隔): ");
        scanf("%d,%d",&i,&j);
    }
    else
    {
        floyed();
        display(i,j);
    }
    return 1;
}

 void  floyed()
 {/*用floyed算法求两个景点的最短路径*/
    int i,j,k; 
    for(i=1;i<=n;i++) 
        for(j=1;j<=n;j++) 
        {
            shortest[i][j]=cost[i][j];
            path[i][j]=0; 
        }
    for(k=1;k<=n;k++) 
        for(i=1;i<=n;i++) 
            for(j=1;j<=n;j++)
                if(shortest[i][j]>(shortest[i][k]+shortest[k][j])) 
                {/*用path[][]记录从i到j的最短路径上点j的前驱景点的序号*/
                    shortest[i][j]=shortest[i][k]+shortest[k][j];
                    path[i][j]=k;
                    path[j][i]=k;
                } 
} 

 void  display( int  i, int  j)
 {/* 打印两个景点的路径及最短距离 */
    int a,b;
    a=i;
    b=j;
    printf("您要查询的两景点间最短路径是: ");
    if(shortest[i][j]!=INT_MAX)
    {
        if(i<j)
        { 
            printf("%d",b);
            while(path[i][j]!=0)
            {/* 把i到j的路径上所有经过的景点按逆序打印出来*/
                printf("<-%d",path[i][j]);
                if(i<j)
                    j=path[i][j]; 
                else 
                    i=path[j][i];
            } 
            printf("<-%d",a);
            printf(" "); 
            printf("(%d->%d)最短距离是:%d米 ",a,b,shortest[a][b]);
        }
        else 
        {
            printf("%d",a);
            while(path[i][j]!=0)
            {/* 把i到j的路径上所有经过的景点按顺序打印出来*/
                printf("->%d",path[i][j]);
                if(i<j)
                    j=path[i][j]; 
                else 
                    i=path[j][i]; 
            } 
            printf("->%d",b);
            printf(" "); 
            printf("(%d->%d)最短距离是:%5d米 \n",a,b,shortest[a][b]);
        } 
    } 
    else
        printf("输入错误！不存在此路！ ");
    printf(" ");
}

int first(int x)
{
	for (i = 1; i <= 10; i++)
	{
		if (cost[x][i] < INT_MAX && n!=i)
			return i;
	}
	printf("起点为故障点，请输入一个不为故障点的起点\n");
	return 0;
}

//
//返回第n个节点相连的比now节点序号大的节点,
//
int next(int x, int now)
{
	for (i = now + 1; i <= 10; i++)
	{
		if (cost[x][i] < INT_MAX && n!=i)
			return i;
	}
	return 1000;  //当找不到节点n的下一个节点，返回1000
}
//
//DFS寻找所有路径 
//count为从起点到当前节点经过的节点数,pathNumber为寻找到的路径条数 
void DFS(int nowPoint, int count)
{
	visited[nowPoint] = 1;
	dfs_path[count++] = nowPoint;
	if (nowPoint == endPoint && (count) >= 1)
	{
		pathNumber++;
		printf("这两个城市间第%d条简单路径为: ", pathNumber);
		for (i = 0; i < (count)-1; i++)
		{
			printf("%d-->", path[i] + 1);
		}
		printf("%d\n", path[(count)-1] + 1);
	}
	else
	{
		int k;
		for (k = first(nowPoint); k <=10; k = next(nowPoint, k))
		{
			if (visited[k] == 0)
				DFS(k, count);
		}
	}
	visited[nowPoint] = 0;  //算法关键，回溯，将访问过状态变为未访问状态 
	(count)--;
	return;
}
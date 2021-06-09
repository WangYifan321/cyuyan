#include <stdio.h>

#define MaxN 20
struct S8Queen
{
    int   N;
    int   iMatrixA [MaxN][MaxN]; //棋盘矩阵，便于输出
    int   iColPerRowA [MaxN]; //每行皇后摆放列号，便于检查
    int   iSolutionCount;
};

//初始化问题
void InitProbelm (struct S8Queen  *pQueenProblem, int n);
//打印一个解
void PrintSolution (struct S8Queen  *pQueenProblem);
//试探第i个皇后摆放
void Try (struct S8Queen  *pQueenProblem, int i);
//检查目前第i个皇后摆放是否ok
int CheckOk (struct S8Queen  *pQueenProblem, int i);

int main ()
{
    int n;
    while (1)
    {
        printf ("请输入棋盘大小(4~20):\n");
        scanf ("%d", &n);
        if (n <4 || n > 20)
            break;
        struct S8Queen  theQueenProblem;
        InitProbelm (&theQueenProblem, n);
        Try (&theQueenProblem, 1);
    }
    return 0;
}

//初始化问题
void InitProbelm (struct S8Queen  *pQueenProblem, int n)
{
    pQueenProblem->N = n;
    int i, j;
    pQueenProblem->iSolutionCount = 0;
    for (i = 0; i < pQueenProblem->N; ++i)
        for (j = 0; j < pQueenProblem->N; ++j)
            pQueenProblem->iMatrixA [i][j] = 0;
}
//打印一个解
void PrintSolution (struct S8Queen  *pQueenProblem)
{
    int i, j;
    printf ("Solution %d:\n", pQueenProblem->iSolutionCount);
    for (i = 0; i < pQueenProblem->N; ++i)
    {
        for (j = 0; j < pQueenProblem->N; ++j)
            printf ("%1d", pQueenProblem->iMatrixA [i][j]);
        printf ("\n");
    }
    printf ("\n");
}
//试探第i个皇后摆放
void Try (struct S8Queen  *pQueenProblem, int i)
{
    if (i > pQueenProblem->N)
    {
        ++ pQueenProblem->iSolutionCount;
        PrintSolution (pQueenProblem);
        return; //继续回溯
    }
    int j;
    for (j = 1; j <= pQueenProblem->N; ++j)
    {
        pQueenProblem->iMatrixA [i-1][j-1] = 1; //试探摆放在j列
        pQueenProblem->iColPerRowA [i-1] = j;
        if (CheckOk (pQueenProblem, i))
            Try (pQueenProblem, i+1); //继续试探摆放下个皇后
        pQueenProblem->iMatrixA [i-1][j-1] = 0; //恢复状态，回溯
    }
}
//检查目前第i个皇后摆放是否ok
int CheckOk (struct S8Queen  *pQueenProblem, int i)
{
    int iQueenColNow = pQueenProblem->iColPerRowA [i -1]; //当前行摆放皇后列号
    int iRow;
    for (iRow = 1; iRow < i; ++iRow)
    {
        int iQueenCol = pQueenProblem->iColPerRowA [iRow -1]; //iRow行已摆放皇后列号
        if (iQueenCol == iQueenColNow)
            return 0; //同一列，有冲突
        if (iQueenCol + iRow == iQueenColNow + i)
            return 0; //右上角已摆放皇后，有冲突
        if (iQueenCol - iRow == iQueenColNow - i )
            return 0; //左上角已摆放皇后，有冲突
    }
    return 1; //ok
}

#include <stdio.h>

#define MaxN 20
struct S8Queen
{
    int   N;
    int   iMatrixA [MaxN][MaxN]; //���̾��󣬱������
    int   iColPerRowA [MaxN]; //ÿ�лʺ�ڷ��кţ����ڼ��
    int   iSolutionCount;
};

//��ʼ������
void InitProbelm (struct S8Queen  *pQueenProblem, int n);
//��ӡһ����
void PrintSolution (struct S8Queen  *pQueenProblem);
//��̽��i���ʺ�ڷ�
void Try (struct S8Queen  *pQueenProblem, int i);
//���Ŀǰ��i���ʺ�ڷ��Ƿ�ok
int CheckOk (struct S8Queen  *pQueenProblem, int i);

int main ()
{
    int n;
    while (1)
    {
        printf ("���������̴�С(4~20):\n");
        scanf ("%d", &n);
        if (n <4 || n > 20)
            break;
        struct S8Queen  theQueenProblem;
        InitProbelm (&theQueenProblem, n);
        Try (&theQueenProblem, 1);
    }
    return 0;
}

//��ʼ������
void InitProbelm (struct S8Queen  *pQueenProblem, int n)
{
    pQueenProblem->N = n;
    int i, j;
    pQueenProblem->iSolutionCount = 0;
    for (i = 0; i < pQueenProblem->N; ++i)
        for (j = 0; j < pQueenProblem->N; ++j)
            pQueenProblem->iMatrixA [i][j] = 0;
}
//��ӡһ����
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
//��̽��i���ʺ�ڷ�
void Try (struct S8Queen  *pQueenProblem, int i)
{
    if (i > pQueenProblem->N)
    {
        ++ pQueenProblem->iSolutionCount;
        PrintSolution (pQueenProblem);
        return; //��������
    }
    int j;
    for (j = 1; j <= pQueenProblem->N; ++j)
    {
        pQueenProblem->iMatrixA [i-1][j-1] = 1; //��̽�ڷ���j��
        pQueenProblem->iColPerRowA [i-1] = j;
        if (CheckOk (pQueenProblem, i))
            Try (pQueenProblem, i+1); //������̽�ڷ��¸��ʺ�
        pQueenProblem->iMatrixA [i-1][j-1] = 0; //�ָ�״̬������
    }
}
//���Ŀǰ��i���ʺ�ڷ��Ƿ�ok
int CheckOk (struct S8Queen  *pQueenProblem, int i)
{
    int iQueenColNow = pQueenProblem->iColPerRowA [i -1]; //��ǰ�аڷŻʺ��к�
    int iRow;
    for (iRow = 1; iRow < i; ++iRow)
    {
        int iQueenCol = pQueenProblem->iColPerRowA [iRow -1]; //iRow���ѰڷŻʺ��к�
        if (iQueenCol == iQueenColNow)
            return 0; //ͬһ�У��г�ͻ
        if (iQueenCol + iRow == iQueenColNow + i)
            return 0; //���Ͻ��ѰڷŻʺ��г�ͻ
        if (iQueenCol - iRow == iQueenColNow - i )
            return 0; //���Ͻ��ѰڷŻʺ��г�ͻ
    }
    return 1; //ok
}

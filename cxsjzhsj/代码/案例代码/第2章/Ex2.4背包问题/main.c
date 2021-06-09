#include <stdio.h>
#include <stdlib.h>

#define MaxN 500
struct SGoods
{   int iWeight; //��Ʒ����
    int iPrice; //��Ʒ��ֵ
    double dPriceRatio; //ÿ��λ�����ļ�ֵ
};
struct SSolution
{   int   bSelectA [MaxN]; //ѡ��״̬
    int   iMaxValue;       //�ܼ�ֵ
};
struct SBag
{   int    N;               //��Ʒ����
    int    iWeightLimit, iWeightLeft;    //����������ʣ������
    struct SGoods sGoodsA [MaxN];  //��Ʒ��Ϣ
    struct SSolution bestSolution, solutionNow; //���Ž⡢Ŀǰ��
};

//��ʼ������, �ɹ�����1��ʧ�ܷ���0
int InitProbelm (struct SBag  *pProblem);
//��ӡ���Ž�
void PrintSolution (struct SBag  *pProblem);
//��̽��i����Ʒѡ��
void Try (struct SBag  *pProblem, int i);
//���Ŀǰ��i���ʺ�ڷ��Ƿ�ok
int CheckOk (struct SBag  *pProblem, int i);

int main ()
{   struct SBag  theProblem;
    if (InitProbelm (&theProblem))
    {   Try (&theProblem, 1);       //�ӵ�һ����Ʒ��ʼ��̽
        PrintSolution (&theProblem);//��ӡ���Ž�
    }
    return 0;
}
//��Ʒ��λ��ֵ�ȽϺ���������������qsort�ݼ�������
int compare(const void *p1, const void *p2)
{   const struct SGoods *pGoods1 = (const struct SGoods *)p1;
    const struct SGoods *pGoods2 = (const struct SGoods *)p2;
    if (pGoods1->dPriceRatio > pGoods2->dPriceRatio)
        return -1; //��Ʒ��λ��ֵ�Ƚϸ���ǰ��
    else if (pGoods1->dPriceRatio == pGoods2->dPriceRatio)
        return 0;
    else
        return 1;
}
//��ʼ������, �ɹ�����1��ʧ�ܷ���0
int InitProbelm (struct SBag  *pProblem)
{   int iWeightLimit;
    printf ("�����뱳������(10~1000):\n");
    scanf ("%d", &iWeightLimit);
    if (iWeightLimit <10 || iWeightLimit > 1000)
        return 0;

    pProblem->iWeightLeft = pProblem->iWeightLimit = iWeightLimit;
    int n;
    printf ("��������Ʒ����(4~500):\n");
    scanf ("%d", &n);
    if (n <4 || n > 500)
        return 0;
    pProblem->N = n;
    printf ("�������������Ʒ�����ͼ�ֵ(�ո�ָ�):\n");
    int i;
    for (i = 0; i < pProblem->N; ++i)
    {   struct SGoods goods;
        scanf ("%d%d", &goods.iWeight, &goods.iPrice);
        //������Ʒ��λ��ֵ
        goods.dPriceRatio = (double)goods.iPrice / goods.iWeight;
        pProblem->sGoodsA [i] = goods;
        pProblem->bestSolution.bSelectA [i]=pProblem->solutionNow.bSelectA[i]=0;
    }
    pProblem->bestSolution.iMaxValue = pProblem->solutionNow.iMaxValue = 0;
    //����Ʒ��λ��ֵ�ݼ�����
    qsort (pProblem->sGoodsA, pProblem->N, sizeof (struct SGoods), compare);
    return 1;
}
//��ӡ���Ž�
void PrintSolution (struct SBag  *pProblem)
{   int i, count = 0;
    printf ("����ܼ�ֵ %d:\n", pProblem->bestSolution.iMaxValue);
    for (i = 0; i < pProblem->N; ++i)
    {   if (pProblem->bestSolution.bSelectA [i])
        {   ++count;
            printf ("No. %d, ���� : %d, ��ֵ %d\n",
                count, pProblem->sGoodsA [i].iWeight, pProblem->sGoodsA [i].iPrice);
        }
    }
}
//��̽��i����Ʒѡ��
void Try (struct SBag  *pProblem, int i)
{   if (i > pProblem->N)
    {   //����̽��������Ʒ
        if (pProblem->bestSolution.iMaxValue < pProblem->solutionNow.iMaxValue)
            pProblem->bestSolution = pProblem->solutionNow; //�滻�ɸ��Ž�
        return; //��������
    }
    int iSelected;
    for (iSelected = 1; iSelected >= 0; --iSelected) //��λ��ֵ��Ʒ���Է�
    {   pProblem->solutionNow.bSelectA [i-1] = iSelected;
        if (pProblem->solutionNow.bSelectA [i-1])
        {   //����ʱ����״̬
            pProblem->iWeightLeft -= pProblem->sGoodsA [i-1].iWeight;
            pProblem->solutionNow.iMaxValue +=  pProblem->sGoodsA [i-1].iPrice;
        }
        if (CheckOk (pProblem, i)) //������̽�Ƿ����
            Try (pProblem, i+1); //������̽�ڷ��¸���Ʒ

        if (pProblem->solutionNow.bSelectA [i-1])
        {   //�ָ�������״̬������
            pProblem->solutionNow.bSelectA [i-1] = 0;
            pProblem->iWeightLeft += pProblem->sGoodsA [i-1].iWeight;
            pProblem->solutionNow.iMaxValue -=  pProblem->sGoodsA [i-1].iPrice;
        }
    }
}
//���Ŀǰ��i����Ʒ�ڷ��Ƿ�ok
int CheckOk (struct SBag  *pProblem, int i)
{   if (pProblem->iWeightLeft < 0)
        return 0; //������Ʒ�����ᳬ��
    int iValue = pProblem->bestSolution.iMaxValue - pProblem->solutionNow.iMaxValue;
    //��Ʒ����λ��ֵ�ݼ�����
    if (i+1 <= pProblem->N && pProblem->iWeightLeft * pProblem->sGoodsA [i].dPriceRatio <= iValue)
        return 0; //������Ʒ�����ڷ����޷�����������ѷ���
    return 1; //ok
}

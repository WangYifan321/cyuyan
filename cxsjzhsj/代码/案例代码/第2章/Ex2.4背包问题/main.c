#include <stdio.h>
#include <stdlib.h>

#define MaxN 500
struct SGoods
{   int iWeight; //商品重量
    int iPrice; //商品价值
    double dPriceRatio; //每单位重量的价值
};
struct SSolution
{   int   bSelectA [MaxN]; //选中状态
    int   iMaxValue;       //总价值
};
struct SBag
{   int    N;               //物品数量
    int    iWeightLimit, iWeightLeft;    //背包容量，剩余容量
    struct SGoods sGoodsA [MaxN];  //物品信息
    struct SSolution bestSolution, solutionNow; //最优解、目前解
};

//初始化问题, 成功返回1，失败返回0
int InitProbelm (struct SBag  *pProblem);
//打印最优解
void PrintSolution (struct SBag  *pProblem);
//试探第i个物品选择
void Try (struct SBag  *pProblem, int i);
//检查目前第i个皇后摆放是否ok
int CheckOk (struct SBag  *pProblem, int i);

int main ()
{   struct SBag  theProblem;
    if (InitProbelm (&theProblem))
    {   Try (&theProblem, 1);       //从第一个物品开始试探
        PrintSolution (&theProblem);//打印最优解
    }
    return 0;
}
//商品单位价值比较函数，快速排序函数qsort递减排序用
int compare(const void *p1, const void *p2)
{   const struct SGoods *pGoods1 = (const struct SGoods *)p1;
    const struct SGoods *pGoods2 = (const struct SGoods *)p2;
    if (pGoods1->dPriceRatio > pGoods2->dPriceRatio)
        return -1; //商品单位价值比较高排前面
    else if (pGoods1->dPriceRatio == pGoods2->dPriceRatio)
        return 0;
    else
        return 1;
}
//初始化问题, 成功返回1，失败返回0
int InitProbelm (struct SBag  *pProblem)
{   int iWeightLimit;
    printf ("请输入背包现重(10~1000):\n");
    scanf ("%d", &iWeightLimit);
    if (iWeightLimit <10 || iWeightLimit > 1000)
        return 0;

    pProblem->iWeightLeft = pProblem->iWeightLimit = iWeightLimit;
    int n;
    printf ("请输入物品数量(4~500):\n");
    scanf ("%d", &n);
    if (n <4 || n > 500)
        return 0;
    pProblem->N = n;
    printf ("请依次输入各物品重量和价值(空格分隔):\n");
    int i;
    for (i = 0; i < pProblem->N; ++i)
    {   struct SGoods goods;
        scanf ("%d%d", &goods.iWeight, &goods.iPrice);
        //计算商品单位价值
        goods.dPriceRatio = (double)goods.iPrice / goods.iWeight;
        pProblem->sGoodsA [i] = goods;
        pProblem->bestSolution.bSelectA [i]=pProblem->solutionNow.bSelectA[i]=0;
    }
    pProblem->bestSolution.iMaxValue = pProblem->solutionNow.iMaxValue = 0;
    //按商品单位价值递减排序
    qsort (pProblem->sGoodsA, pProblem->N, sizeof (struct SGoods), compare);
    return 1;
}
//打印最优解
void PrintSolution (struct SBag  *pProblem)
{   int i, count = 0;
    printf ("最大总价值 %d:\n", pProblem->bestSolution.iMaxValue);
    for (i = 0; i < pProblem->N; ++i)
    {   if (pProblem->bestSolution.bSelectA [i])
        {   ++count;
            printf ("No. %d, 重量 : %d, 价值 %d\n",
                count, pProblem->sGoodsA [i].iWeight, pProblem->sGoodsA [i].iPrice);
        }
    }
}
//试探第i个物品选择
void Try (struct SBag  *pProblem, int i)
{   if (i > pProblem->N)
    {   //已试探完所有物品
        if (pProblem->bestSolution.iMaxValue < pProblem->solutionNow.iMaxValue)
            pProblem->bestSolution = pProblem->solutionNow; //替换成更优解
        return; //继续回溯
    }
    int iSelected;
    for (iSelected = 1; iSelected >= 0; --iSelected) //单位价值物品先试放
    {   pProblem->solutionNow.bSelectA [i-1] = iSelected;
        if (pProblem->solutionNow.bSelectA [i-1])
        {   //放入时设置状态
            pProblem->iWeightLeft -= pProblem->sGoodsA [i-1].iWeight;
            pProblem->solutionNow.iMaxValue +=  pProblem->sGoodsA [i-1].iPrice;
        }
        if (CheckOk (pProblem, i)) //本次试探是否可行
            Try (pProblem, i+1); //继续试探摆放下个物品

        if (pProblem->solutionNow.bSelectA [i-1])
        {   //恢复不放入状态，回溯
            pProblem->solutionNow.bSelectA [i-1] = 0;
            pProblem->iWeightLeft += pProblem->sGoodsA [i-1].iWeight;
            pProblem->solutionNow.iMaxValue -=  pProblem->sGoodsA [i-1].iPrice;
        }
    }
}
//检查目前第i个物品摆放是否ok
int CheckOk (struct SBag  *pProblem, int i)
{   if (pProblem->iWeightLeft < 0)
        return 0; //本项物品放入后会超重
    int iValue = pProblem->bestSolution.iMaxValue - pProblem->solutionNow.iMaxValue;
    //物品按单位价值递减排序
    if (i+1 <= pProblem->N && pProblem->iWeightLeft * pProblem->sGoodsA [i].dPriceRatio <= iValue)
        return 0; //后面物品继续摆放已无法超过已有最佳方案
    return 1; //ok
}

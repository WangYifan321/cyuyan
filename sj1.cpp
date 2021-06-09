#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100
#define M 10
char suffix[N];             //后缀表达式
char ret[2];                //字符串栈进行弹出时的返回值（弹出元素）
char tokens[N][M];          //令牌，将中缀表达式分解后的字符串数组
char ctokens[N][M];         //令牌，将后缀表达式分解后的字符串数组
int count;                  //tokens令牌的个数
int value;                  //表达式的值
int l = 0;                  //ctokens令牌的个数
typedef struct stack1{      //操作符栈
    int  top;
    char elem[N][2];
}stacki;
typedef struct stack2{      //操作数栈
    int top;
    int elem[N];
}stackj;
typedef stacki* STACK;      //指向操作符栈的指针
typedef stackj* DSTACK;     //指向操作数栈的指针

void toSuffix(char *str);                   //将中缀表达式转化成后缀表达式
int PreParse(char tokens[][M],char *str);   //将中缀表达式分解成令牌返回令牌中字符串个数
int GetProsity(char *ch);                   //获得操作符的优先级并返回
void push(STACK S,char *opt);               //操作符栈的入栈
char *pop(STACK S);                         //操作符栈的出栈，并返回出栈元素
int IsEmpty(STACK S);                       //判断操作符栈是否为空
void MakeNull(STACK S);                     //将操作符栈制空
void PrintStack(STACK S);                   //打印操作符栈
void dpush(DSTACK S,int opd);               //操作符数的入栈
void dpop(DSTACK S);                        //操作符数的出栈
void PrintStack1(DSTACK S);                 //打印操作数栈
void MakeNull1(DSTACK S);                   //将操作数栈制空
int Evalute(char ctokens[][M]);             //计算后缀表达式的值并返回

int main()
{
    char str[N];
    printf("Please input a expression：\n");
    gets(str);                              //输入所求中缀表达式str
    toSuffix(str);                          //将中缀表达式转化成后缀表达式
    puts(suffix);                           //输出转化后的后缀表达式
    value = Evalute(ctokens);               //计算后缀表达式的值
    printf("%d",value);
    return 0;
}

void toSuffix(char *str)
{
    int i;
    stacki stacks;                          //定义一个操作符栈stacks
    STACK optstack = &stacks;               //定义操作符栈指针optstack
    MakeNull(optstack);
    count = PreParse(tokens,str);
    for(i = 0;i < count;i++)
    {
        if(!(strcmp(tokens[i],"+") && strcmp(tokens[i],"-") && strcmp(tokens[i],"*") && strcmp(tokens[i],"/") && strcmp(tokens[i],"(") && strcmp(tokens[i],")")))
        {
            if(IsEmpty(optstack))
            {
                push(optstack,tokens[i]);
                PrintStack(optstack);
            }
            else
            {
                if(!strcmp(tokens[i],"("))
                {
                    push(optstack,tokens[i]);
                    PrintStack(optstack);
                }
                else if(!strcmp(tokens[i],")"))
                {
                    while(strcmp(optstack->elem[optstack->top],"("))        //循环直到遇见左括号
                    {
                        strcpy(ctokens[l],optstack->elem[optstack->top]);
                        l++;
                        strcat(suffix,pop(optstack));
                        PrintStack(optstack);
                    }
                    pop(optstack);                                          //左括号弹出
                    PrintStack(optstack);
                }
                else
                {
                    if(GetProsity(tokens[i]) > GetProsity(optstack->elem[optstack->top]))
                    {
                        push(optstack,tokens[i]);
                        PrintStack(optstack);
                    }
                    else
                    {
                        while(optstack->top < 100)
                        {
                            if(GetProsity(tokens[i]) <= GetProsity(optstack->elem[optstack->top]))
                            {
                                strcpy(ctokens[l],optstack->elem[optstack->top]);
                                l++;
                                strcat(suffix,pop(optstack));
                                PrintStack(optstack);
                            }
                            else
                            {
                                break;
                            }
                        }
                        push(optstack,tokens[i]);
                        PrintStack(optstack);
                    }
                }
            }
        }
        else                            //是数字则直接加到suffix的后面
        {
            strcpy(ctokens[l],tokens[i]);
            l++;
            strcat(suffix,tokens[i]);
        }
    }
    while(optstack->top < 100)          //将剩余元素弹出
    {
        strcpy(ctokens[l],optstack->elem[optstack->top]);
        l++;
        strcat(suffix,pop(optstack));
    }
    PrintStack(optstack);
}

int PreParse(char tokens[][M],char *str)
{
    char p[N];
    char temp[2];
    int i=0,j = 0,l,k = 0;
    for(i = 0;i < strlen(str);i++)      //删除表达式中的空格
    {
        if(str[i] == ' ') continue;
        else
        {
            p[j] = str[i];
            j++;
        }
    }
    p[j] = '\0';
    i = 0;
    for(j = 0;j < strlen(p);j++)
    {
        if(p[j] == '+' || p[j] == '-' || p[j] == '*' || p[j] == '/' || p[j] == '(' || p[j] == ')')    //运算符转化为字符串
        {
            temp[0] = p[j];
            temp[1] = '\0';
            strcpy(tokens[k],temp);
        }
        else
        {
            for(l = 0;isdigit(p[j]);l++)                    //得到多位数字的字符串
            {
                tokens[k][l] = p[j];
                j++;
            }
            tokens[k][l] = '\0';
            j--;
        }
        k++;
    }
    return k ;
}

int GetProsity(char *ch)
{
    int prosity;
    if(!(strcmp(ch,"(")))
    {
        prosity = 0;
    }
    if(!(strcmp(ch,"+") && strcmp(ch,"-")))
    {
        prosity = 1;
    }
    if(!(strcmp(ch,"*") && strcmp(ch,"/")))
    {
        prosity = 2;
    }
    return prosity;
}

void push(STACK S,char *opt)
{
    if(S->top == 0)
    {
        return ;
    }
    S->top--;
    strcpy(S->elem[S->top],opt);
    return ;
}

char *pop(STACK S)
{
        strcpy(ret,S->elem[S->top]);
        S->top++;
        return ret;

}

int IsEmpty(STACK S)
{
    if(S->top > N - 1)
        return 1;
    else
        return 0;
}

void MakeNull(STACK S)
{
    S->top = N ;
}

void MakeNull1(DSTACK S)
{
    S->top = N ;
}
void PrintStack(STACK S)
{
    int i;
    for(i = N-1;i >= S->top;i--)
    {
        printf("%s",S->elem[i]);
    }
    printf("\n");
}

void dpush(DSTACK S,int opd)
{
    if(S->top == 0)
    {
        return ;
    }
    S->top--;
    S->elem[S->top] = opd;
}

void dpop(DSTACK S)
{
    S->top++;
}

void PrintStack1(DSTACK S)
{
    int i;
    for(i = N-1;i >= S->top;i--)
    {
        printf("%d ",S->elem[i]);
    }
    printf("\n");
}
int Evalute(char ctokens[][M])
{
    int i;
    int ropd,lopd;
    int t;
    stackj stack;                   //定义一个操作数栈
    DSTACK opdstack = &stack;       //初始化操作数栈指针
    MakeNull1(opdstack);
    for(i = 0;i < l;i++)
    {
        if(!strcmp(ctokens[i],"+")) //操作符则弹出两栈内元素进行相应运算
        {
            ropd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            lopd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            t = lopd + ropd;
            dpush(opdstack,t);
            PrintStack1(opdstack);
        }
        else if(!strcmp(ctokens[i],"-"))
        {
            ropd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            lopd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            t = lopd - ropd;
            dpush(opdstack,t);
            PrintStack1(opdstack);
        }
        else if(!strcmp(ctokens[i],"*"))
        {
            ropd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            lopd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            t = lopd * ropd;
            dpush(opdstack,t);
            PrintStack1(opdstack);
        }
        else if(!strcmp(ctokens[i],"/"))
        {
            ropd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            lopd = opdstack->elem[opdstack->top];
            dpop(opdstack);
            t = lopd / ropd;
            dpush(opdstack,t);
            PrintStack1(opdstack);
        }
        else            //操作数入栈
        {
            dpush(opdstack,atoi(ctokens[i]));
            PrintStack1(opdstack);
        }
    }
    value = opdstack->elem[opdstack->top];
    return value;
}
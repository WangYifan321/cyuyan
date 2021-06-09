#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#define STACK_INIT_SIZE 1000
#define STACKNCREMENT 10
//度 出度（向下的） 哈夫曼树没有度为1的节点
typedef struct {
    char *base;
    char *top;
    int stacksize;
}TRStack;

typedef struct {
    float *base;
    float *top;
    int stacksize;
}NDStack;

char TRGetTop(TRStack *S){
    char e;
    if(S->top == S->base) return 0;
    e = *(S->top-1);
    return e;
}

float NDGetTop(NDStack *S){
    float e;
    if(S->top == S->base) return 0;
    e = *(S->top-1);
    return e;
}

int InitTRStack(TRStack *S){
    S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if(!S->base) exit(-2);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

int InitNDStack(NDStack *S){
    S->base = (float *)malloc(STACK_INIT_SIZE * sizeof(float));
    if(!S->base) exit(-2);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

int TRPush(TRStack *S, char e){
    if(S->top - S->base >= S->stacksize){
        S->base = (char *)realloc(S->base, (S->stacksize + STACK_INIT_SIZE * sizeof(char)));
        if(!S->base) exit(-2);
        S->top = S->base + S->stacksize;
        S->stacksize += STACKNCREMENT;
        }
    *S->top++ = e;
    return 1;
}

int NDPush(NDStack *S, float e){
    if(S->top - S->base >= S->stacksize){
        S->base = (float *)realloc(S->base, (S->stacksize + STACK_INIT_SIZE * sizeof(float)));
        if(!S->base) exit(-2);
        S->top = S->base + S->stacksize;
        S->stacksize += STACKNCREMENT;
        }
    *S->top++ = e;
    return 1;
}

int TRPop(TRStack *S, char *e){
    if(S->top == S->base) return 0;
    *e = * --S->top;
    return 1;
}

int NDPop(NDStack *S, float *e){
    if(S->top == S->base) return 0;
    *e = * --S->top;
    return 1;
}

float Opreate(float a, float b, char theta){
    switch(theta){
        case'+':return a+b;
        case'-':return a-b;
        case'/':return a/b;
        case'*':return a*b;
        default:return 0;
    }
}

int In(char c,char *OP){
    int flag = 0;
    int i = 0;
    while(OP[i]!='\0'){
        if(OP[i]==c) flag=1;
        i++;
    }
    return flag;
}

char Precede(char m, char n, char *OP){
    unsigned char Prior[7][7] =
    {'>','>','<','<','<','>','>',
     '>','>','<','<','<','>','>',
     '>','>','>','>','<','>','>',
     '>','>','>','>','<','>','>',
     '<','<','<','<','<','=',' ',
     '>','>','>','>',' ','>','>',
     '<','<','<','<','<',' ','=',};
     int i = 0; int j = 0;
     while(m != OP[i]) i++;
     while(n != OP[j]) j++;
     return Prior[i][j];
}

void OutPutNDStack(NDStack *S){
    float *c;
    c =  S->top;
    printf("OPND栈: ");
    while(c!=S->base){
        c--;
        printf("%f  ",*c);
    }
}

void OutPutTRStack(TRStack *S){
    char *c;
    c =  S->top;
    printf("OPTR栈: ");
    while(c!=S->base){
        c--;
        printf("%c  ",*c);
    }
}

float EvaluateExpression(char *expr){
    char OP[8] = {'+','-','*','/','(',')','#','\0'};
    TRStack OPTR; NDStack OPND;
    char *c;
    char End[] = {'#','\0'};
    char cc[255];
    float a,b;
    char theta,x;
    float cf;
    InitTRStack(&OPTR); TRPush(&OPTR,'#');
    InitNDStack(&OPND); c = strcat(expr,End);
    while(*c!='#' || TRGetTop(&OPTR)!='#') {
        if(!In(*c,OP)){
            while(!In(*c,OP)){strcat(cc,c);c++;}
            cf = atof(cc);
            OutPutTRStack(&OPTR);
            OutPutNDStack(&OPND);
            printf("输入字符:%f  ",cf);
            memset(cc, 0x00, sizeof (char) * 256);
            NDPush(&OPND,cf);
            printf("操作:Push(OPND,%f)\n",cf);
        }
        else{
            OutPutTRStack(&OPTR);
            OutPutNDStack(&OPND);
            printf("输入字符:%c  ",*c);
            switch(Precede(TRGetTop(&OPTR),*c,OP)){
            case'<':
                TRPush(&OPTR,*c);
                printf("操作:Push(OPTR,%c)\n",*c);
                c++;
                break;
            case'=':
                TRPop(&OPTR,&x);
                printf("操作:Pop(OPTR,%c)\n",x);
                c++;
                break;
            case'>':
                TRPop(&OPTR,&theta);
                NDPop(&OPND,&b);
                NDPop(&OPND,&a);
                NDPush(&OPND,Opreate(a,b,theta));
                printf("操作:Opreate(%f,%c,%f)\n",a,theta,b);
                break;
            case' ':
                return 0;
            }
        }
    }
    OutPutTRStack(&OPTR);
    OutPutNDStack(&OPND);
    printf("输入字符:%c  ",*c);
    printf("操作:return GetTop(OPND)\n");
    return NDGetTop(&OPND);
}

int main(){
    char Exp[254];
    int i = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    int flag = 0;
    printf("input equation:\n");
    gets(Exp);
    char stdinput[17] = {'+','-','*','/','(',')','1','2','3','4','5','6','7','8','9','0','\0'};
    while(Exp[i]!='\0'){
        if(Exp[i]=='(') cnt1++;
        if(Exp[i]==')') cnt2++;
        if(!In(Exp[i],stdinput)) {flag = 1; break;}
        else i++;
    }
    if(cnt1!=cnt2) flag = 1;
    if(!flag) {printf("结果：%f",EvaluateExpression(Exp));}
    else {printf("invalid input\n");}
}
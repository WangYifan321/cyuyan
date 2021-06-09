#include<stdio.h>
#include<stdlib.h>
//2栈为符号
struct node2{
    char b[20];
    int top;
};
typedef struct node2 *stack2;
stack2 init2(){
    stack2 s;
    s=(stack2)malloc(sizeof(struct node2));
    s->top=-1;
    return s;
}
void push2(stack2 s,char c){
    s->top++;
    s->b[s->top]=c;
}
char pop2(stack2 s){
    char i = s->b[s->top];
    s->top--;
    return i;
}
char Precede(char m, char n){
    char OP[6] = {'+','-','*','/','(',')'};
    unsigned char Prior[6][6] =
    {'<','<','<','<','>','<',
     '<','<','<','<','>','<',
     '>','>','<','<','>','<',
     '>','>','<','<','>','<',
     '>','>','>','>','>',' ',
     '<','<','<','<','=',' ',
     };
     int i = 0; int j = 0;
     while(m != OP[i]) i++;
     while(n != OP[j]) j++;
     return Prior[i][j];
}
int in(char c){
    char op[6]={'+','-','*','/','(',')'};
    int a=3;
    for(int i=0;i<6;i++){
        if(c == op[i]){
            return 2;

        }
    }
    if((c>='0' && c<='9') || c == '.')
        return 1;

        }//1代表是数字，2代表是符号
int main(){
    char c[100];
    gets(c);
    stack2 s2 = init2();
    for(int i=0;c[i]!='\0';i++){
       if(in(c[i])==1){
          printf("%c",c[i]);
          while(in(c[i+1])==1){
              printf("%c",c[i+1]);
              i++;
          }
          if(c[i+1] != '\0' || s2->top != -1)
          printf(" ");
       }else if(in(c[i])==2){
              if(in(c[i+1])==1 && (i==0 || (c[i-1]=='('))){
                  if(c[i] == '+'){
                      printf("");
                  }else if(c[i] == '-')
                  printf("-");
                  else if(c[i] == '(')
                   push2(s2,c[i]);
              }else
                   if(s2->top==-1)
          push2(s2,c[i]);
          else{
              switch(Precede(c[i],s2->b[s2->top])){
                  case'>':
                       push2(s2,c[i]);
                       break;
                  case'=':
                       pop2(s2);
                       break;
                  case'<':
                           printf("%c ",pop2(s2));

                           i--;
                           break;

                        }                    
              }
                     
              }
          
        
    }
         while(s2->top>0){
              printf("%c ",pop2(s2));  
                      } 
                      if(s2->top == 0)
              printf("%c",pop2(s2));  
              return 0;    
}

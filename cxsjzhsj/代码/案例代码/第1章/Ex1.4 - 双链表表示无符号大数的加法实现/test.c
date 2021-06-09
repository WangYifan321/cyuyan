#include <stdio.h>
#include "UBigNumber.h"

int main ()
{   struct UBigNumber A, B, C;
    A = InputUBN (); //无符号大数输入
    B = InputUBN ();
    C = AddUBN (&A, &B); //无符号大数相加

    PrintUBN (A);
    printf (" + ");
    PrintUBN (B);
    printf (" = ");
    PrintUBN (C);

    DestoryUBN (&A); //销毁无符号大数
    DestoryUBN (&B);
    DestoryUBN (&C);
    return 0;
}

#include <stdio.h>
#include "UBigNumber.h"

int main ()
{   struct UBigNumber A, B, C;
    A = InputUBN (); //�޷��Ŵ�������
    B = InputUBN ();
    C = AddUBN (&A, &B); //�޷��Ŵ������

    PrintUBN (A);
    printf (" + ");
    PrintUBN (B);
    printf (" = ");
    PrintUBN (C);

    DestoryUBN (&A); //�����޷��Ŵ���
    DestoryUBN (&B);
    DestoryUBN (&C);
    return 0;
}

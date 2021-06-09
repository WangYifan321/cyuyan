#include <stdio.h>
//��n�����д�x������z�����ɽ���y��
void Hanoi (int n, char x, char y, char z);

int main ()
{   int n;  //��������
    scanf( "%d", &n);
    Hanoi (n, 'A', 'B', 'C');
    return 0;
}
//��n�����д�x������z�����ɽ���y��
void Hanoi (int n, char x, char y, char z)
{
    if (n == 1) {
        printf ("%c->%c\n", x, z); //һ������ʱ��ֱ�Ӱᶯ
    } else {
        Hanoi (n-1, x, z, y);//��n-1�����д�x������y��������z��
        printf ("%c->%c\n", x, z);//ʣ��һ������ʱ��ֱ�Ӱᶯ
        Hanoi (n-1, y, x, z);//��n-1�����д�y������z��������x��
    }
}

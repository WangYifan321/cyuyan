备注：上一个pdf忘记写特殊排序了，由于原先的markdown笔记删掉了，只留下了pdf，因此上交了两个pdf。

无序：

100、1000、10000      0.000

100000    0.001

1000000  0.016

有序：

100、1000、10000      0.000

1000000  0.016

100000    0.001

```c
void CountSort(int *a, int n)
{
	int i, j, k;
	for (i = 0; i<n; i++)
		fz[a[i]]++;  
	k = 0;
	for (j = 0; j <=n; j++)  
	for (i = 1; i <= fz[j]; i++)   
		a[k++] = j;
}
```


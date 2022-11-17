#include<stdio.h>
void reverseit(char a[100000], int n)
{
	char b[100000];
	int cnt = 7;
	int i = 0;
	int t = n;//从第n个数开始翻转
	for (i=0;i<8;i++)
	{
		b[cnt] = a[n];
		cnt--;
		n++;
	}
	for (i = 0; i < 8; i++)//翻转8位
	{
		 a[t]=b[i] ;
		 t++;
		
	}
}

void reversetarray(char a[1000][100], char b[1000][100], int n)
{
	int i = 0, j = 0, k = 0;
	for (i = 1; i <= n; i++)
	{
		j = 0, k = 0;
		while (a[i][j] == '0' || a[i][j] == '1')//统计该字符对应串的长度
		{
			j++;
		}

		for (j = j - 1; j >= 0; j--, k++)//对第i种字符的编码进行翻转
			b[i][k] = a[i][j];
	}
}

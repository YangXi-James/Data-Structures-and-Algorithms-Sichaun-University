#include<stdio.h>
void reverseit(char a[100000], int n)
{
	char b[100000];
	int cnt = 7;
	int i = 0;
	int t = n;//�ӵ�n������ʼ��ת
	for (i=0;i<8;i++)
	{
		b[cnt] = a[n];
		cnt--;
		n++;
	}
	for (i = 0; i < 8; i++)//��ת8λ
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
		while (a[i][j] == '0' || a[i][j] == '1')//ͳ�Ƹ��ַ���Ӧ���ĳ���
		{
			j++;
		}

		for (j = j - 1; j >= 0; j--, k++)//�Ե�i���ַ��ı�����з�ת
			b[i][k] = a[i][j];
	}
}

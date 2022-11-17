#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include"Huffman.h"
#include"reverse.h"



void compressit(HuffmanTree HT, int n, char a[1000][100], char name[100], char name1[100])
{
	FILE *fp, *fp2;
	char this;//���ڵõ��ļ����ַ�
	char total[100000];//���ڴ洢�����ļ��ı���
	int i = 0, j = 0,k=0,totalnumber=0,it=0,cnt=0;
	fp = fopen(name, "rb");

	if ((fp2 = fopen(name1, "a")) == NULL)
	{
		printf("fail to write");
		exit(1);
	}
	
	else
	{
		while (!feof(fp))//���������ļ�������õ����ַ�������ĳ���ַ���ͬ�������Ӧ���������total�ַ�����
		{
			this = fgetc(fp);
			
			j = 0;
			for (i = 1; i <= n; i++)
			{
				if (this == HT[i].sign)
				{
					while (a[i][j] == '0' || a[i][j] == '1')
					{
						total[k] = a[i][j];
						j++;
						k++;
					}
				}
			}		
		}

		it = k % 8;//�õ�Ҫ����0�ĸ������������ļ���
		if (it != 0)
			fputc(8 - it, fp2);
		else
			fputc(0, fp2);

		if (it != 0)//���ַ�����Ҫ�ӵ�0
		{
			for (i = 0; i < 8 - it; i++)
			{
				total[k] = '0';
				k++;
			}
		}
		it = k / 8;
		for (j = 0; j < it; j++)//ÿ8���ַ�һ�飬�����Ӧ��intֵ������������ļ�
		{
			totalnumber = 0;
			for (i = cnt; i < cnt + 8; i++)
			{
				if (total[i] == '1')
				{
					totalnumber = totalnumber + pow(2, cnt + 8 - i - 1);
				}
			}
			fputc(totalnumber, fp2);
			cnt = i;
		}
	}
	fclose(fp2);
}


void decompressit(HuffmanTree HT, char a[1000][100], char name[100], char name1[100])
{
	FILE *fp2 = fopen(name, "rb");
	FILE *fp3;
	char thisone[100000] = "";//���ڵõ��ļ������ַ���Ӧ�Ĺ����������ܴ�
	int i = 0, j = 0,total=0,k=1,m=0,it,w=0;
	int cnt = 0, len = 0;
	if ((fp3 = fopen(name1, "w")) == NULL)
	{
		printf("fail to write");
		exit(1);
	}
	else
	{
		len = fgetc(fp2);//�õ��ַ��������
		for (j = 0; j < len;j++)//��������Ĳ�ͬ�ַ�
		{
			total = fgetc(fp2);
			continue;
		}
		for (j = 0; j < len; j++)//��������Ĳ�ͬ�ַ��ĸ���
		{
			 fscanf(fp2,"%d", &total);
			continue;
		}

		it = fgetc(fp2);//����fprintf��Ŀո�
		it = fgetc(fp2);//�õ��ַ�����󲹳�0�ĸ���

		total = fgetc(fp2);//�õ������int�͵�ֵ
		while(total !=EOF)
		{
			w = 0;
			while (total > 0)//ͨ��int��ֵ����ԭ�ַ��������ģ�
			{
				thisone[i] = total % 2 +'0';
				total = total / 2;
				w++;
				i++;
			}
			if (w < 8)//��0
			{
				for (w; w < 8; w++)
				{
					thisone[i] = '0';
					i++;
				}
			}
			reverseit(thisone, i - 8);//���õ��ķ���01�����з�ת
			total = fgetc(fp2);
		}
		for (j = 0; j < it; j++)//ȥ�������0
		{
			thisone[i - 1] = '\0';
			i--;
		}
        
		for (k = 1; a[k][0] == '1' || a[k][0] == '0'; k++)//���õ��Ĵ��봢��ĸ��ֲ�ͬ���ַ��Ĵ���Ƚϣ�ÿһλ����ͬ�򽫶�Ӧ�����ַ������ļ�
		{
			j = cnt;
			m = 0;
			while (a[k][m] == thisone[j])
			{
				m++;
				j++;
				if (a[k][m] != '1' && a[k][m] != '0')
				{
					if(HT[k].sign !='\r')//���ڱ���ʱ���з�������Ϊ'\r'��'\n������'\r'ʱ����
					fputc(HT[k].sign, fp3);
					cnt = j;
					k = 0;
				}
			}
		}
		
	}
}

void Huffcode(HuffmanTree HT, int n, char a[1000][100],char b[1000][100])
{
	
		int i, j = 0, k = 0;
		int newone;
		for (i = 1; i <= n; i++)
		{
			k = i;
			j = 0;
			while (HT[k].parent != 0)//���ַ����б��룬ֱ�����ڵ�
			{
				newone = HT[k].parent;
				if (HT[newone].lc == k)//����丸�ڵ������������������Ϊ0
				{
					a[i][j] = '0';
					j++;
				}
				
				else//����丸�ڵ���Ҷ��������������Ϊ1
				{
					a[i][j] = '1';
					j++;
				}
				k = newone;
			}
		}
	
		reversetarray(a, b, n);//���õ��ķ��Ĵ����з�ת
}
void save(char output[10000], int outputnumber[10000], int n, char name1[100])
{
	int i,number;
	FILE *fp = fopen(name1, "wb");
	char a;
	
		n = n - 1;
		fputc(n, fp);//���ַ���������浽�ļ���
		for (i = 1; i <= n; i++)//��ÿһ���ַ����浽�ļ���
		{
			a = output[i];
			fputc(a, fp);
		}

		for (i = 1; i <= n; i++)//��ÿһ���ַ������������ļ���
		{
			number = outputnumber[i];
			fprintf(fp, " %d ", number);
		}

		fclose(fp);
}


int count(char name[100], char output[10000], int outnumber[10000],char name1[100])
{

	char buffer[1000];
	char buf[100000] = "";
	int j = 1;
	FILE *fp;            
	if ((fp = fopen(name, "rb")) == NULL)
	{
		printf("fail to read");
		exit(1);
	}

	while (!feof(fp))
	{
		fgets(buffer, 100, fp);//ÿ100���ַ�Ϊ��λ���������buffer��
		strcat(buf, buffer);//��buffer�ַ���ƴ�ӵ�buf���

	}

	int cnt[10000] = { 0 };
	int i;
	for (i = 0; buf[i] != '\0'; i++)//�����ַ�����ͳ�Ƹ���
	{
		if (buf[i] < 0) //�ж��Ƿ�Ϊ����
		{
			cnt[256 + buf[i]]++;
		}
		else 
		{
			cnt[buf[i]]++;
		}
	}
	cnt[buf[i]]++;

	for (i = 0; i < 300; i++)
		if (cnt[i] != 0)//���������Ϊ0���򽫸��ַ�����������д���
		{
			output[j] = i;
			outnumber[j] = cnt[i];
			j++;
		}
	save(output, outnumber, j, name1);//���õ����ַ������༰ÿ���ַ��������д���
	return j;

}



HuffmanTree * read(HuffmanTree HT,int *x,char name[100])
{
	int i = 0, j = 0;
	char get = "";
	char a[1000];
	FILE *fp = fopen(name, "rb");
	int number;
	number = fgetc(fp);//�õ��ļ��ַ����������
	int count[1000];

	x[0] = number;
	 i = 1;
	 while (j<number)//��ȡ�ļ��в�ͬ���ַ�
	 {
		get = fgetc(fp);
		a[i] = get;
		i++;
		j++;
	 }

	 i = 1;
	int k = 0;
	 while (k < number)//��ȡ�ļ��в�ͬ�ַ��ĸ���
	 {
		  fscanf(fp,"%d",&count[i]);
		 i++;
		 k++;
	 }
	HT = (HuffmanTree)malloc(number * 2 * sizeof(HTNode));//������������
	CreatHuff(HT, count, a, number);//��������������

	return HT;
}
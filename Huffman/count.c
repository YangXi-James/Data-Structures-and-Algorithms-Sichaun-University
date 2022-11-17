#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include"Huffman.h"
#include"reverse.h"



void compressit(HuffmanTree HT, int n, char a[1000][100], char name[100], char name1[100])
{
	FILE *fp, *fp2;
	char this;//用于得到文件中字符
	char total[100000];//用于存储整个文件的编码
	int i = 0, j = 0,k=0,totalnumber=0,it=0,cnt=0;
	fp = fopen(name, "rb");

	if ((fp2 = fopen(name1, "a")) == NULL)
	{
		printf("fail to write");
		exit(1);
	}
	
	else
	{
		while (!feof(fp))//遍历整个文件，如果得到的字符与树中某个字符相同，则将其对应编码其存入total字符串中
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

		it = k % 8;//得到要补的0的个数，并存入文件中
		if (it != 0)
			fputc(8 - it, fp2);
		else
			fputc(0, fp2);

		if (it != 0)//在字符串后补要加的0
		{
			for (i = 0; i < 8 - it; i++)
			{
				total[k] = '0';
				k++;
			}
		}
		it = k / 8;
		for (j = 0; j < it; j++)//每8个字符一组，算出对应的int值，并将其存入文件
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
	char thisone[100000] = "";//用于得到文件所有字符对应的哈夫曼编码总串
	int i = 0, j = 0,total=0,k=1,m=0,it,w=0;
	int cnt = 0, len = 0;
	if ((fp3 = fopen(name1, "w")) == NULL)
	{
		printf("fail to write");
		exit(1);
	}
	else
	{
		len = fgetc(fp2);//得到字符种类个数
		for (j = 0; j < len;j++)//跳过储存的不同字符
		{
			total = fgetc(fp2);
			continue;
		}
		for (j = 0; j < len; j++)//跳过储存的不同字符的个数
		{
			 fscanf(fp2,"%d", &total);
			continue;
		}

		it = fgetc(fp2);//跳过fprintf后的空格
		it = fgetc(fp2);//得到字符串最后补充0的个数

		total = fgetc(fp2);//得到储存的int型的值
		while(total !=EOF)
		{
			w = 0;
			while (total > 0)//通过int的值计算原字符串（反的）
			{
				thisone[i] = total % 2 +'0';
				total = total / 2;
				w++;
				i++;
			}
			if (w < 8)//补0
			{
				for (w; w < 8; w++)
				{
					thisone[i] = '0';
					i++;
				}
			}
			reverseit(thisone, i - 8);//将得到的反的01串进行翻转
			total = fgetc(fp2);
		}
		for (j = 0; j < it; j++)//去掉多余的0
		{
			thisone[i - 1] = '\0';
			i--;
		}
        
		for (k = 1; a[k][0] == '1' || a[k][0] == '0'; k++)//将得到的串与储存的各种不同的字符的串相比较，每一位都相同则将对应树的字符存入文件
		{
			j = cnt;
			m = 0;
			while (a[k][m] == thisone[j])
			{
				m++;
				j++;
				if (a[k][m] != '1' && a[k][m] != '0')
				{
					if(HT[k].sign !='\r')//由于编码时换行符被编码为'\r'和'\n’，故'\r'时跳过
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
			while (HT[k].parent != 0)//对字符进行编码，直到根节点
			{
				newone = HT[k].parent;
				if (HT[newone].lc == k)//如果其父节点的左儿子是它，则编码为0
				{
					a[i][j] = '0';
					j++;
				}
				
				else//如果其父节点的右儿子是它，则编码为1
				{
					a[i][j] = '1';
					j++;
				}
				k = newone;
			}
		}
	
		reversetarray(a, b, n);//将得到的反的串进行翻转
}
void save(char output[10000], int outputnumber[10000], int n, char name1[100])
{
	int i,number;
	FILE *fp = fopen(name1, "wb");
	char a;
	
		n = n - 1;
		fputc(n, fp);//将字符种类个数存到文件中
		for (i = 1; i <= n; i++)//将每一种字符串存到文件中
		{
			a = output[i];
			fputc(a, fp);
		}

		for (i = 1; i <= n; i++)//将每一种字符串个数存入文件中
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
		fgets(buffer, 100, fp);//每100个字符为单位，将其存入buffer中
		strcat(buf, buffer);//将buffer字符串拼接到buf最后

	}

	int cnt[10000] = { 0 };
	int i;
	for (i = 0; buf[i] != '\0'; i++)//遍历字符串，统计个数
	{
		if (buf[i] < 0) //判断是否为中文
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
		if (cnt[i] != 0)//如果个数不为0，则将该字符与其个数进行储存
		{
			output[j] = i;
			outnumber[j] = cnt[i];
			j++;
		}
	save(output, outnumber, j, name1);//将得到的字符串种类及每种字符个数进行储存
	return j;

}



HuffmanTree * read(HuffmanTree HT,int *x,char name[100])
{
	int i = 0, j = 0;
	char get = "";
	char a[1000];
	FILE *fp = fopen(name, "rb");
	int number;
	number = fgetc(fp);//得到文件字符串种类个数
	int count[1000];

	x[0] = number;
	 i = 1;
	 while (j<number)//读取文件中不同的字符
	 {
		get = fgetc(fp);
		a[i] = get;
		i++;
		j++;
	 }

	 i = 1;
	int k = 0;
	 while (k < number)//读取文件中不同字符的个数
	 {
		  fscanf(fp,"%d",&count[i]);
		 i++;
		 k++;
	 }
	HT = (HuffmanTree)malloc(number * 2 * sizeof(HTNode));//建立哈夫曼树
	CreatHuff(HT, count, a, number);//建立哈夫曼编码

	return HT;
}
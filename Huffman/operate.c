#include<stdio.h>
#include"Huffman.h"
#include"count.h"
  

void compress(char name[100],  char name1[100])
{
	int j;
	char a[1000][100];
	char b[1000][100];
	char output[1000];
	int outnumber[1000];
	j=count( name, output, outnumber, name1);//统计字符种类
	HuffmanTree HT = (HuffmanTree)malloc((j - 1) * 2 * sizeof(HTNode));//分配大小为2倍种类数的节点个数的结构体空间
	HT = CreatHuff(HT, outnumber, output, j - 1);//创建哈夫曼树
	 Huffcode(HT, j - 1,a,b);//哈夫曼编码
	 compressit(HT, j-1, b,  name, name1);//压缩
}

void decompree(char name[100], char name1[100])
{
	HuffmanTree HT=NULL;
	char a[1000][100];
	char b[1000][100];
	int x[1] = { 0 }, n;
	HT=read(HT,x,name);//从文件中读出字符并建树
	n = x[0];//得到字符种类
	 Huffcode(HT, n,a,b);//哈夫曼编码
	decompressit(HT, b,name,name1);//解压
}

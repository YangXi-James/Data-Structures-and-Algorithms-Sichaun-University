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
	j=count( name, output, outnumber, name1);//ͳ���ַ�����
	HuffmanTree HT = (HuffmanTree)malloc((j - 1) * 2 * sizeof(HTNode));//�����СΪ2���������Ľڵ�����Ľṹ��ռ�
	HT = CreatHuff(HT, outnumber, output, j - 1);//������������
	 Huffcode(HT, j - 1,a,b);//����������
	 compressit(HT, j-1, b,  name, name1);//ѹ��
}

void decompree(char name[100], char name1[100])
{
	HuffmanTree HT=NULL;
	char a[1000][100];
	char b[1000][100];
	int x[1] = { 0 }, n;
	HT=read(HT,x,name);//���ļ��ж����ַ�������
	n = x[0];//�õ��ַ�����
	 Huffcode(HT, n,a,b);//����������
	decompressit(HT, b,name,name1);//��ѹ
}

#pragma once
int count( char name[100], char output[10000], int outnumber[10000], char name1[100]);//����ͳ���ַ����༰ÿ���ַ�������
void decompressit(HuffmanTree HT, char b[1000][100], char name[100], char name1[100]);//���ڽ�ѹ����
void Huffcode(HuffmanTree HT, int n, char a[1000][100],char b[1000][100]);//���ڵõ����������벢�������
HuffmanTree * read(HuffmanTree HT,int *x, char name[100]);//���ڶ�ȡ���벢������������
void compressit(HuffmanTree HT, int n, char a[1000][100], char name[100], char name1[100]);//����ѹ���ı�
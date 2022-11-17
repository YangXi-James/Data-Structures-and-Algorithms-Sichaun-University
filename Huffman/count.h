#pragma once
int count( char name[100], char output[10000], int outnumber[10000], char name1[100]);//用于统计字符种类及每种字符的数量
void decompressit(HuffmanTree HT, char b[1000][100], char name[100], char name1[100]);//用于解压编码
void Huffcode(HuffmanTree HT, int n, char a[1000][100],char b[1000][100]);//用于得到哈夫曼编码并储存编码
HuffmanTree * read(HuffmanTree HT,int *x, char name[100]);//用于读取编码并建立哈夫曼树
void compressit(HuffmanTree HT, int n, char a[1000][100], char name[100], char name1[100]);//用于压缩文本
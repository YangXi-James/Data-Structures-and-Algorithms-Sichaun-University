typedef struct {
	int weight;         // ���Ȩֵ
	int parent, lc, rc; // ˫�׽��������ӽڵ�
	char sign;          //�洢���ַ�
}HTNode, *HuffmanTree;
HuffmanTree *CreatHuff(HuffmanTree HT, int *w, char *a, int n);
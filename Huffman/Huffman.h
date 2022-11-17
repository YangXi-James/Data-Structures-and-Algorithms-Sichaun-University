typedef struct {
	int weight;         // 结点权值
	int parent, lc, rc; // 双亲结点和左右子节点
	char sign;          //存储的字符
}HTNode, *HuffmanTree;
HuffmanTree *CreatHuff(HuffmanTree HT, int *w, char *a, int n);
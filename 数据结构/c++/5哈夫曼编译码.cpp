#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct {
	double weight;//节点所权值
	char s;//节点数据
	int parent, lchild, rchild;//节点的父亲节点，左孩子节点，右孩子节点
}HuffmanTree;//默认哈夫曼树包括空格，a--z，0--9共37个节点
typedef struct {
	char s;//存入的节点数据
	char code[38];//存入编码字符串
	int cnt;
}hashlist;//存编码信息的数组（一个哈夫曼表）
void CreatHuffmanTree(HuffmanTree* ht, int n, char* text) {//创建哈夫曼树
	int i, j, firstmin, secondmin, first, second;
	ht[0].s = ' ';//空格为0号单元直接存
	ht[0].parent = ht[0].lchild = ht[0].rchild = -1;
	ht[0].weight = 0;
	for (i = 1; i < 27; i++) {
		ht[i].s = 'a' + i - 1;
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
		ht[i].weight = 0;
	}
	for (i = 1; i < 11; i++) {
		ht[i + 26].s = '0' + i - 1;
		ht[i + 26].parent = ht[i + 26].lchild = ht[i + 26].rchild = -1;
		ht[i + 26].weight = 0;
	}
	for (i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') {
			ht[0].weight++;
		}
		else if (text[i] >= 'a' && text[i] <= 'z') {
			int j = text[i] - 'a' + 1;
			ht[j].weight++;
		}
		else if (text[i] >= '0' && text[i] <= '9') {
			int j = text[i] - '0' + 27;
			ht[j].weight++;
		}
		else {
			cout << "输入文本有误" << endl;
			break;
		}
	}
	cout << "打印文本出现各个字符的频度：" << endl;
	for (int i = 0; i < n; i++) {
		cout << ht[i].s << '\t' << ht[i].weight << endl;
	}
	for (i = n; i < 2 * n - 1; i++) {
		firstmin = 99999;//最小值
		secondmin = 99999;//次最小值
		first = 0;
		second = 0;//记录最小值和次最小值的下标
		for (int j = 0; j < i; j++) {
			if (ht[j].parent == -1) {
				if (ht[j].weight < firstmin) {
					second = first;
					secondmin = firstmin;
					firstmin = ht[j].weight;
					first = j;
				}
				else if (ht[j].weight < secondmin) {
					secondmin = ht[j].weight;
					second = j;
				}
			}
		}
		ht[i].weight = ht[first].weight + ht[second].weight;
		ht[i].s = ' ';//新节点方便整体输出加入字符空格
		ht[i].lchild = first;
		ht[i].rchild = second;
		ht[first].parent = i;
		ht[second].parent = i;
		ht[i].parent = -1;//新节点没有双亲
	}//构建哈夫曼的过程注意 找到的最小值作为新根的左孩子，次小值作为右孩子
}
void RHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int p, c;
	hashlist s;
	for (int i = 0; i < n; i++) {
		c = i;//将树中的第一个字符的下标给c暂存
		p = ht[c].parent;//找到c下标字符的双亲给p暂存
		s.cnt = n; //把cnt的值初始化为n，后续再用数组存字符的编码时, 倒着存
		s.code[n] = '\0';
		while (p != -1) {
			if (ht[p].lchild == c) {
				s.code[--s.cnt] = '0';
			}
			else {
				s.code[--s.cnt] = '1';
			}
			c = p;
			p = ht[c].parent;
		}//将第i个字符从它自身找到它的双亲为止
		codetext[i] = s;//第i个字符的编码存入codetext
		codetext[i].s = ht[i].s;
	}
}//逆向哈夫曼编码
void PrintHuffmanTreenode(hashlist* codetext, int n) {
	for (int i = 0; i < n; i++) {
		cout << i + 1 << '\t';
		cout << codetext[i].s << "：";
		int index = codetext[i].cnt;
		while (codetext[i].code[index] != '\0') {
			cout << codetext[i].code[index++];
		}
		cout << endl;
	}
}//打印哈夫曼编译表（即哈希表的数据）
void scanfstring(char* str) {
	int lens = 0;
	while (1) {
		cin.get(str[lens]);
		if (str[lens] == '#') {
			str[lens] = '\0';
			break;
		}
		lens++;
	}
}//输入需要编码的字符串
void PrintHuffmanCoding(hashlist* codetext, char* str, int lens) {
	for (int i = 0; i < lens; i++) {
		int index;
		if (str[i] == ' ') {
			index = 0;
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') {
				cout << codetext[index].code[len++];
			}
		}
		else if (str[i] <= 'z' && str[i] >= 'a') {
			index = (int)(str[i] - 'a' + 1);
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') {
				cout << codetext[index].code[len++];
			}
		}
		else if (str[i] <= '9' && str[i] >= '0') {
			index = (int)(str[i] - '0' + 27);
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') {
				cout << codetext[index].code[len++];
			}
		}
	}
	cout << endl;
}//打印编码结果
void HuffmanDecoding(HuffmanTree* ht, int n, char* pwd) {
	int ct = 0, Ppwdlen = 0;
	char s;
	cin >> s;
	int i = 2 * n - 2; //根结点的下标（地址）为2* N - 2
	while (s != '#') {
		if (s == '0') {
			i = ht[i].lchild;
		}//‘0’判断左走
		else if (s == '1') {
			i = ht[i].rchild;
		}//‘1’判断右走
		if (ht[i].lchild == -1 || ht[i].rchild == -1) {
			pwd[ct++] = ht[i].s;
			i = 2 * n - 2;//译完一段编码后置为头结点继续翻译
		}//从根结点一直找到叶子
		cin >> s;
	}//#结束后不再翻译
	if ((ht[i].lchild != -1 || ht[i].rchild != -1) && i != 2 * n - 2) {
		cout << "编码有误！";
	}
	pwd[ct] = '\0';
}//哈夫曼译码
void solve() {
	char c;
	int n = 37;//字符个数
	char str[200], text[1000];
	char* pwd;
	HuffmanTree* ht;
	hashlist* codetext;//存编码信息的数组，大小动态分配
	codetext = (hashlist*)malloc(sizeof(hashlist) * n);//给codetext数组分配空间
	pwd = (char*)malloc(sizeof(char) * 100);
	ht = (HuffmanTree*)malloc(sizeof(HuffmanTree) * (2 * n - 1));//哈夫曼树结点个数
	cout << "文本为（以#结束）：" << endl;
	scanfstring(text);
	CreatHuffmanTree(ht, n, text);//创建哈夫曼树
	RHuffmanCoding(ht, codetext, n);//哈夫曼编码
	cout << "编码对应的哈夫曼表" << endl;
	PrintHuffmanTreenode(codetext, n);//打印编码表（即哈希表的数据）
	cout << "请输入需要编码的字符串（以#结束）：" << endl;
	scanfstring(str);//输入字符串
	cout << "该字符串编码为：" << endl;
	PrintHuffmanCoding(codetext, str, strlen(str));//打印编码结果
	cout << "输入需要译文的编码（以#结束）：" << endl;
	HuffmanDecoding(ht, n, pwd);//解码
	cout << "编码译文为：" << endl << pwd;
}
int main() {
	solve();
	return 0;
}
/*运行结果
文本为（以#结束）：
qwertyuiopasdfghjklzxcvbnm1230456789qiajszntryhedjskpaidojhbryueijwskpajsvdiobjkfh56498guyhsd16514 4685432sa1dguhybiasfunom489  5631a65sd4fa 498f4 a9w8#
打印文本出现各个字符的频度：
		5
a       9
b       4
c       1
d       7
e       3
f       5
g       3
h       6
i       6
j       7
k       4
l       1
m       2
n       3
o       4
p       3
q       2
r       3
s       9
t       2
u       5
v       2
w       3
x       1
y       5
z       2
0       1
1       5
2       2
3       3
4       9
5       6
6       6
7       1
8       6
9       5
编码对应的哈夫曼表
1        ：10001
2       a：0101
3       b：00101
4       c：1000010
5       d：0000
6       e：101111
7       f：10010
8       g：111010
9       h：11000
10      i：11001
11      j：0001
12      k：00110
13      l：1000011
14      m：001001
15      n：111011
16      o：00111
17      p：111100
18      q：010000
19      r：111101
20      s：0110
21      t：010001
22      u：10011
23      v：010010
24      w：111110
25      x：1011100
26      y：10100
27      z：010011
28      0：1011101
29      1：10101
30      2：100000
31      3：111111
32      4：0111
33      5：11010
34      6：11011
35      7：001000
36      8：11100
37      9：10110
请输入需要编码的字符串（以#结束）：
huffman coding#
该字符串编码为：
11000100111001010010001001010111101110001100001000111000011001111011111010
输入需要译文的编码（以#结束）：
11000100111001010010001001010111101110001100001000111000011001111011111010#
编码译文为：
huffman coding
*/
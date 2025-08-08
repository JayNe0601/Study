#include<iostream>
using namespace std;

#define MaxSize 100 // 定义线性表顺序存储的最大长度
struct SeqList{
    int data[MaxSize]; // 用静态数组存放数据元素
    int length; // 顺序表的当前长度
};

// 初始化顺序表
void InitList(SeqList &L){
    L.length = 0;// 初始化顺序表的长度为0
}

// 求表长，返回线性表的长度
int Length(SeqList L){
    return L.length;
}

//按值查找操作，在表中查找具有给定关键子值的元素
int LocateElem(SeqList L, int e){
    int n = Length(L);
    for(int i = 0; i < n; i++) if(L.data[i] == e) return i + 1; // 数组下标从0开始，所以返回 i + 1
    return 0; // 查找失败，返回0
}

//按位查找操作，获取表中给定位置的元素的值
int GetElem(SeqList L, int i) {
    if(i < 1 || i > Length(L)) return 0; // 位置i不合法
    return L.data[i - 1]; // 数组下标从0开始，所以返回 i - 1
}

// 插入操作，在表的指定位置插入指定元素
bool ListInsert(SeqList &L, int i, int e) {
    int n = Length(L);// 表长
    if(i < 1 || i > n + 1) return false; // i值不合法
    if(n == MaxSize) return false; // 当前存储空间已满
    for(int j = n; j >= i; j--) L.data[j] = L.data[j - 1]; // 将第i个元素及之后的元素后移
    L.data[i - 1] = e; // 在位置i处放入e
    L.length++; // 线性表长度加1
    return true;
}

// 删除操作，删除表中指定位置的元素
bool ListDelete(SeqList &L, int i, int &e) {
    int n = Length(L);// 表长
    if(i < 1 || i > n) return false; // i值不合法
    if(L.length == 0) return false; // 线性表为空
    e = L.data[i - 1]; // 被删除的元素赋值给e
    for(int j = i; j < n; j++) L.data[j - 1] = L.data[j]; // 将第i个元素之后的元素前移
    L.length--; // 线性表长度减1
    return true;
}

// 输出顺序表中的所有元素
void PrintList(SeqList L) {
    int n = Length(L);
    for(int i = 0; i < n; i++) cout << L.data[i] << ((i == n - 1) ? '\n' : ' ');
}

//判空操作
bool Empty(SeqList L) {
    int n = Length(L);
    return (n == 0) ? true : false;// 长度为0，返回true；否则返回false
}

// 销毁顺序表，并释放线性表的空间
void DestroyList(SeqList &L) {
    L.length = 0;
}// 释放空间


int main() {
    SeqList L;
    InitList(L);
    cout << "初始化后表是否为空表：" << (Empty(L) ? "是" : "否") << endl;
    ListInsert(L, 1, 1);
    cout << "插入元素1后表长为：" << Length(L) << endl;
    cout << "表为：";
    PrintList(L);
    cout << "表是否为空表：" << (Empty(L) ? "是" : "否") << endl;
    ListInsert(L, 1, 2);
    cout << "插入元素2后表长为：" << Length(L) << endl;
    cout << "表为：";
    PrintList(L); // 2 1
    int e = 2;
    cout << "元素" << e << "的位置为：" << LocateElem(L, e) << endl; // 1
    cout << "元素3：" << (LocateElem(L, 3) == 0 ? "不存在" : "存在") << endl; // 0
    cout << "第1个元素的值为：" << GetElem(L, 1) << endl; // 2
    ListDelete(L, 1, e);
    cout << "删除第1个元素" << e << "后表为：";
    PrintList(L); // 1
    DestroyList(L);
    cout << "销毁后表是否为空表：" << (Empty(L) ? "是" : "否") << endl; // 1
    cout << "表长为：" << Length(L) << endl; // 0
    return 0;
}
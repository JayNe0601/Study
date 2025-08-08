#include<iostream>
using namespace std;

struct DNode{
    int data;
    DNode *prior, *next;
};
typedef DNode* DLinkList;

// 初始化循环双链表
bool InitList(DLinkList &L) {
    L = new DNode;
    L->prior = L;
    L->next = L;
    return true;
}

// 循环双链表插入（前插法）
bool ListInsert(DLinkList &L, int i, int e) {
    DNode *p = L->next;
    int j = 0;
    while(p != L && j < i - 1) {
        p = p->next;
        j++;
    }
    if(j != i-1) return false;
    DNode *s = new DNode{e, p->prior, p};
    p->prior->next = s;
    p->prior = s;
    return true;
}

// 循环双链表删除
bool ListDelete(DLinkList &L, int i, int &e) {
    DNode *p = L->next;
    int j = 0;
    while(p != L && j < i-1) {
        p = p->next;
        j++;
    }
    if(p == L) return false;

    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
    return true;
}

// 遍历输出
void PrintList(DLinkList L) {
    DNode *p = L->next;
    while(p != L) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main() {
    DLinkList L;
    InitList(L);
    
    // 测试插入
    for(int i = 1; i <= 5; i++) ListInsert(L, i, i * 10);
    
    cout << "循环双链表内容：";
    PrintList(L);  // 应输出：10 20 30 40 50
    
    // 测试删除
    int del;
    ListDelete(L, 3, del);
    cout << "删除第三个元素(" << del << ")后：";
    PrintList(L);  // 应输出：10 20 40 50
}
#include<iostream>
using namespace std;

struct LNode{
    int data;
    LNode *next;
};
typedef LNode* LinkList;

// 初始化循环单链表
bool InitList(LinkList &L) {
    L = new LNode();
    L->next = L;  // 头节点自循环
    return true;
}

// 循环单链表求表长
int Length(LinkList L) {
    int len = 0;
    LNode *p = L->next;
    while(p != L) {  // 循环终止条件
        len++;
        p = p->next;
    }
    return len;
}

// 插入操作（保持循环特性）
bool ListInsert(LinkList &L, int i, int e) {
    LNode *p = L;
    int j = 0;
    while(p->next != L && j < i-1) {  // 遍历条件调整
        p = p->next;
        j++;
    }
    if(j != i-1) return false;
    LNode *s = new LNode();
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 删除操作
bool ListDelete(LinkList &L, int i, int &e) {
    LNode *p = L;
    int j = 0;
    while(p->next != L && j < i-1) {
        p = p->next;
        j++;
    }
    if(p->next == L) return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    delete q;
    return true;
}

// 循环单链表打印
void PrintList(LinkList L) {
    LNode *p = L->next;
    while(p != L) {
        cout << p->data << (p->next == L ? '\n' : ' ');
        p = p->next;
    }
}

// 测试用例
int main() {
    LinkList L;
    InitList(L);
    // 测试插入和遍历
    for(int i = 1; i <= 5; i++) ListInsert(L, i, i*10);
    cout << "循环单链表内容：";
    PrintList(L);  // 应输出：10 20 30 40 50
    // 测试删除
    int deleted;
    ListDelete(L, 3, deleted);
    cout << "删除第三个元素（" << deleted << "）后：";
    PrintList(L);  // 应输出：10 20 40 50
}
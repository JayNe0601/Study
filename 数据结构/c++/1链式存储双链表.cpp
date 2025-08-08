#include<iostream>
using namespace std;

struct DNode{ //定义双链表节点类型
    int data; // 数据域
    DNode *prior, *next; // 指针域，前驱和后继指针
};
typedef DNode* DLinkList; // 定义双链表类型

// 初始化双链表（循环双链表）
bool InitList(DLinkList &L) {
    L = new DNode();
    L->prior = L;
    L->next = new DNode();
    L->next->prior = L;
    L->next->next = NULL;    
    return true;
}

// 求表长，返回双链表的长度
int Length(DLinkList L){
    int len = 0;// 统计表长
    DNode *p = L->next;// p指向头指针
    while(p->next != NULL){
        p = p->next; // p指向下一个结点
        len++; // 长度加1
    }
    return len;
}

//按值查找操作，在双链表中查找具有给定关键子值的元素
int LocateElem(DLinkList L, int e){
    int len = 0;// 统计表长
    DNode *p = L->next;// p指向头结点
    while(p != NULL){
        if(p->data == e) return len + 1; // 找到，返回位置
        p = p->next; // p指向下一个结点
        len++; // 长度加1
    }
    return 0; // 查找失败，返回0
}

//按位查找操作，获取表中给定位置的元素的值
int GetElem(DLinkList L, int i) {
    int len = 0;// 统计表长
    DNode *p = L;// p指向头指针
    while(p != NULL){
        p = p->next; // p指向下一个结点
        len++; // 长度加1
        if(len == i) return p->data; // 找到，返回位置
    }
    return 0; // 查找失败，返回0`
}

// 插入操作，在双链表的指定位置插入指定元素
bool ListInsert(DLinkList &L, int i, int e) {
    DNode *p = L;
    int len = 0;
    while(p != NULL && len < i - 1) {// 找到第 i - 1个结点
        p = p->next;
        len++;
    }
    if(p == NULL) return false; // i值不合法
    DNode *s = new DNode(); // 申请一个新结点
    s->data = e;// 新结点数据域赋值为e
    s->next = p->next;// 新结点后继指针域指向p的后继结点
    p->next->prior = s;// p的后继结点的前驱指针域指向s
    s->prior = p;// 新结点后继指针域指向p
    p->next = s;// p的后继指针域指向新结点
    return true;
}

// 删除操作，删除表中指定位置的元素
bool ListDelete(DLinkList &L, int i, int &e) {
    DNode *p = L;
    int len = 0;
    while(p->next != NULL && len < i - 1) {// 找到第 i - 1个结点
        p = p->next;
        len++;
    }
    if(p->next == NULL || len > i - 1) return false; // i值不合法
    DNode *q = p->next; // q指向待删除结点
    e = q->data; // 被删除的元素赋值给e
    p->next = q->next;// p的后继指针域指向q的后继结点
    q->next->prior = p;// q的后继结点的前驱指针域指向p
    delete q; // 释放q结点
    return true;
}

// 输出顺序表中的所有元素
void PrintList(DLinkList L) {
    DNode *p = L->next; // p指向头结点
    while(p->next != NULL){
        cout << p->data << ((p->next->next == NULL) ? '\n' : ' '); // 输出数据域
        p = p->next; // p指向下一个结点
    }
}

//判空操作
bool Empty(DLinkList L) {
    return (L->next->next == NULL) ? true : false;// 头结点指针域为空，返回true；否则返回false
}

// 销毁顺序表，并释放线性表的空间
void DestroyList(DLinkList &L) {
    DNode *p = L->next; // p指向头结点
    while(p->next != NULL){
        DNode *q = p; // q指向p结点
        p = p->next; // p指向下一个结点
        delete q; // 释放q结点
    }
    L->next->next = NULL; // 头节点为空
}// 释放空间


int main() {
    DLinkList L;
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
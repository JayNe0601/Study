#include <iostream>
using namespace std;

typedef struct LinkNode {
    int data;
    LinkNode* next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

// 初始化链队列
void InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = new LinkNode;
    Q.front->next = nullptr;
}

// 判断队列空
bool QueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}

// 入队操作
bool EnQueue(LinkQueue &Q, int x) {
    LinkNode* s = new LinkNode;
    s->data = x;
    s->next = nullptr;
    Q.rear->next = s;
    Q.rear = s;
    return true;
}

// 出队操作
bool DeQueue(LinkQueue &Q, int &x) {
    if (QueueEmpty(Q)) return false;
    LinkNode* p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    delete p;
    return true;
}

// 获取队头元素
bool GetHead(LinkQueue Q, int &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.front->next->data;
    return true;
}

// 销毁队列
void DestroyQueue(LinkQueue &Q) {
    while (Q.front) {
        LinkNode* p = Q.front;
        Q.front = Q.front->next;
        delete p;
    }
    Q.rear = nullptr;
}

// 测试用例
int main() {
    LinkQueue Q;
    InitQueue(Q);

    // 批量入队测试
    for (int i = 1; i <= 5; i++) {
        if (!EnQueue(Q, i * 10)) {
            cout << "入队失败: " << i * 10 << endl;
        }
    }

    // 获取队首
    int head;
    GetHead(Q, head);
    cout << "当前队首: " << head << endl;
	int i = 1; // 测试出队时入队
    // 循环出队
    int val;
    while (!QueueEmpty(Q)) {
    	i++;
        if(i == 3) EnQueue(Q, i);
        DeQueue(Q, val);
        cout << "出队元素: " << val << endl;
    }

    // 空队列测试
    if (!DeQueue(Q, val)) cout << "空队列操作正常" << endl;

    DestroyQueue(Q);
    return 0;
}
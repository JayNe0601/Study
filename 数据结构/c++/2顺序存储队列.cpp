#include <iostream>
using namespace std;

#define MaxSize 100
typedef struct {
    int data[MaxSize];
    int front, rear;
} SqQueue;

// 初始化循环队列
void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

// 判断队列空
bool QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 入队操作
bool EnQueue(SqQueue &Q, int x) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false; // 队满
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

// 出队操作
bool DeQueue(SqQueue &Q, int &x) {
    if (QueueEmpty(Q)) return false; // 队空
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

// 获取队头元素
bool GetHead(SqQueue Q, int &x) {
    if (QueueEmpty(Q)) return false; // 队空
    x = Q.data[Q.front];
    return true;
}

// 测试用例
int main() {
    SqQueue Q;
    InitQueue(Q);

    // 批量入队
    for (int i = 1; i <= 5; i++) if (!EnQueue(Q, i * 10)) break;

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
    if (!DeQueue(Q, val)) cout << "空队列处理正常" << endl;
    
    return 0;
}
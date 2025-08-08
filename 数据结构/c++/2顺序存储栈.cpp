#include <iostream>
using namespace std;

#define MAXSIZE 100 // 栈的最大容量
struct SqStack {
    int data[MAXSIZE];    // 栈存储空间
    int top;         // 栈顶指针(初始化为-1)
};

// 初始化栈
void InitStack(SqStack &S) {
    S.top = -1;
}

// 判断栈空
bool StackEmpty(SqStack S) {
    return S.top == -1;
}

// 入栈操作
bool Push(SqStack &S, int x) {
    if (S.top >= MAXSIZE-1) {
        cout << "[错误] 栈空间不足 (MAXSIZE=" << MAXSIZE << ")" << endl;
        return false;
    }
    S.data[++S.top] = x;
    return true;
}

// 出栈操作
bool Pop(SqStack &S, int &x) {
    if (StackEmpty(S)) {
        cout << "空栈" << endl;
        return false;
    }
    x = S.data[S.top--];
    return true;
}

// 获取栈顶元素
bool GetTop(SqStack S, int &x) {
    if (StackEmpty(S)) {
        cout << "空栈" << endl;
        return false;
    }
    x = S.data[S.top];
    return true;
}

// 销毁栈
void ClearStack(SqStack &S) {
    S.top = -1;
}

// 测试用例
int main() {
    SqStack S;
    InitStack(S);
    
    // 测试入栈
    for (int i = 1; i <= 5; i++) {
        if (!Push(S, i * 10)) break;
    }
    
    // 测试获取栈顶
    int top;
    GetTop(S, top);
    cout << "当前栈顶: " << top << endl;
    
    // 测试出栈
    int x;
    while (!StackEmpty(S)) {
        Pop(S, x);
        cout << "弹出元素: " << x << endl;
    }
    
    ClearStack(S);
    return 0;
}


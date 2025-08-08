#include <iostream>
#include <stack>
using namespace std;

struct CallFrame {
    int n;
    bool is_unsolved;  // 是否未计算
    int result;        // 存储中间结果
    
    CallFrame(int n, bool is_unsolved) : n(n), is_unsolved(is_unsolved), result(0) {}
};

int fibonacci_stack(int n) {
    if (n < 0) throw invalid_argument("n必须为非负整数");
    stack<CallFrame> call_stack;
    call_stack.push(CallFrame(n, true));
    
    while (!call_stack.empty()) {
        CallFrame current = call_stack.top();
        call_stack.pop();
        
        if (current.n == 0) {
            current.result = 0;
        } else if (current.n == 1) {
            current.result = 1;
        } else {
            if (current.is_unsolved) {
                // 未计算：压回当前帧（标记为已计算），并压入子问题
                current.is_unsolved = false;
                call_stack.push(current);
                call_stack.push(CallFrame(current.n - 1, true));
                call_stack.push(CallFrame(current.n - 2, true));
                continue;  // 跳过后续处理，继续处理子问题
            } else {
                // 已计算：获取前两个结果并相加
                int fn1 = current.result;
                int fn2 = call_stack.top().result;
                call_stack.pop();
                current.result = fn1 + fn2;
            }
        }
        
        // 将当前结果传递给上一层
        if (!call_stack.empty()) {
            call_stack.top().result = current.result;
        }
    }
    
    return (n == 0 || n == 1) ? n : call_stack.top().result;
}

int main() {
    cout << fibonacci_stack(5) << endl;  // 输出：5
    cout << fibonacci_stack(10) << endl; // 输出：55
    return 0;
}
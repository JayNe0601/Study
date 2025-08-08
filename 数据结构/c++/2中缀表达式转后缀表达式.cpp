#include<bits/stdc++.h>
using namespace std;

int main() {
    map<char, int> mp;
    mp['+'] = 1;// 加减优先级相同
    mp['-'] = 1;
    mp['*'] = 2;// 乘除优先级相同，高于加减
    mp['/'] = 2;
    stack<char> s;
    string str, ans = "";
    cin >> str;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')') { // 运算符
            if(s.empty() || str[i] == '(' || s.top() == '(') s.push(str[i]);// 栈为空，或者当前运算符为左括号，或者栈顶元素为左括号，直接入栈
            else if(str[i] == ')') {// 遇到右括号出栈运算符，且删除左括号
                while(!s.empty() && s.top() != '(') {
                    ans += s.top();
                    s.pop();
                }
                s.pop();
            }
            else if(mp[str[i]] > mp[s.top()]) s.push(str[i]);// 当前运算符优先级大于栈顶运算符，直接入栈
            else {// 当前运算符优先级小于等于栈顶运算符，出栈运算符，直到栈为空，或者栈顶运算符优先级小于当前运算符
                while(!s.empty() && mp[str[i]] <= mp[s.top()]) {
                    ans += s.top();
                    s.pop();
                }
                s.push(str[i]);
            }
        }
        else ans += str[i];// 操作数直接入栈
    }
    while(!s.empty()) { // 栈中剩余运算符直接出栈
        ans += s.top();
        s.pop();
    }
    cout << ans;
}
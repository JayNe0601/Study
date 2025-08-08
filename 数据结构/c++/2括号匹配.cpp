#include<bits/stdc++.h>
using namespace std;

int main() {
    stack<char> s;
    string str;
    getline(cin, str);// 读入整行，包括空格
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '(' || str[i] == '[') s.push(str[i]);// 左括号入栈
        else if(str[i] == ')' || str[i] == ']') {
            if(s.empty()) {// 栈为空，说明没有左括号匹配
                cout << "NO" << endl;
                return 0;
            }
            char c = s.top();// 获取栈顶元素
            if((str[i] == ')' && c == '(') || (str[i] == ']' && c == '[')) s.pop();// 右括号匹配，栈顶元素出栈
            else {// 右括号不匹配
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    if(s.empty()) cout << "YES" << endl;// 栈为空，说明所有左括号都有匹配
    else cout << "NO" << endl;// 栈不为空，说明有左括号没有匹配
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    stack<ll> s;
    string str;
    ll ans = 0;
    getline(cin, str);// 输入每一个操作符和运算符用空格隔开
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == ' ') continue;
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ) {
            if(!s.empty()) {
                ll y = s.top();
                s.pop();
                ll x = s.top();
                s.pop();
                if(str[i] == '+') s.push(x + y);
                else if(str[i] == '-') s.push(x - y);
                else if(str[i] == '*') s.push(x * y);
                else if(str[i] == '/') s.push(x / y);
            }
        }
        else {
            ll num = 0;
            while(str[i] >= '0' && str[i] <= '9' && i < str.size()) { // 得到数，并防止越界
                num = num * 10 + str[i] - '0';
                i++;
            }
            s.push(num);
            i -= 1; // 因为for循环会i++，所以要减1
        }
    }
    cout << s.top();
    return 0;
}
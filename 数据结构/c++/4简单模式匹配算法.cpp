#include <iostream>
#include <string>
using namespace std;

int Index(string s, string t) {
    if(s.size() < t.size()) return -1;
    int i = 0, j = 0;
    while(i < s.size() && j < t.size()) {
        if(s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
        if(j == t.size()) return i - j + 1; // 返回匹配的第一个字符的位置（非下标，位置从 1 开始）
    }
    return -1; // 匹配失败返回 -1
}

int main() {
    string s, t;
    cin >> s >> t;
    cout << Index(s, t);
}
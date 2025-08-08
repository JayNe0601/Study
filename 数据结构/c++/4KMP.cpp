#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> get_next(string s) {
    int prefix_len = 0, i = 1;
    vector<int> next;
    next.push_back(0);
    while (i < s.size()) {
        if (s[i] == s[prefix_len]) { // 匹配时，将前缀指针指向 next 数组中对应的位置
            prefix_len++;
            next.push_back(prefix_len);
            i++;
        }
        else {
            if(prefix_len == 0) { // 前缀指针指向第一个字符时，不匹配时，将 next 数组对应位置赋值为 0
                next.push_back(0);
                i++;
            }
            else prefix_len = next[prefix_len - 1]; // 不匹配时，将前缀指针指向 next 数组中对应的位置
        }
    }
    return next;
}

int kmp_search(string t, string s) { //  主串为t, 子串为s
    vector<int> next = get_next(s);
    int i = 0, j = 0;
    while(i < t.size() && j < s.size()) {
        if(t[i] == s[j]) {// 匹配成功
            i++;
            j++;
        }
        else if(j > 0) j = next[j - 1]; // 匹配失败
        else i++; // 子串第一个字符不匹配，主串往后移动
        if(j == s.size()) return i - j + 1; // 匹配成功，返回匹配的第一个字符的位置（非下标，位置从 1 开始）
    }
    return -1; // 匹配失败返回 -1
}

int main() {
    string main_str, pattern;
    cout << "输入主串：";
    cin >> main_str;
    cout << "输入模式串：";
    cin >> pattern;
    
    int pos = kmp_search(main_str, pattern);
    if(pos != -1)
        cout << "匹配位置(从1开始): " << pos << endl;
    else
        cout << "匹配失败" << endl;
    return 0;
}
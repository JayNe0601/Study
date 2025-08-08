#include <iostream>
#include <cstring>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct {
    char ch[MAXSIZE];
    int length;
} SSString;

// 赋值操作
int StrAssign(SSString &T, const char *chars) {
    int len = strlen(chars);
    if(len > MAXSIZE) return ERROR;
    for(int i = 0; i < len; i++) T.ch[i] = chars[i];
    T.length = len;
    return OK;
}

// 复制操作
int strCopy(SSString &T, SSString S) {
    if(S.length > MAXSIZE) return ERROR;
    for(int i = 0; i < S.length; i++) T.ch[i] = S.ch[i];
    T.length = S.length;
    return OK;
}

// 判空操作
int strEmpty(SSString S) {
    return S.length == 0 ? TRUE : FALSE;
}

// 比较操作
int strCompare(SSString S, SSString T) {
    int min_len = S.length < T.length ? S.length : T.length;
    for(int i = 0; i < min_len; i++) if(S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
    return S.length - T.length;
}

// 求串长
int strLength(SSString S) {
    return S.length;
}

// 求子串
int Substring(SSString &Sub, SSString S, int pos, int len) {
    if(pos<1 || pos>S.length || len<0 || pos+len-1>S.length) return ERROR;
    for(int i = 0; i < len; i++) Sub.ch[i] = S.ch[pos - 1 + i];
    Sub.length = len;
    return OK;
}

// 串联接
int concat(SSString &T, SSString S1, SSString S2) {
    if(S1.length + S2.length > MAXSIZE) {
        for(int i = 0; i < MAXSIZE; i++) T.ch[i] = (i < S1.length) ? S1.ch[i] : S2.ch[i - S1.length];
        T.length = MAXSIZE;
        return ERROR;
    }
    for(int i = 0; i < S1.length; i++) T.ch[i] = S1.ch[i];
    for(int i = 0; i < S2.length; i++) T.ch[S1.length + i] = S2.ch[i];
    T.length = S1.length + S2.length;
    return OK;
}

// 定位操作（KMP算法）
int Index(SSString S, SSString T) {
    int next[T.length];
    next[0] = -1;
    int i = 0, j = -1;
    while(i < T.length - 1) {
        if(j == -1 || T.ch[i] == T.ch[j]) {
            i++;
			j++;
            next[i] = (T.ch[i] != T.ch[j]) ? j : next[j];
        } 
		else j = next[j];
    }
    i = 0; 
	j = 0;
    while(i < S.length && j < T.length) {
        if(j == -1 || S.ch[i] == T.ch[j]) {
            i++; 
			j++;
        } 
		else j = next[j];
    }
    return j >= T.length ? i - T.length + 1 : 0;
}

// 清空操作
void ClearString(SSString &S) {
    S.length = 0;
}

// 销毁串
void DestroyString(SSString &S) {
    ClearString(S);
}

int main() {
    SSString s1, s2, concatStr;
    
    // 测试赋值操作
    StrAssign(s1, "HelloData");
    StrAssign(s2, "Structure");
    
    // 测试连接操作
    concat(concatStr, s1, s2);
    cout << "连接结果：";
    for(int i = 0; i < concatStr.length; i++) cout << concatStr.ch[i];
    
    // 测试子串操作
    SSString sub;
    Substring(sub, s1, 3, 4);
    cout << "\n子串结果：";
    for(int i = 0; i < sub.length; i++) cout << sub.ch[i];
    
    // 测试定位操作
    SSString pattern;
    StrAssign(pattern, "Data");
    cout << "\n模式串位置：" << Index(s1, pattern);
    
    return 0;
}
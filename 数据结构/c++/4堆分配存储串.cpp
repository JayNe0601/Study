#include <iostream>
#include <cstring>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct {
    char *ch;
    int length;
} HString;

// 初始化空串
void InitString(HString &S) {
    S.ch = nullptr;
    S.length = 0;
}

// 赋值操作
int StrAssign(HString &T, const char *chars) {
    if(T.ch) delete[] T.ch;
    
    int len = strlen(chars);
    if(len == 0) {
        T.ch = nullptr;
        T.length = 0;
        return OK;
    }
    
    T.ch = new char[len + 1];
    if(!T.ch) return ERROR;
    
    strcpy(T.ch, chars);
    T.length = len;
    return OK;
}

// 复制操作
int strCopy(HString &T, HString S) {
    if(T.ch) delete[] T.ch;
    
    if(S.length == 0) {
        T.ch = nullptr;
        T.length = 0;
        return OK;
    }
    
    T.ch = new char[S.length+1];
    if(!T.ch) return ERROR;
    
    strcpy(T.ch, S.ch);
    T.length = S.length;
    return OK;
}

// 判空操作
int strEmpty(HString S) {
    return S.length == 0 ? TRUE : FALSE;
}

// 比较操作
int strCompare(HString S, HString T) {
    return strcmp(S.ch, T.ch);
}

// 求串长
int strLength(HString S) {
    return S.length;
}

// 求子串
int Substring(HString &Sub, HString S, int pos, int len) {
    if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
        return ERROR;
    
    if(Sub.ch) delete[] Sub.ch;
    
    if(len == 0) {
        Sub.ch = nullptr;
        Sub.length = 0;
        return OK;
    }
    
    Sub.ch = new char[len + 1];
    strncpy(Sub.ch, S.ch + pos - 1, len);
    Sub.ch[len] = '\0';
    Sub.length = len;
    return OK;
}

// 串联接
int concat(HString &T, HString S1, HString S2) {
    if(T.ch) delete[] T.ch;
    
    T.length = S1.length + S2.length;
    T.ch = new char[T.length + 1];
    
    strcpy(T.ch, S1.ch);
    strcat(T.ch, S2.ch);
    return OK;
}

// 清空操作
void ClearString(HString &S) {
    if(S.ch) {
        delete[] S.ch;
        S.ch = nullptr;
    }
    S.length = 0;
}

// 销毁串
void DestroyString(HString &S) {
    ClearString(S);
}

int main() {
    HString s1, s2, s3;
    InitString(s1);
    InitString(s2);
    
    // 测试赋值操作
    StrAssign(s1, "Data");
    StrAssign(s2, "Structure");
    
    // 测试连接操作
    concat(s3, s1, s2);
    cout << "连接结果：" << s3.ch << endl;
    
    // 测试子串操作
    HString sub;
    InitString(sub);
    Substring(sub, s3, 3, 5);
    cout << "子串结果：" << sub.ch << endl;
    
    // 内存释放
    DestroyString(s1);
    DestroyString(s2);
    DestroyString(s3);
    DestroyString(sub);
    
    return 0;
}
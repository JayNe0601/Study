#include <iostream>
using namespace std;

#define MAX 100
int a[MAX]; // 有序线性表(从1号位置开始存储)
int length = 0;

// 初始化有序线性表
void InitList(int arr[], int n) {
    if (n >= MAX) {
        cout << "线性表长度超过最大值!" << endl;
        return;
    }
    // 复制并保持有序性
    for (int i = 0; i < n; i++) a[i + 1] = arr[i];
    length = n;
}

// 有序表的顺序查找算法
int Search_Seq(int key) {
    // 从表头开始查找
    for (int i = 1; i <= length; i++) {
        if (a[i] == key) return i; // 找到返回位置
        else if (a[i] > key) return 0; // 有序表特性：后续元素更大，无需继续查找
    }
    return 0; // 查找失败
}

// 显示线性表
void DisplayList() {
    cout << "有序线性表元素: ";
    for (int i = 1; i <= length; i++) cout << a[i] << " ";
    cout << endl;
}

int main() {
    // 测试有序表
    int sortedData[] = {12, 23, 34, 45, 56, 78, 90};
    int n = sizeof(sortedData) / sizeof(sortedData[0]);
    
    InitList(sortedData, n);
    DisplayList();
    
    // 测试查找功能
    int key = 45;
    int result = Search_Seq(key);
    if (result != 0) cout << "查找元素" << key << "成功，位置: " << result << endl;
    else  cout << "查找元素" << key << "失败!" << endl;
    
    key = 66;
    result = Search_Seq(key);
    if (result != 0) cout << "查找元素" << key << "成功，位置: " << result << endl;
    else  cout << "查找元素" << key << "失败!" << endl;
    
    return 0;
}
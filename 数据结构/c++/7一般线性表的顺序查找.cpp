#include <iostream>
using namespace std;

#define MAX 101
int a[MAX]; // 0号位置用作哨兵
int length = 0;

// 初始化线性表
void InitList(int arr[], int n) {
    if (n >= MAX) {
        cout << "线性表长度超过最大值!" << endl;
        return;
    }
    for (int i = 0; i < n; i++) a[i + 1] = arr[i]; // 从1号位置开始存储数据
    length = n;
}

// 顺序查找算法（带哨兵优化）
int Search_Seq(int key) {
    a[0] = key; // 设置哨兵
    int i = length;
    // 从后往前查找，不需要判断数组越界
    while (a[i] != key) i--;
    return i; // 若 i = 0则查找失败，否则返回下标
}

// 显示线性表
void DisplayList() {
    cout << "线性表元素: ";
    for (int i = 1; i <= length; i++) cout << a[i] << " ";
    cout << endl;
}

int main() {
    int testData[] = {34, 12, 56, 78, 90, 23, 45};
    int n = sizeof(testData) / sizeof(testData[0]); // 求数组长度
    // 初始化线性表
    InitList(testData, n);
    DisplayList();
    
    // 测试查找功能
    int key = 78;
    int result = Search_Seq(key);
    if (result != 0) cout << "查找元素" << key << "成功，位置: " << result << endl << "元素值为：" << a[result] << endl;
    else cout << "查找元素" << key << "失败!" << endl;
    
    key = 100;
    result = Search_Seq(key);
    if (result != 0) cout << "查找元素" << key << "成功，位置: " << result << endl;
    else cout << "查找元素" << key << "失败!" << endl;
    
    return 0;
}
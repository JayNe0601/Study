#include <iostream>
#include <algorithm>
using namespace std;

// 计数排序（支持非负整数排序）
// 参数：a-待排序数组(1-based)，b-输出数组(1-based)，n-元素个数
void CountSort(int a[], int b[], int n) {
    if (n <= 0) return;

    // 找出数组中的最大值
    int maxVal = a[1];
    for (int i = 2; i <= n; i++) if (a[i] > maxVal) maxVal = a[i];

    // 创建计数数组并初始化
    int* c = new int[maxVal + 1]();  // 初始化为0

    // 1. 计数阶段：统计每个元素出现的次数
    for (int i = 1; i <= n; i++) c[a[i]]++;

    // 2. 累加阶段：计算每个元素在输出数组中的位置
    for (int i = 1; i <= maxVal; i++) c[i] += c[i - 1];

    // 3. 分配阶段：将元素放到输出数组的正确位置（从后往前保证稳定性）
    for (int i = n; i >= 1; i--) {
        b[c[a[i]]] = a[i];
        c[a[i]]--;
    }

    // 释放临时内存
    delete[] c;
}

// 初始化测试数组
void initArray(int a[], int n, int type) {
    switch (type) {
        case 1: // 随机无序数组
            a[1] = 4; a[2] = 2; a[3] = 2; a[4] = 8; a[5] = 3; a[6] = 3; a[7] = 1; a[8] = 5;
            break;
        case 2: // 已排序数组
            a[1] = 1; a[2] = 2; a[3] = 2; a[4] = 3; a[5] = 3; a[6] = 4; a[7] = 5; a[8] = 8;
            break;
        case 3: // 逆序数组
            a[1] = 8; a[2] = 5; a[3] = 4; a[4] = 3; a[5] = 3; a[6] = 2; a[7] = 2; a[8] = 1;
            break;
        case 4: // 重复元素数组
            a[1] = 5; a[2] = 5; a[3] = 5; a[4] = 5; a[5] = 5; a[6] = 5; a[7] = 5; a[8] = 5;
            break;
        case 5: // 单元素数组
            a[1] = 10; // 仅一个元素
            break;
    }
}

// 打印数组
void printArray(int a[], int n) {
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

// 测试计数排序
void testCountSort() {
    const int MAX_SIZE = 100;
    int a[MAX_SIZE];  // 原始数组
    int b[MAX_SIZE];  // 排序结果数组
    int n;

    // 测试场景1: 随机无序数组
    cout << "测试场景1: 随机无序数组" << endl;
    n = 8;
    initArray(a, n, 1);
    cout << "排序前: ";
    printArray(a, n);
    CountSort(a, b, n);
    cout << "排序后: ";
    printArray(b, n);
    cout << endl;

    // 测试场景2: 已排序数组
    cout << "测试场景2: 已排序数组" << endl;
    n = 8;
    initArray(a, n, 2);
    cout << "排序前: ";
    printArray(a, n);
    CountSort(a, b, n);
    cout << "排序后: ";
    printArray(b, n);
    cout << endl;

    // 测试场景3: 逆序数组
    cout << "测试场景3: 逆序数组" << endl;
    n = 8;
    initArray(a, n, 3);
    cout << "排序前: ";
    printArray(a, n);
    CountSort(a, b, n);
    cout << "排序后: ";
    printArray(b, n);
    cout << endl;

    // 测试场景4: 重复元素数组
    cout << "测试场景4: 重复元素数组" << endl;
    n = 8;
    initArray(a, n, 4);
    cout << "排序前: ";
    printArray(a, n);
    CountSort(a, b, n);
    cout << "排序后: ";
    printArray(b, n);
    cout << endl;

    // 测试场景5: 单元素数组
    cout << "测试场景5: 单元素数组" << endl;
    n = 1;
    initArray(a, n, 5);
    cout << "排序前: ";
    printArray(a, n);
    CountSort(a, b, n);
    cout << "排序后: ";
    printArray(b, n);
    cout << endl;
}

int main() {
    testCountSort();
    system("pause");
    return 0;
}
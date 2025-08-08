#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

// 辅助函数：求数据的最大位数
int maxbit(int data[], int n) {
    int maxData = data[1];  // 1-based索引，从第一个元素开始
    // 先求出最大数
    for (int i = 2; i <= n; ++i) if (maxData < data[i]) maxData = data[i];
    // 求最大数的位数
    int d = 1;
    int p = 10;
    while (maxData >= p) {
        maxData /= 10;
        ++d;
    }
    return d;
}

// 基数排序（LSD法）
void RadixSort(int data[], int n) {
    int d = maxbit(data, n);       // 获取最大位数

    for (int digit = 1; digit <= d; digit++) {  // 修正循环变量名冲突
        queue<int> q[10];          // 0-9共10个桶
        int* temp = new int[n + 1]; // 临时数组(1-based)
        int k = 1;                 // 临时数组指针
        // 计算当前位权重（替换pow避免精度问题）
        int weight = 1;
        for (int i = 1; i < digit; i++) weight *= 10;
        // 将数据分配到桶中
        for (int j = 1; j <= n; j++) q[(data[j] / weight) % 10].push(data[j]);

        // 从桶中收集数据
        for (int j = 0; j < 10; j++) {             // 修正桶索引变量
            while (!q[j].empty()) {                // 使用当前桶j而非digit
                temp[k++] = q[j].front();          // 获取队首元素
                q[j].pop();                        // 弹出队首元素
            }
        }
        // 将临时数组复制回原数组
        for (int j = 1; j <= n; j++) data[j] = temp[j];
        cout << "第 " << digit << " 轮结果：";
        for (int j = 1; j <= n; j++) cout << data[j] << ((j == n) ? '\n' : ' ');
        delete[] temp;  // 释放临时数组
    }
}

// 初始化测试数组
void initArray(int a[], int n, int type) {
    switch (type) {
        case 1: // 随机无序数组
            a[1] = 64; a[2] = 8; a[3] = 216; a[4] = 512; a[5] = 27; a[6] = 125; a[7] = 343; a[8] = 1;
            break;
        case 2: // 已排序数组
            a[1] = 1; a[2] = 8; a[3] = 27; a[4] = 64; a[5] = 125; a[6] = 216; a[7] = 343; a[8] = 512;
            break;
        case 3: // 逆序数组
            a[1] = 512; a[2] = 343; a[3] = 216; a[4] = 125; a[5] = 64; a[6] = 27; a[7] = 8; a[8] = 1;
            break;
        case 4: // 重复元素数组
            a[1] = 16; a[2] = 8; a[3] = 16; a[4] = 8; a[5] = 16; a[6] = 8; a[7] = 16; a[8] = 8;
            break;
        case 5: // 单元素数组
            a[1] = 100; // 仅一个元素
            break;
    }
}

// 打印数组
void printArray(int a[], int n) {
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

// 测试基数排序
void testRadixSort() {
    const int MAX_SIZE = 100;
    int a[MAX_SIZE];
    int n;

    // 测试场景1: 随机无序数组
    cout << "测试场景1: 随机无序数组" << endl;
    n = 8;
    initArray(a, n, 1);
    cout << "排序前: ";
    printArray(a, n);
    RadixSort(a, n);
    cout << "排序后: ";
    printArray(a, n);
    cout << endl;

    // 测试场景2: 已排序数组
    cout << "测试场景2: 已排序数组" << endl;
    n = 8;
    initArray(a, n, 2);
    cout << "排序前: ";
    printArray(a, n);
    RadixSort(a, n);
    cout << "排序后: ";
    printArray(a, n);
    cout << endl;

    // 测试场景3: 逆序数组
    cout << "测试场景3: 逆序数组" << endl;
    n = 8;
    initArray(a, n, 3);
    cout << "排序前: ";
    printArray(a, n);
    RadixSort(a, n);
    cout << "排序后: ";
    printArray(a, n);
    cout << endl;

    // 测试场景4: 重复元素数组
    cout << "测试场景4: 重复元素数组" << endl;
    n = 8;
    initArray(a, n, 4);
    cout << "排序前: ";
    printArray(a, n);
    RadixSort(a, n);
    cout << "排序后: ";
    printArray(a, n);
    cout << endl;

    // 测试场景5: 单元素数组
    cout << "测试场景5: 单元素数组" << endl;
    n = 1;
    initArray(a, n, 5);
    cout << "排序前: ";
    printArray(a, n);
    RadixSort(a, n);
    cout << "排序后: ";
    printArray(a, n);
    cout << endl;
}

int main() {
    testRadixSort();
    system("pause");
    return 0;
}
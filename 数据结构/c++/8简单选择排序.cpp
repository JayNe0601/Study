#include <iostream>
#include <algorithm> // 用于std::swap
using namespace std;

#define MAX 100 // 数组最大容量
int a[MAX]; // 全局数组，采用1-based索引
int length; // 数组长度

// 简单选择排序算法实现
void SelectSort(int a[], int n) {
    for (int i = 1; i <= n - 1; i++) { // i从1开始，符合1-based索引
        int minIndex = i; // 记录最小元素位置
        // 在未排序部分查找最小元素
        for (int j = i + 1; j <= n; j++) if (a[j] < a[minIndex]) minIndex = j; // 更新最小元素位置
        // 如果最小元素不是当前位置，则交换
        if (minIndex != i) swap(a[i], a[minIndex]);
    }
}

// 辅助函数：打印数组元素
void printArray(int arr[], int len) {
    for (int i = 1; i <= len; i++) cout << arr[i] << " ";
    cout << endl;
}

// 辅助函数：初始化数组（1-based索引）
void initArray(int arr[], int len, const int source[]) {
    for (int i = 1; i <= len; i++) arr[i] = source[i - 1];
    length = len;
}

// 测试简单选择排序函数
void testSelectSort() {
    cout << "=== 简单选择排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    int test1[] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    initArray(a, n1, test1);
    cout << "测试用例1（随机无序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n1);
    SelectSort(a, n1);
    cout << "排序后：";
    printArray(a, n1);
    cout << endl;

    // 测试用例2：已经有序的数组
    int test2[] = {12, 23, 34, 45, 56, 67};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    initArray(a, n2, test2);
    cout << "测试用例2（已排序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n2);
    SelectSort(a, n2);
    cout << "排序后：";
    printArray(a, n2);
    cout << endl;

    // 测试用例3：逆序数组
    int test3[] = {98, 76, 54, 32, 10};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    initArray(a, n3, test3);
    cout << "测试用例3（逆序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n3);
    SelectSort(a, n3);
    cout << "排序后：";
    printArray(a, n3);
    cout << endl;

    // 测试用例4：包含重复元素的数组
    int test4[] = {55, 33, 77, 33, 99, 22, 55};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    initArray(a, n4, test4);
    cout << "测试用例4（含重复元素）：" << endl;
    cout << "排序前：";
    printArray(a, n4);
    SelectSort(a, n4);
    cout << "排序后：";
    printArray(a, n4);
    cout << endl;

    // 测试用例5：单元素数组
    int test5[] = {42};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    initArray(a, n5, test5);
    cout << "测试用例5（单元素数组）：" << endl;
    cout << "排序前：";
    printArray(a, n5);
    SelectSort(a, n5);
    cout << "排序后：";
    printArray(a, n5);
}

int main() {
    testSelectSort();
    return 0;
}
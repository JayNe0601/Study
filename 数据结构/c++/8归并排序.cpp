#include <iostream>
using namespace std;

#define MAX 100 // 数组最大容量
int a[MAX]; // 全局数组，采用1-based索引
int length; // 数组长度

// 合并两个有序子序列：将a[low..mid]和a[mid+1..high]合并为有序序列
void Merge(int a[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = 0; // k为临时数组b的下标
    int *b = new int[high - low + 1]; // 动态分配临时数组
    // 将两个子序列中的元素按顺序放入临时数组
    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    // 将剩余元素复制到临时数组
    while (i <= mid) b[k++] = a[i++];
    while (j <= high) b[k++] = a[j++];
    // 将临时数组中的元素复制回原数组
    for (i = low, k = 0; i <= high; i++, k++) a[i] = b[k];
    delete[] b; // 释放动态分配的内存
}

// 归并排序算法：递归划分并排序
void MergeSort(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2; // 计算中间位置
        MergeSort(a, low, mid); // 对左子序列递归排序
        MergeSort(a, mid + 1, high); // 对右子序列递归排序
        Merge(a, low, mid, high); // 合并两个有序子序列
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

// 测试归并排序函数
void testMergeSort() {
    cout << "=== 归并排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    int test1[] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    initArray(a, n1, test1);
    cout << "测试用例1（随机无序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n1);
    MergeSort(a, 1, n1);
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
    MergeSort(a, 1, n2);
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
    MergeSort(a, 1, n3);
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
    MergeSort(a, 1, n4);
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
    MergeSort(a, 1, n5);
    cout << "排序后：";
    printArray(a, n5);
}

int main() {
    testMergeSort();
    return 0;
}
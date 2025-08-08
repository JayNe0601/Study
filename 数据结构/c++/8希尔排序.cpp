

#include <iostream>
using namespace std;

// 希尔排序函数实现
void ShellSort(int a[], int n) {
    int dk, i, j;
    // 增量序列从n/2开始，逐步减半直至1
    for (dk = n / 2; dk >= 1; dk = dk / 2) {
        // 对每个子序列进行直接插入排序
        for (i = dk + 1; i <= n; i++) { // 若当前元素小于其所在子序列的前一个元素，需要插入排序
            if (a[i] < a[i - dk]) {
                a[0] = a[i]; // 寻找插入位置
                for (j = i - dk; j > 0 && a[0] < a[j]; j -= dk) a[j + dk] = a[j];  // 记录后移
                a[j + dk] = a[0];  // 插入到正确位置
            }
        }
    }
}

// 打印数组元素
void printArray(int a[], int n) {
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

// 初始化数组（1-based索引）
void initArray(int a[], int arr[], int n) {
    for (int i = 0; i < n; i++) a[i + 1] = arr[i];
}

// 测试希尔排序函数
void testShellSort() {
    cout << "=== 希尔排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    int test1[11], arr1[] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    initArray(test1, arr1, n1);
    cout << "测试用例1（随机无序数组）：" << endl;
    cout << "排序前：";
    printArray(test1, n1);
    ShellSort(test1, n1);
    cout << "排序后：";
    printArray(test1, n1);
    cout << endl;

    // 测试用例2：已经有序的数组
    int test2[6], arr2[] = {12, 23, 34, 45, 56};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    initArray(test2, arr2, n2);
    cout << "测试用例2（已排序数组）：" << endl;
    cout << "排序前：";
    printArray(test2, n2);
    ShellSort(test2, n2);
    cout << "排序后：";
    printArray(test2, n2);
    cout << endl;

    // 测试用例3：逆序数组
    int test3[6], arr3[] = {98, 76, 54, 32, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    initArray(test3, arr3, n3);
    cout << "测试用例3（逆序数组）：" << endl;
    cout << "排序前：";
    printArray(test3, n3);
    ShellSort(test3, n3);
    cout << "排序后：";
    printArray(test3, n3);
    cout << endl;

    // 测试用例4：包含重复元素的数组
    int test4[7], arr4[] = {55, 33, 77, 33, 99, 22};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    initArray(test4, arr4, n4);
    cout << "测试用例4（含重复元素）：" << endl;
    cout << "排序前：";
    printArray(test4, n4);
    ShellSort(test4, n4);
    cout << "排序后：";
    printArray(test4, n4);
    cout << endl;

    // 测试用例5：单元素数组
    int test5[2], arr5[] = {42};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    initArray(test5, arr5, n5);
    cout << "测试用例5（单元素数组）：" << endl;
    cout << "排序前：";
    printArray(test5, n5);
    ShellSort(test5, n5);
    cout << "排序后：";
    printArray(test5, n5);
}

int main() {
    testShellSort();
    return 0;
}
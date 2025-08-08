#include <iostream>
using namespace std;
#define MAX 100 // 数组最大容量
int a[MAX]; // 全局数组，a[0]未使用，从a[1]开始存储数据
int length; // 数组长度

// 划分函数：将数组划分为两部分，返回枢轴位置
int Partition(int a[], int i, int j) {
    int pivot = a[i]; // 选择第一个元素作为枢轴
    while (i < j) { 
        while (i < j && a[j] >= pivot) j--;// 从右向左找到第一个小于枢轴的元素
        a[i] = a[j]; 
        while (i < j && a[i] <= pivot) i++; // 从左向右找到第一个大于枢轴的元素
        a[j] = a[i];
    }
    a[i] = pivot; // 将枢轴放到最终位置
    return i; // 返回枢轴位置
}

// 快速排序递归函数
void QuickSort(int a[], int low, int high) {
    if (low < high) {
        int pivotpos = Partition(a, low, high); // 进行划分
        QuickSort(a, low, pivotpos - 1); // 对左子表递归排序
        QuickSort(a, pivotpos + 1, high); // 对右子表递归排序
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

// 测试快速排序函数
void testQuickSort() {
    cout << "=== 快速排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    int test1[] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    initArray(a, n1, test1);
    cout << "测试用例1（随机无序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n1);
    QuickSort(a, 1, n1);
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
    QuickSort(a, 1, n2);
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
    QuickSort(a, 1, n3);
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
    QuickSort(a, 1, n4);
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
    QuickSort(a, 1, n5);
    cout << "排序后：";
    printArray(a, n5);
}

int main() {
    testQuickSort();
    return 0;
}
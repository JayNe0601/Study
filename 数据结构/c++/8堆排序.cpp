#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100 // 数组最大容量
int a[MAX]; // 全局数组，采用1-based索引
int length; // 数组长度

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

// 堆调整：将以k为根的子树调整为大根堆
void HeadAdjust(int a[], int k, int len) {
    a[0] = a[k]; // a[0]暂存子树的根节点
    for (int i = 2 * k; i <= len; i *= 2) { // 从左孩子开始
        // 选择左右孩子中较大的一个
        if (i < len && a[i] < a[i + 1]) i++;
        // 如果根节点大于等于最大孩子，则无需调整
        if (a[0] >= a[i]) break;
        else {
            a[k] = a[i]; // 将较大孩子上移
            k = i; // 继续向下调整
        }
    }
    a[k] = a[0]; // 将暂存的根节点放到最终位置
}

// 构建大根堆
void BuildMaxHeap(int a[], int len) {
    // 从最后一个非叶子节点开始向上调整
    for (int i = len / 2; i > 0; i--) HeadAdjust(a, i, len);
}

// 堆排序算法
void HeapSort(int a[], int len) {
    BuildMaxHeap(a, len); // 构建初始大根堆
    cout << "构建大根堆后：";
    printArray(a, len);
    for (int i = len; i > 1; i--) {
        swap(a[1], a[i]); // 将堆顶元素与最后一个元素交换
        HeadAdjust(a, 1, i - 1); // 调整剩余元素为大根堆
    }
}

// 测试堆排序函数
void testHeapSort() {
    cout << "=== 堆排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    int test1[] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    initArray(a, n1, test1);
    cout << "测试用例1（随机无序数组）：" << endl;
    cout << "排序前：";
    printArray(a, n1);
    HeapSort(a, n1);
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
    HeapSort(a, n2);
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
    HeapSort(a, n3);
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
    HeapSort(a, n4);
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
    HeapSort(a, n5);
    cout << "排序后：";
    printArray(a, n5);
}

int main() {
    testHeapSort();
    return 0;
}
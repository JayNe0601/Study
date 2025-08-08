#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 11 
int a[MAX];
int length;

void BubbleSort() {
    for(int i = 1; i < length; i++) {
        bool flag = false; // 标志位，用于判断是否发生交换
        for(int j = length; j > i; j--) {
            if(a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                flag = true; // 发生交换，标志位设为true
            }
        }
        if(!flag) return; // 如果没有发生交换，说明数组已经有序，直接返回
    }
}

// 辅助函数：打印数组
void printArray(int arr[], int len) {
    for (int i = 1; i <= len; i++) cout << arr[i] << " ";
    cout << endl;
}

// 辅助函数：初始化数组
void initArray(int arr[], int len, const int source[]) {
    for (int i = 1; i <= len; i++) arr[i] = source[i - 1];
    length = len;
}

// 测试函数
void testInsertSort() {
    cout << "=== 冒泡排序测试 ===" << endl;

    // 测试用例1：随机无序数组
    cout << "\n[测试1] 随机无序数组: " << endl;
    int test1[] = {38, 49, 65, 97, 76, 13, 27, 49};
    initArray(a, 8, test1);
    cout << "排序前: ";
    printArray(a, length);
    BubbleSort();
    cout << "排序后: ";
    printArray(a, length);

    // 测试用例2：已排序数组
    cout << "\n[测试2] 已排序数组: " << endl;
    int test2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    initArray(a, 8, test2);
    cout << "排序前: ";
    printArray(a, length);
    BubbleSort();
    cout << "排序后: ";
    printArray(a, length);

    // 测试用例3：逆序数组
    cout << "\n[测试3] 逆序数组: " << endl;
    int test3[] = {8, 7, 6, 5, 4, 3, 2, 1};
    initArray(a, 8, test3);
    cout << "排序前: ";
    printArray(a, length);
    BubbleSort();
    cout << "排序后: ";
    printArray(a, length);

    // 测试用例4：含重复元素数组
    cout << "\n[测试4] 含重复元素数组: " << endl;
    int test4[] = {5, 3, 8, 3, 9, 1, 5, 2};
    initArray(a, 8, test4);
    cout << "排序前: ";
    printArray(a, length);
    BubbleSort();
    cout << "排序后: ";
    printArray(a, length);

    // 测试用例5：单元素数组
    cout << "\n[测试5] 单元素数组: " << endl;
    int test5[] = {10};
    initArray(a, 1, test5);
    cout << "排序前: ";
    printArray(a, length);
    BubbleSort();
    cout << "排序后: ";
    printArray(a, length);
}

int main() {
    testInsertSort();
    return 0;
}
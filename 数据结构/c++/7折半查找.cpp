#include <iostream>
#include <utility>
using namespace std;

#define MAX 100
int a[MAX]; // 有序线性表(从0号位置开始存储)
int length = 0;

// 折半查找算法
pair<int, int> Binary_Search(int key) {
    int l = 0, r = length - 1, mid;
    int ans = 0;
    while (l <= r) {
        mid = l + (r - l) / 2; // 避免(l+r)溢出
        ans++;
        if (a[mid] == key) return {mid, ans}; // 找到返回位置
        else if (a[mid] > key) r = mid - 1; // 向左查找
        else l = mid + 1; // 向右查找
    }
    return {-1, ans}; // 查找失败
}

// 显示线性表
void DisplayList() {
    cout << "有序线性表元素: ";
    for (int i = 0; i < length; i++)  cout << a[i] << " ";
    cout << endl;
}

int main() {
    // 测试有序表
    int sortedData[] = {12, 23, 34, 45, 56, 78, 90};
    for(int i = 0; i < 7; i++) a[i] = sortedData[i];
    length = sizeof(sortedData) / sizeof(sortedData[0]);
    DisplayList();
    
    // 测试查找功能
    int key = 45;
    pair<int, int> result = Binary_Search(key);
    if (result.first != -1) cout << "查找元素" << key << "成功，下标索引: " << result.first << "比较次数：" << result.second << endl;
    else  cout << "查找元素" << key << "失败!" << "比较次数：" << result.second << endl;
    
    key = 66;
    result = Binary_Search(key);
    if (result.first != -1) cout << "查找元素" << key << "成功，下标索引: " << result.first << "比较次数：" << result.second << endl;
    else  cout << "查找元素" << key << "失败!" << "比较次数：" << result.second << endl;
    
    return 0;
}
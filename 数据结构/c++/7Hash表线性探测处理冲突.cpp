#include <iostream>
#include <iomanip>
using namespace std;

// 哈希表最大容量
#define TABLE_SIZE 16
// 状态常量定义
#define EMPTY 0 // 空
#define OCCUPIED 1 // 占用
#define DELETED -1 // 已删除

// 哈希表结构体
struct HashTable {
    int* data;          // 存储数据
    int* status;        // 状态数组：EMPTY/OCCUPIED/DELETED
    int count;          // 当前元素个数
};

// 初始化哈希表
void InitHashTable(HashTable& ht) {
    ht.data = new int[TABLE_SIZE];
    ht.status = new int[TABLE_SIZE];
    ht.count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.data[i] = 0;
        ht.status[i] = EMPTY;
    }
}

// 哈希函数 (除留余数法)
int Hash(int key) {
    return key % 13;
}

// 线性探测法解决冲突
int LinearProbe(HashTable& ht, int key) {
    int addr = Hash(key);
    int i = 1;
    // 寻找下一个空位置，探测次数不超过表长
    while (ht.status[addr] == OCCUPIED) {
        addr = (Hash(key) + i) % TABLE_SIZE;
        i++;
        if (i > TABLE_SIZE) return -1; // 哈希表已满
    }
    return addr;
}

// 插入元素到哈希表
bool Insert(HashTable& ht, int key) {
    if (ht.count >= TABLE_SIZE) return false; // 表已满
    int addr = Hash(key);
    // 发生冲突时进行线性探测
    if (ht.status[addr] == OCCUPIED) {
        addr = LinearProbe(ht, key);
        if (addr == -1) return false;
    }
    ht.data[addr] = key;
    ht.status[addr] = OCCUPIED;
    ht.count++;
    return true;
}

// 查找元素并返回探测次数
int Search(HashTable& ht, int key, int& compareCount) {
    int addr = Hash(key);
    compareCount = 1;
    // 线性探测查找
    while (ht.status[addr] != EMPTY) {
        if (ht.status[addr] == OCCUPIED && ht.data[addr] == key) {
            return addr; // 查找成功
        }
        addr = (addr + 1) % TABLE_SIZE;
        compareCount++;
        // 探测一圈后停止
        if (compareCount > TABLE_SIZE) break;
    }
    return -1; // 查找失败
}

// 显示哈希表状态
void DisplayHashTable(HashTable& ht) {
    cout << "哈希表状态(线性探测法):\n";
    cout << "--------------------------------\n";
    cout << "|  下标  |  关键字  |   状态   |\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "|  " << setw(4) << i << "  |  ";
        if (ht.status[i] == OCCUPIED) {
            cout << setw(6) << ht.data[i] << "  |  已占用  |\n";
        } else if (ht.status[i] == DELETED) {
            cout << setw(6) << "-" << "  |  已删除  |\n";
        } else {
            cout << setw(6) << "-" << "  |  空      |\n";
        }
    }
    cout << "--------------------------------\n\n";
}

// 计算成功查找的平均查找长度
double CalculateSuccessASL(HashTable& ht, int keys[], int n) {
    int totalCompare = 0;
    for (int i = 0; i < n; i++) {
        int compareCount;
        Search(ht, keys[i], compareCount);
        totalCompare += compareCount;
    }
    return (double)totalCompare / n;
}

// 计算不成功查找的平均查找长度
double CalculateUnsuccessASL(HashTable& ht) {
    int totalCompare = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int compareCount = 0;
        int addr = i;
        compareCount++;
        while (ht.status[addr] == OCCUPIED) {
            addr = (addr + 1) % TABLE_SIZE;
            compareCount++;
            if (compareCount > TABLE_SIZE) break;
        }
        totalCompare += compareCount;
    }
    return (double)totalCompare / TABLE_SIZE;
}

int main() {
    HashTable ht;
    InitHashTable(ht);

    // 测试数据 (包含冲突情况)
    int keys[] = {19, 14, 23, 01, 68, 20, 84, 27, 55, 11, 10, 79};
    int n = sizeof(keys) / sizeof(keys[0]);

    // 插入测试数据
    for (int i = 0; i < n; i++) {
        if (Insert(ht, keys[i])) cout << "插入成功: " << keys[i] << endl;
        else cout << "插入失败: " << keys[i] << " (哈希表已满或其他错误)\n";
    }

    // 显示哈希表
    DisplayHashTable(ht);

    // 计算并输出平均查找长度
    double successASL = CalculateSuccessASL(ht, keys, n);
    double unsuccessASL = CalculateUnsuccessASL(ht);

    cout << "成功查找的平均查找长度(ASL_s): " << fixed << setprecision(2) << successASL << endl;
    cout << "失败查找的平均查找长度(ASL_uns): " << fixed << setprecision(2) << unsuccessASL << endl;

    // 释放内存
    delete[] ht.data;
    delete[] ht.status;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int MAXSIZE = 100;

typedef struct {
    int i, j; // 行号列号
    int v;    // 元素值
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1]; // 三元组表
    int mu, nu, tu;           // 行数、列数、非零元个数
} TSMatrix;

bool cmp(Triple a, Triple b) {
    if (a.i == b.i) {  
        if (a.j < b.j) return true;
        return false;
    }
    return a.i < b.i;
}
// 创建稀疏矩阵
void CreateSMatrix(TSMatrix &M) {
    cout << "输入矩阵行列数和非零元个数: ";
    cin >> M.mu >> M.nu >> M.tu;
    cout << "输入" << M.tu << "个非零元素(行 列 值):\n";
    for (int k = 1; k <= M.tu; k++)
        cin >> M.data[k].i >> M.data[k].j >> M.data[k].v;
}

// 打印矩阵
void PrintSMatrix(TSMatrix M) {
    cout << "稀疏矩阵(" << M.mu << "x" << M.nu << ")：\n";
    int k = 1;
    for (int i = 1; i <= M.mu; i++) {
        for (int j = 1; j <= M.nu; j++) {
            if (i == M.data[k].i && j == M.data[k].j) {
                cout << M.data[k].v << " ";
                k++;
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

int main() {
    TSMatrix M, T;
    CreateSMatrix(M);
    sort(M.data + 1, M.data + M.tu + 1, cmp);
    cout << "\n原始矩阵：";
    PrintSMatrix(M);
    
    return 0;
}
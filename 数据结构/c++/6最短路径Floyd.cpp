#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTEX 20

vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, INT_MAX));
vector<char> vertices;
vector<vector<int>> A(MAX_VERTEX, vector<int>(MAX_VERTEX, INT_MAX));
int n = 0;

void Floyd() {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i][j] = adj[i][j];
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (A[i][k] != INT_MAX && A[k][j] != INT_MAX && A[i][k] + A[k][j] < A[i][j]) A[i][j] = A[i][k] + A[k][j];
}

int main() {
    n = 6;
    vertices = {'A','B','C','D','E','F'};
    
    // 初始化邻接矩阵（有向图）
    adj[0][1] = 6;  // A->B
    adj[0][2] = 1;  // A->C
    adj[0][3] = 5;  // A->D
    adj[1][4] = 3;  // B->E
    adj[2][3] = 5;  // C->D
    adj[2][4] = 6;  // C->E
    adj[2][5] = 4;  // C->F
    adj[3][5] = 2;  // D->F
    adj[4][5] = 6;  // E->F
    
    Floyd();

    // 输出结果
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != INT_MAX) cout << vertices[i] << "到" << vertices[j] << "的最短路径长度为：" << A[i][j] << endl;
            else cout << vertices[i] << "到" << vertices[j] << "没有路径" << endl;
        }
        cout << endl;
    }
    return 0;
}
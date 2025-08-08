#include <iostream>
#include <vector>
using namespace std;

#define MAX_VERTEX 20

vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, INT_MAX));
vector<char> vertices;
int n = 0;

void Dijkstra(int v0) {
    vector<bool> final(n, false);
    vector<int> dist(n, INT_MAX);
    vector<int> path(n, -1);

    // 初始化
    dist[v0] = 0;
    final[v0] = true;
    for (int i = 0; i < n; i++) {
        if (adj[v0][i] != INT_MAX) {
            dist[i] = adj[v0][i];
            path[i] = v0;
        }
    }

    // 主循环
    for (int i = 1; i < n; ++i) {
        int min_dist = INT_MAX;
        int u = -1;

        // 选择当前最短路径顶点
        for (int j = 0; j < n; ++j) {
            if (!final[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        final[u] = true;

        // 更新邻接顶点
        for (int w = 0; w < n; ++w) {
            if (!final[w] && adj[u][w] != INT_MAX && dist[u] + adj[u][w] < dist[w]) {
                dist[w] = dist[u] + adj[u][w];
                path[w] = u;
            }
        }
    }

    // 输出结果
    cout << "从 " << vertices[v0] << " 出发，到 " << vertices[n - 1] << " 的最短路径：" << endl;
    int v = n - 1;
    while(v != v0) {
        cout << vertices[v] << "->";
        v = path[v];
    }
    cout << vertices[v0] << endl;
    cout << "最短路径长度：" << dist[n - 1] << endl;
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

    Dijkstra(0); // 从A出发，终点为F
    return 0;
}
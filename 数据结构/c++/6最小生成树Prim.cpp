#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX_VERTEX 20

vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, INT_MAX));
vector<char> vertices;
int n = 0;

void Prim(int start = 0) {
    vector<int> lowcost(n, INT_MAX); // 当前最小权值
    vector<int> mst(n, -1);         // 最小生成树的父节点
    vector<bool> visited(n, false);

    // 初始化起始节点
    lowcost[start] = 0;
    
    for (int i = 0; i < n; i++) {
        // 寻找当前最小权值的顶点
        int min_val = INT_MAX, u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && lowcost[v] < min_val) {
                min_val = lowcost[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;

        // 更新相邻顶点
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != INT_MAX && !visited[v] && adj[u][v] < lowcost[v]) {
                lowcost[v] = adj[u][v];
                mst[v] = u;
            }
        }

    }

    // 输出结果
    cout << "最小生成树边集：" << endl;
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (mst[i] != -1) {
            cout << vertices[mst[i]] << "-" << vertices[i] << " 权重：" << adj[mst[i]][i] << endl;
            total += adj[mst[i]][i];
        }
    }
    cout << "总权重：" << total << endl;
}

int main() {
    // 示例图（与Kruskal算法示例相同）
    n = 6;
    vertices = {'A','B','C','D','E','F'};
    
    // 初始化邻接矩阵
    adj[0][1] = adj[1][0] = 6;  // A-B
    adj[0][2] = adj[2][0] = 1;  // A-C
    adj[0][3] = adj[3][0] = 5;  // A-D
    adj[1][4] = adj[4][1] = 3;  // B-E
    adj[1][2] = adj[2][1] = 5;  // B-C
    adj[2][3] = adj[3][2] = 5;  // C-D
    adj[2][4] = adj[4][2] = 6;  // C-E
    adj[2][5] = adj[5][2] = 4;  // C-F
    adj[3][5] = adj[5][3] = 2;  // D-F
    adj[4][5] = adj[5][4] = 6;  // E-F

    Prim();
    return 0;
}
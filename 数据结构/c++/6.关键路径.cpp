#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

#define MAX_VERTEX 20

// 邻接矩阵存储
vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, 0));
vector<char> vertices;
int n = 0; // 顶点数

// 拓扑排序（返回是否成功且存储排序结果）
bool TopologicalSort(vector<int>& order) {
    vector<int> inDegree(n, 0);
    queue<int> q;
    // 计算入度
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (adj[i][j]) inDegree[j]++;
    // 拓扑排序逻辑
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            order.push_back(i);
            q.push(i);
        }
    }
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w = 0; w < n; w++) {
            if (adj[v][w] != 0) {
                inDegree[w]--;
                if (inDegree[w] == 0) {
                    order.push_back(w);
                    q.push(w);
                }
            }
        }
    }
    if (order.size() != n) return false;
    return true;
    // 如果排序顶点数 < n 返回false
}

void CriticalPath() {
    // 步骤1：拓扑排序
    vector<int> topoOrder;
    if (!TopologicalSort(topoOrder)) {
        cout << "\n存在环，无法计算关键路径";
        return;
    }
    cout << "\n拓扑排序结果：";
    for(int i = 0; i < topoOrder.size(); i++) cout << topoOrder[i] << " ";
    cout << "\n";
    // 步骤2：计算ve
    vector<int> ve(n, 0);
    for(int i = 1; i < topoOrder.size(); i++) {
        int v = topoOrder[i];
        for (int w = 0; w < n; w++) if(adj[w][v]) ve[v] = max(adj[w][v] + ve[w], ve[v]);
    }

    // 步骤3：计算vl
    stack<int> reverseOrder; // 需要逆序处理
    for(int i = 0; i < topoOrder.size() - 1; i++) reverseOrder.push(topoOrder[i]);
    vector<int> vl(n, ve.back());
    while (!reverseOrder.empty()) {
        int v = reverseOrder.top();
        reverseOrder.pop();
        for (int w = 0; w < n; w++) if (adj[v][w] != 0) vl[v] = min(vl[v], vl[w] - adj[v][w]);
    }

    // 步骤4：输出关键路径
    cout << "\n关键路径：";
    int v = 0;
    while(v != n - 1) {
        for (int w = 0; w < n; w++) {
            if (adj[v][w] != 0) {
                int e = ve[v];
                int l = vl[w] - adj[v][w];
                if (e == l) {
                    cout << " " << vertices[v] << "->" << vertices[w];
                    v = w;
                    break;
                }
            }
        }
    }// 若有多条关键路径，需要根据实际情况选择一条
}

int main() {
    // 输入顶点和边（示例）
    n = 6;
    vertices = {'A','B','C','D','E','F'};
    adj[0][1] = 3; // A->B
    adj[0][2] = 2; // A->C
    adj[1][3] = 3; // B->D
    adj[1][4] = 2; // B->E
    adj[2][4] = 4; // C->E
    adj[2][5] = 3; // C->F
    adj[3][5] = 1; // D->F
    adj[4][5] = 2; // E->F

    CriticalPath();
    return 0;
}
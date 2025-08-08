#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_VERTEX = 10;
vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, 0));
vector<int> vertices;

// 顶点存在性检查
bool VertexExist(int x) {
    return find(vertices.begin(), vertices.end(), x) != vertices.end();
}

// 判断边是否存在
bool Adjacent(int x, int y) {
    return adj[x][y] != 0 || adj[y][x] != 0;
}

// 插入顶点
void InsertVertex(int x) {
    if (!VertexExist(x))
        vertices.push_back(x);
}

// 删除顶点
void DeleteVertex(int x) {
    vertices.erase(remove(vertices.begin(), vertices.end(), x), vertices.end());
    for (auto& row : adj) {
        row[x] = 0;
        row[x] = 0;
    }
}

// 添加边
void AddEdge(int x, int y, int weight = 1) {
    adj[x][y] = weight;
    adj[y][x] = weight; // 无向图
}

// 删除边
void RemoveEdge(int x, int y) {
    adj[x][y] = 0;
    adj[y][x] = 0;
}

// 获取第一个邻接点
int FirstNeighbor(int x) {
    for (int y = 0; y < MAX_VERTEX; y++)
        if (adj[x][y] != 0) return y;
    return -1;
}

// 获取下一个邻接点
int NextNeighbor(int x, int y) {
    for (int z = y + 1; z < MAX_VERTEX; z++)
        if (adj[x][z] != 0) return z;
    return -1;
}

// DFS实现
void DFS(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int w = FirstNeighbor(v); w != -1; w = NextNeighbor(v, w))
        if (!visited[w]) DFS(w, visited);
}

// BFS实现
void BFS(int start) {
    vector<bool> visited(MAX_VERTEX, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int w = FirstNeighbor(u); w != -1; w = NextNeighbor(u, w)) {
            if (!visited[w]) {
                q.push(w);
                visited[w] = true;
            }
        }
    }
}

// 测试用例
int main() {
    // 初始化顶点
    for (int i = 0; i < 5; i++)
        InsertVertex(i);

    // 添加边
    AddEdge(0, 1);
    AddEdge(0, 2);
    AddEdge(1, 3);
    AddEdge(2, 4);

    cout << "BFS遍历结果：";
    BFS(0);

    cout << "\nDFS遍历结果：";
    vector<bool> visited(MAX_VERTEX, false);
    DFS(0, visited);
    
    // 删除边
    RemoveEdge(0, 1);
    RemoveEdge(1, 3);
    
    // 打印邻接矩阵
    cout << "\n删除边后的邻接矩阵：" << endl;
    for (auto& row : adj) {
        for (auto& col : row)
            cout << col << " ";
        cout << endl;
    }
    
    // 删除顶点
    DeleteVertex(2);
    
    // 打印邻接矩阵
    cout << "\n删除顶点后的邻接矩阵：" << endl;
    for (auto& row : adj) {
        for (auto& col : row)
            cout << col << " ";
        cout << endl;
    }
    
    // 打印顶点
    cout << "\n打印顶点：" << endl;
    for (auto& vertex : vertices) cout << vertex << " ";
    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> vertices;

// 顶点存在性检查
bool VertexExist(int x) {
    return find(vertices.begin(), vertices.end(), x) != vertices.end();
}

// 判断边是否存在
bool Adjacent(int x, int y) {
    return find(adj[x].begin(), adj[x].end(), y) != adj[x].end();
}

// 插入顶点
void InsertVertex(int x) {
    if (!VertexExist(x)) {
        vertices.push_back(x);
        adj.resize(vertices.size());
    }
}

// 添加边
void AddEdge(int x, int y) {
    if (!Adjacent(x, y)) {
        adj[x].push_back(y);
        adj[y].push_back(x); // 无向图
    }
}

// 删除边
void RemoveEdge(int x, int y) {
    adj[x].erase(remove(adj[x].begin(), adj[x].end(), y), adj[x].end());
    adj[y].erase(remove(adj[y].begin(), adj[y].end(), x), adj[y].end());
}

// 删除顶点
void DeleteVertex(int x) {
    if (VertexExist(x)) {
        vertices.erase(remove(vertices.begin(), vertices.end(), x), vertices.end());
        adj.erase(adj.begin() + x);
        for (auto& row : adj)
            row.erase(remove(row.begin(), row.end(), x), row.end());
    }
}

// 获取第一个邻接点
int FirstNeighbor(int x) {
    return !adj[x].empty() ? adj[x][0] : -1;
}

// 获取下一个邻接点
int NextNeighbor(int x, int y) {
    auto it = find(adj[x].begin(), adj[x].end(), y);
    if (it != adj[x].end() && next(it) != adj[x].end())
        return *next(it);
    return -1;
}

// DFS实现
void DFS(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << vertices[v] << " ";
    for (int w : adj[v])
        if (!visited[w]) DFS(w, visited);
}

// BFS实现
void BFS(int start) {
    vector<bool> visited(vertices.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << vertices[u] << " ";

        for (int w : adj[u])
            if (!visited[w]) {
                q.push(w);
                visited[w] = true;
            }
    }
}

// 测试用例
int main() {
    // 初始化顶点
    for (int i = 1; i <= 5; i++)
        InsertVertex(i);

    // 添加边
    AddEdge(0, 1); // 1-2
    AddEdge(0, 2); // 1-3
    AddEdge(1, 3); // 2-4
    AddEdge(2, 4); // 3-5
    cout << "邻接表：" << endl;
    for (auto& row : vertices) {
        cout << row << ":";
        for (auto& col : adj[row - 1])
            cout << col + 1 << " ";
        cout << endl;
    }
    
    cout << "BFS遍历结果：";
    BFS(0);
    
    cout << "\nDFS遍历结果：";
    vector<bool> visited(vertices.size(), false);
    DFS(0, visited);

    // 删除边
    RemoveEdge(0, 1);
    RemoveEdge(1, 3);
    
    // 打印邻接矩阵
    cout << "\n删除边后的邻接表：" << endl;
    for (auto& row : vertices) {
        cout << row << ":";
        for (auto& col : adj[row - 1])
            cout << col + 1 << " ";
        cout << endl;
    }
    
    // 删除顶点
    DeleteVertex(1);
    
    // 打印邻接矩阵
    cout << "\n删除顶点后的邻接表：" << endl;
    for (auto& row : vertices) {
        cout << row << ":";
        for (auto& col : adj[row - 1])
            cout << col + 1 << " ";
        cout << endl;
    }
    
    // 打印顶点
    cout << "\n打印顶点：" << endl;
    for (auto& vertex : vertices) cout << vertex << " ";
    cout << endl;

    return 0;
}
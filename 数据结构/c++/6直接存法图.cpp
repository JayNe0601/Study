#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 顶点集合和边集合
vector<int> vertices;
struct Edge {
    int u, v;
    int weight = 0;
};
vector<Edge> e;

// 判断边是否存在
bool Adjacent(int x, int y) {
    for (auto& edge : e) {
        if ((edge.u == x && edge.v == y) || (edge.u == y && edge.v == x))
            return true;
    }
    return false;
}

// 插入顶点
void InsertVertex(int x) {
    if (find(vertices.begin(), vertices.end(), x) == vertices.end()) vertices.push_back(x);
}

// 删除顶点
void DeleteVertex(int x) {
    // 删除顶点
    vertices.erase(remove(vertices.begin(), vertices.end(), x), vertices.end());
    
    // 删除相关边
    e.erase(remove_if(e.begin(), e.end(), [x](Edge edge){ return edge.u == x || edge.v == x; }), e.end());
}

// 添加边
void AddEdge(int x, int y) {
    if (!Adjacent(x, y)) e.push_back({x, y});
}

// 删除边
void RemoveEdge(int x, int y) {
    e.erase(remove_if(e.begin(), e.end(), [x,y](Edge edge){ return (edge.u == x && edge.v == y) || (edge.u == y && edge.v == x); }), e.end());
}

// 获取第一个邻接点
int FirstNeighbor(int x) {
    for (auto& edge : e) {
        if (edge.u == x) return edge.v;
        if (edge.v == x) return edge.u;
    }
    return -1;
}

// 获取下一个邻接点
int NextNeighbor(int x, int y) {
    bool found = false;
    for (auto& edge : e) {
        if ((edge.u == x && edge.v == y) || (edge.v == x && edge.u == y)) found = true;
        else if (found && (edge.u == x || edge.v == x)) return edge.u == x ? edge.v : edge.u;
    }
    return -1;
}

// 深度优先遍历
void DFS(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int w = FirstNeighbor(v); w != -1; w = NextNeighbor(v, w)) if (!visited[w]) DFS(w, visited);
}

// 广度优先遍历
void BFS(int start) {
    vector<bool> visited(vertices.size(), false);
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

// 设置边权值
void Set_edge_value(int x, int y, int v) {
    for (auto& edge : e) if ((edge.u == x && edge.v == y) || (edge.u == y && edge.v == x)) edge.weight = v;
}

// 测试用例
int main() {
    // 初始化顶点
    for (int i = 1; i <= 5; i++) InsertVertex(i);
    
    // 添加边
    AddEdge(1, 2);
    AddEdge(1, 3);
    AddEdge(2, 4);
    AddEdge(3, 5);
    
    cout << "BFS遍历结果：";
    BFS(1);
    
    cout << "\nDFS遍历结果：";
    vector<bool> visited(vertices.size()+1, false);
    DFS(1, visited);
    
    // 设置边权值
    Set_edge_value(1, 2, 10);
    Set_edge_value(1, 3, 20);
    Set_edge_value(2, 4, 30);
    Set_edge_value(3, 5, 40);
    
    // 删除边
    RemoveEdge(1, 2);
    RemoveEdge(2, 4);
    
    // 打印边权值
    cout << "\n打印边权值：" << endl;
    for (auto& edge : e) cout << edge.u << " " << edge.v << " " << edge.weight << endl;
    
    // 删除顶点
    DeleteVertex(3);
    
    // 打印顶点
    cout << "\n打印顶点：" << endl;
    for (auto& vertex : vertices) cout << vertex << " ";
    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;
    int weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<char> vertices;
int n = 0;

vector<int> ds;

int Find(int x) {
    if (ds[x] == x) return x;
    return ds[x] = Find(ds[x]);
}

void Union(int x, int y) {
    ds[Find(x)] = Find(y);
}

void Kruskal() {
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 6));
    edges.push_back(Edge(0, 2, 1));
    edges.push_back(Edge(0, 3, 5));
    edges.push_back(Edge(1, 4, 3));
    edges.push_back(Edge(1, 2, 5));
    edges.push_back(Edge(2, 3, 5));
    edges.push_back(Edge(2, 4, 6));
    edges.push_back(Edge(2, 5, 4));
    edges.push_back(Edge(3, 5, 2));
    edges.push_back(Edge(4, 5, 6));
    ds.push_back(0);
    ds.push_back(1);
    ds.push_back(2);
    ds.push_back(3);
    ds.push_back(4);
    ds.push_back(5);

    // 按边权排序
    sort(edges.begin(), edges.end());

    vector<Edge> result;
    int total = 0;// 最小生成树总权重

    for (const Edge& e : edges) {
        if (Find(e.u) != Find(e.v)) {
            Union(e.u, e.v);
            result.push_back(e);
            total += e.weight;
            if (result.size() == n - 1) break;
        }
    }

    // 输出结果
    cout << "最小生成树边集：" << endl;
    for (const Edge& e : result) {
        cout << vertices[e.u] << "-" << vertices[e.v]
             << " 权重：" << e.weight << endl;
    }
    cout << "总权重：" << total << endl;
}

int main() {
    // 初始化图（与Prim算法示例相同）
    n = 6;
    vertices = {'A','B','C','D','E','F'};

    Kruskal();
    return 0;
}
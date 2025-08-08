#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1000;
vector<vector<int>> adj(N + 1);//邻接表
vector<int> deg(N + 1, 0);//顶点入度数
vector<int> toporder(int n) {
    vector<int> orders;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i); // 入度数为 0，入队
            orders.push_back(i); // 入度数为 0，进入 orders 序列待后续输出
        }
    }
    while (!q.empty()) { // 队列不为空
        int u = q.front(); 
        q.pop(); // 出队
        for (int v : adj[u]) { // 遍历该点邻接表
            deg[v]--; // 入度数减一
            if (deg[v] == 0) { // 如果入度为 0
                q.push(v);//入队
                orders.push_back(v); // 进入 orders 序列待后续输出
            }
        }
    }
    return orders;
}
int main() {
    int n, m;
    cin >> n >> m; //假设n个节点，m条边
    while (m--) {
        int u, v;
        cin >> u >> v; //输入 u，v 表示 u->v 这条边
        adj[u].push_back(v);
        deg[v]++; // 顶点 v 的入度加一
    }
    vector<int> order = toporder(n);
    if (order.size() < n)  cout << "无法拓扑排序" << endl;
    else for (int i = 0; i < n; i++) cout << order[i] << ' ';
    return 0;
}
#include <iostream>
using namespace std;
const int N = 10001;
int fa[N];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void unionset(int x, int y) {
    fa[find(x)] = find(y);
}
void f(int x, int y) {
    if (find(x) == find(y))cout << "Y" << endl;
    else cout << "N" << endl;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i;
    int z, x, y;
    while (m--) {
        cin >> z >> x >> y;
        if (z == 1) unionset(x, y);
        else f(x, y);
    }
}
int main() {
    solve();
    return 0;
}
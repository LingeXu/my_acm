#include <bits/stdc++.h>
using namespace std;

void solve() {
    int k;
    cin >> k;
    vector<int> n(k + 1);
    vector< vector< pair<int,int> > > e(k + 1);  // e[i]: 第 i 棵树的边表
    vector< vector<int> > deg(k + 1);            // deg[i][v]: 第 i 棵树中 v 的度数
    for(int i = 1; i <= k; i++) {
        cin >> n[i];
        deg[i].assign(n[i] + 1, 0);
        for(int j = 0; j < n[i] - 1; j++) {
            int u, v;
            cin >> u >> v;
            e[i].push_back(make_pair(u, v));
            deg[i][u]++;
            deg[i][v]++;
        }
    }
    if(k == 1)  return;  // 不需要加边
    // 找一棵大小 >= 2 的树作为中心
    int c = -1;
    for(int i = 1; i <= k; i++)
        if(n[i] >= 2) { c = i; break; }
    if(c == -1) {
        // 所有树都是单点: 连成星形, 最大独立集 = k - 1(最优)
        for(int i = 2; i <= k; i++)
            cout << 1 << " " << 1 << " " << i << " " << 1 << "\n";
        return;
    }
    // 取中心树的一个叶子 x, 记其唯一邻居为 y
    // 关键: 一定存在一个最大独立集不含 y(把含 y 的最大独立集里的 y 换成 x 即可)
    int leaf = -1;
    for(int v = 1; v <= n[c]; v++)
        if(deg[c][v] == 1) { leaf = v; break; }
    int y = -1;
    for(size_t j = 0; j < e[c].size(); j++) {
        if(e[c][j].first == leaf)   y = e[c][j].second;
        if(e[c][j].second == leaf)  y = e[c][j].first;
    }
    // 其他所有树任意取一个顶点连到 y; y 不在中心树的最大独立集里, 交叉边全被"罩住"
    for(int i = 1; i <= k; i++)
        if(i != c)
            cout << c << " " << y << " " << i << " " << 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}

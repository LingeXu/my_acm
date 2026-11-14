#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t, n;
vector<int> graph[N], dis_1(N, 0), dis_2(N, 0), dis_3(N, 0);
void dfs1(int u, int fa) {
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dis_1[v] = dis_1[u] + 1;
        dfs1(v, u);
    }
}
void dfs2(int u, int fa) {
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dis_2[v] = dis_2[u] + 1;
        dfs2(v, u);
    }
}
void dfs3(int u, int fa) {
    for(int v : graph[u]) {
        if(v == fa)
            continue;
        dis_3[v] = dis_3[u] + 1;
        dfs3(v, u);
    }
}
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        graph[i].clear();
        dis_1[i] = 0;
        dis_2[i] = 0;
        dis_3[i] = 0;
    }
    vector<int> in_deg(n + 1, 0);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        in_deg[u]++;
        in_deg[v]++;
    }
    dfs1(1, 0);
    int dist = 0, diameter = 1;
    for(int i = 1; i <= n; i++) {
        if(dis_1[i] > dist) {
            dist = dis_1[i];
            diameter = i;
        }
    }

    //cout << "diameter = " << diameter << '\n';

    dfs2(diameter, 0);
    int dist2 = 0, diameter2 = diameter;
    for(int i = 1; i <= n; i++) {
        if(dis_2[i] > dist2) {
            dist2 = dis_2[i];
            diameter2 = i;
        }
    }

   //cout << "diameter2 = " << diameter2 << '\n';

    dfs3(diameter2, 0);
    int d = dis_3[diameter];
    for(int i = 1; i <= n; i++) {
        if(i == diameter || i == diameter2)
            continue;
        if(dis_2[i] + dis_3[i] == d && in_deg[i] > 2) {
            for(int j : graph[i]) {
                if(dis_2[j] + dis_3[j] == d) {
                    cout << j << ' ';
                    break;
                }
            }
            cout << i << ' ';
            for(int j : graph[i]) {
                if(dis_2[j] + dis_3[j] != d) {
                    cout << j << ' ';
                    return;
                }
            }
        }
    }
    cout << -1 << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
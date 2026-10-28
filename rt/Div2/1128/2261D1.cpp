#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> added;
void dfs(int l, int r) {
    int length = r - l + 1;
    if(length <= 1)
        return;
    int span = (length + 1) / 2;
    if(length % 2 == 0) 
        for(int i = l; i + span - 1 < r; i++)
            added.push_back(make_pair(i, i + span - 1));       
    else
        for(int i = l; i + span - 1 <= r; i++)
            added.push_back(make_pair(i, i + span - 1));
    return;
}
void solve() {
    added.clear();
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> detectors(m);
    for (int i = 0; i < m; i++) 
        cin >> detectors[i].first >> detectors[i].second;
    if(m == 0) {
        dfs(1, n);
        cout << added.size() << "\n";
        for (auto p : added) 
            cout << p.first << " " << p.second << "\n";
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}
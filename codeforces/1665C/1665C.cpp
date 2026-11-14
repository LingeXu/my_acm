#include <bits/stdc++.h>
using namespace std;
#define N 200005
int t, n;
vector<int> graph[N], cnt;
bool check(int x) {
    int need = 0;
    for(int i = 0; i < cnt.size(); i++) {
        if(cnt[i] + i <= x)
            continue;
        need += cnt[i] + i - x;
    }
    return need <= x - (int)cnt.size();
}
void solve() {
    cin >> n;
    cnt.clear();
    for(int i = 1; i <= n; i++)
        graph[i].clear();
    for(int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        graph[fa].push_back(i);
    }
    for(int i = 1; i <= n; i++) 
        if((int)graph[i].size() > 0)
            cnt.push_back((int)graph[i].size());
    cnt.push_back(1);
    sort(cnt.begin(), cnt.end(), greater<int>());

    /*for(int i : cnt) 
        cout << i << ' ';
    cout << '\n';*/


    int l = 0, r = n, ans = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else    l = mid + 1;
    }
    cout << ans << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
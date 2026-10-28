#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k;
auto cmp = [](pair<int, int> &x, pair<int, int> &y){return x.second > y.second;};
int lowbit(int x) {
    for(int i = 0; i < 64; i++) {
        if((x >> i) & 1 == 1)   continue;
        return (1LL << i);
    }
    cerr << "something 's wrong";
    return -1;
}
void solve() {
    cin >> n >> k;
    priority_queue< pair<int, int>, vector< pair<int, int> >, decltype(cmp) > pq(cmp);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans += __builtin_popcount(x);
        pq.push(make_pair(x, lowbit(x)));
    }
    int delta = 0;
    while(k >= pq.top().second) {
        auto x = pq.top();
        pq.pop();
        delta++;
        k -= x.second;
        x.first += lowbit(x.first);
        pq.push(make_pair(x.first, lowbit(x.first)));
        //cout << pq.top().first << ' ' << pq.top().second << '\n';
    }
    cout << delta + ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;   
}
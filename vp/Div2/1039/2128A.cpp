#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, c;
void solve() {
    cin >> n >> c;
    int ans = 0;
    priority_queue<int, vector<int>, less<int> > pq;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x > c)   continue;
        else    pq.push(x);
    }
    double cur = c;
    while(!pq.empty()) {
        int x = pq.top();
        pq.pop();
        if(x <= cur) {
            ans++;
            cur /= 2;
        }
    }
    cout << n - ans << '\n';
    return;
}
signed main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}
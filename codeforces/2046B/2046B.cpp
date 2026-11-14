#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n), moved(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int mn = LLONG_MAX, p = LLONG_MAX;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] > mn) {
            moved[i] = 1;
            p = min(p, a[i] + 1);
        }
        mn = min(mn, a[i]);
    }
    for(int i = 0; i < n; i++)
        if(a[i] > p)
            moved[i] = 1;
    priority_queue< int, vector<int>, greater<int> > pq;
    for(int i = 0; i < n; i++) {
        if(moved[i] == 0)
            cout << a[i] << ' ';
        else    pq.push(a[i] + 1);
    }
    while(!pq.empty()) {
        int x = pq.top();
        pq.pop();
        cout << x << ' ';
    }
    cout << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
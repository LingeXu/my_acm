#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int mn = n + 1;
    vector<int> a(n + 1);
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mn = min(mn, a[i]);
        if(mn == n - i + 1 && i != n)
            ok = false;
    }
    if(!ok) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    stack<int> st;
    vector< pair<int, int> > ans;
    for(int i = 1; i <= n; i++) {
        int cur = a[i];
        while(!st.empty() && st.top() < a[i]) {
            cur = min(cur, st.top());
            ans.push_back(make_pair(st.top(), a[i]));
            st.pop();
        }
        st.push(cur);
    }
    for(auto &e : ans)
        cout << e.first << ' ' << e.second << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int cnt_a = 0;
    for(int i = 0; i < n; ) {
        int j = i;
        cnt_a++;
        while(j < n && a[j] == a[i])    j++;
        i = j;
    }
    for(int i = 0; i < n; i++)
        cin >> b[i];
    sort(b.begin(), b.end());
    int cnt_b = 0;
    for(int i = 0; i < n; ) {
        int j = i;
        cnt_b++;
        while(j < n && b[j] == b[i])    j++;
        i = j;
    }
    if(cnt_a >= 3 || cnt_b >= 3 ||(cnt_a == 2 && cnt_b == 2)) {
        cout << "YES\n";
    }
    else    cout << "NO\n";
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
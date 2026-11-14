#include <bits/stdc++.h>
using namespace std;
int n, k;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    string op;
    for(int i = 0; i < k; i++) {
        op += (char)('a' + i);
        for(int j = i + 1; j < k; j++) {
            op += (char)('a' + i);
            op += (char)('a' + j);
        }
    }
    int sz = op.size();
    for(int i = 1; i <= n / sz; i++)
        cout << op;
    int rem = n % sz;
    for(int i = 0; i < rem; i++)
        cout << op[i];
    cout << '\n';
    return 0;
}
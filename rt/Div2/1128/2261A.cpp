#include <bits/stdc++.h>
using namespace std;
int n;
string s;
void solve() {
    cin >> n >> s;
    vector<int> id1, id2;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1')
            id1.push_back(i + 1);
        else id2.push_back(i + 1);
    }
    if((int)id1.size() == 1) {
        cout << 0 << '\n';
        return;
    }
    if((int)id1.size() == 2) {
        cout << 1 << '\n';
        return;
    }
    cout << id1.back() - id1[0] << '\n';
    return;
}
int main() {
    int t;
    cin >> t;
    while(t--)  solve();
    return 0;
}
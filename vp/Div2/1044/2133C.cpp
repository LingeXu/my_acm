#include <bits/stdc++.h>
using namespace std;
int t, n;
void solve() {
    cin >> n;
    int resp, mx_length = 0, diameter = -1;
    vector<vector<int> > mp(n + 1);
    for(int i = 1; i <= n; i++) {
        cout << "? " << i << ' ' << n;
        for(int j = 1; j <= n; j++)
            cout << ' ' << j;
        cout << endl;
        cin >> resp;
        if(resp == -1)  exit(0);
        if(mx_length < resp) {
            mx_length = resp;
            diameter = i;
        }
        mp[resp].push_back(i);
    }
    vector<int> ans;
    ans.push_back(diameter);
    int cur = diameter;
    for(int i = mx_length - 1; i >= 1; i--) {
        if((int)mp[i].size() == 1) {  
            cur = mp[i][0];
            ans.push_back(cur);
            continue;
        }
        for(int j : mp[i]) {
            cout << "? " << cur << ' ' << 2 << ' ' << cur << ' ' << j << endl;
            cin >> resp;
            if(resp == 2) {             
                cur = j;
                ans.push_back(j);
                break;
            }
        }
    }
    cout << "! " << mx_length;
    for(int i : ans)
        cout << " " << i;
    cout << endl;
    return;
}
int main() {
    cin >> t;
    while(t--)  solve();
    return 0;
}
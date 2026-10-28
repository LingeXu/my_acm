#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, resp;
void solve() {
    cin >> n;
    vector<int> f(n + 3, -1), val(n + 1, -1);
    f[n + 1] = f[n + 2] = 0;
    for(int i = n; i >= 1; i--) {
        if(f[i + 1] != f[i + 2]) {
            cout << "throw " << i << endl;
            cin >> resp;
            f[i] = resp;
            if(resp == f[i + 1] + 1)  val[i] = 1;
            else    val[i] = 2;
            continue;
        }
        else {
            if(i == 1) {
                cout << "swap " << 1 << endl;
                cout << "throw " << 2 << endl;
                cin >> resp;
                if(resp == f[2])    val[1] = 2;
                else    val[1] = 1;
                break;
            }
            f[i] = f[i + 1] + 1;                 
            cout << "throw " << i - 1 << endl;   
            cin >> resp;
            val[i - 1] = (resp == f[i + 1] + 1 ? 2 : 1);
            cout << "swap " << i - 1 << endl;
            cout << "throw " << i - 1 << endl;   
            cin >> resp;
            val[i] = (resp == f[i + 1] + 1 ? 2 : 1);
            f[i - 1] = resp;                     
            i--;  
        }
    }
    cout << "!";
    for(int i = 1; i <= n; i++)
        cout << ' ' << val[i];
    cout << endl;
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}
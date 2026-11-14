/*#include <bits/stdc++.h>
using namespace std; 
#define int long long
int t, n;
void solve() {
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += (1LL << a[i]);
    }
    sort(a.begin(), a.end());
    int cur = 0;
    int cur1, cur2;
    for(int i = 0; i < n; i++) {
        cur += (1LL << a[i]);
        if(cur <= sum / 2)
            cur1 = cur;
        else {
            cur2 = cur;
            break;
        }
    }
    cout << "cur1 = " << cur1 << '\n';
    cout << "cur2 = " << cur2 << '\n';
    cout << max(cur1 * (sum - cur1), cur2 * (sum - cur2)) << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)  solve();
    return 0;
}*/

#include <bits/stdc++.h>
using namespace std;

string u64ToString(unsigned long long x){
    if(x == 0) return "0";
    string s;
    while(x){ s.push_back(char('0' + (int)(x % 10))); x /= 10; }
    reverse(s.begin(), s.end());
    return s;
}

string mulDec(const string &A, const string &B){   
    int n = A.size(), m = B.size();
    vector<int> c(n + m, 0);
    for(int i = n-1; i >= 0; --i)
        for(int j = m-1; j >= 0; --j)
            c[(n-1-i) + (m-1-j)] += (A[i]-'0') * (B[j]-'0');
    string res;
    int carry = 0;
    for(int i = 0; i < n+m; ++i){
        int cur = c[i] + carry;
        res.push_back(char('0' + cur % 10));
        carry = cur / 10;
    }
    while(carry){ res.push_back(char('0' + carry % 10)); carry /= 10; }
    while(res.size() > 1 && res[res.size()-1] == '0') res.erase(res.size()-1);
    reverse(res.begin(), res.end());
    return res;
}


int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;  
    while(t--){
        int n;
        if(scanf("%d", &n) != 1) break;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);

        sort(a.rbegin(), a.rend());

        unsigned long long T = 0;
        for(int i = 0; i < n; ++i) T += 1ULL << a[i];

        unsigned long long half = T / 2, s = 0;
        for(int i = 0; i < n; ++i){
            unsigned long long v = 1ULL << a[i];
            if(s + v <= half) s += v;
        }

        printf("%s\n", mulDec(u64ToString(s), u64ToString(T - s)).c_str());
    }
    return 0;
}
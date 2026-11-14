#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd_(ll x, ll y) { 
    while(y) { 
        ll t = x % y; 
        x = y; y = t;
    } 
    return abs(x); 
}
int main(){
    int t; 
    cin >> t;
    while(t--) {
        ll a,b; 
        cin >> a >> b;
        if(a == b) { 
            puts("0"); 
            continue; 
        }
        if(gcd_(a,b) == 1) { 
            printf("1\n%lld\n", b - a); 
            continue; 
        }
        ll lim = max(a + 1, b - 200000);   
        bool done = false; 
        for(ll m = b - 1; m >= lim; m--) {                   
            if(gcd_(a, m) == 1 && gcd_(m, b) == 1) {
                printf("2\n%lld %lld\n", m - a, b - m); 
                done = true; 
                break;
            }
        }
        if(done) continue;

        for(ll m2 = b-1; m2 >= lim && !done; m2--){         
            if(gcd_(m2, b) != 1) continue;
            for(ll m1 = m2 - 1; m1 >= lim && !done; m1--) {
                if(gcd_(a, m1) == 1 && gcd_(m1, m2) == 1){
                    printf("3\n%lld %lld %lld\n", m1 - a, m2 - m1, b - m2); 
                    done = true;
                }
            }
        }
    }
    return 0;
}
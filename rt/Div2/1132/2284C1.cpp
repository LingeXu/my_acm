#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
static inline ull mulmod(ull a, ull b, ull m) { 
    return a * b % m; 
}   

ull pwmod(ull a, ull e, ull m){
    ull r = 1 % m; a %= m;
    while(e) { 
        if(e & 1) r = mulmod(r, a, m); 
        a = mulmod(a, a, m); 
        e >>= 1; 
    }
    return r;
}

bool isPrime(ull n){
    if(n < 2) return false;
    static const ull small[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for(ull p : small) 
        if(n % p == 0) 
            return n == p; 
    ull d = n - 1; 
    int s = 0;
    while((d & 1) == 0) { 
        d >>= 1; 
        ++s; 
    }
    for(ull a : {2ULL, 3ULL, 5ULL, 7ULL}){
        ull x = pwmod(a, d, n);
        if(x == 1 || x == n-1)  continue;
        bool ok = false;
        for(int r = 1; r < s; ++r){
            x = mulmod(x, x, n);
            if(x == n - 1) {
                ok = true; 
                break; 
            }
        }
        if(!ok) return false;
    }
    return true;
}

int main(){
    int t; 
    scanf("%d", &t);
    while(t--) {
        int n; 
        scanf("%d", &n);
        vector<long long> a(n);
        for(int i = 0;i < n; i++) scanf("%lld", &a[i]);
        for(int i = 0;i < n; i++){
            if(a[i] == 1) continue;
            ull p = (ull)a[i];
            while(!isPrime(p)) ++p;         
            a[i] = (long long)p;
        }
        for(int i = 0;i < n; i++) 
            printf("%lld%c", a[i], " \n"[i + 1 == n]);
    }
    return 0;
}
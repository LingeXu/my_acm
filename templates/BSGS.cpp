//BSGS(baby-step giant-step): 解离散对数 a^x ≡ b (mod p), O(sqrt(p))
//前提: gcd(a, p) == 1(否则用 exBSGS, 区域赛少见)
//思想: 令 x = i * m - j (m = ceil(sqrt(p)), 0 <= i <= m, 0 <= j < m),
//      则 a^(i*m) ≡ b * a^j, 枚举 i 查表匹配 j
//返回最小非负解 x, 无解返回 -1
//需预定义: 无(自带任意模快速幂);  unordered_map 存 (b * a^j -> j)

ll qpow_mod(ll a, ll n, ll p) {    //模 p 快速幂(任意模数)
    ll res = 1 % p;
    a %= p;
    while(n) {
        if(n & 1)    res = res * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return res;
}

ll bsgs(ll a, ll b, ll p) {
    a %= p;
    b %= p;
    if(b == 1)    return 0;                 //x = 0 恒为解
    ll m = ceil(sqrt(p));
    unordered_map<ll, ll> mp;
    ll cur = b;                             //枚举 j: 存 b * a^j 的最小 j
    for(ll j = 0; j < m; j++) {
        if(!mp.count(cur))    mp[cur] = j;
        cur = cur * a % p;
    }
    ll step = qpow_mod(a, m, p);            //giant step: a^m
    cur = 1;
    for(ll i = 1; i <= m; i++) {            //枚举 i: 查 a^(i*m) 是否在表中
        cur = cur * step % p;
        if(mp.count(cur)) {
            ll x = i * m - mp[cur];
            if(x >= 0)    return x;         //(注意同一 x 可能多个 (i, j) 表示, 取最小)
        }
    }
    return -1;
}
//配套:
//1. p 为质数时最小解一定 < p;  解的周期 = ord_p(a), 可求所有解
//2. exBSGS(gcd(a, p) > 1): 提取公因子化为 gcd 互质情形, 代码较长, 赛前备一份即可

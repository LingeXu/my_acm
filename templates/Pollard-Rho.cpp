//Pollard-Rho: 大整数(<= 2^62)质因数分解, 期望 O(n^(1/4))
//原理: 生日悖论构造循环序列 x -> x^2 + c, 用"龟兔赛跑"(Floyd)判环,
//      环上两点的 gcd(|xi - xj|, n) 有概率产生 n 的非平凡因子; 素数判定用 Miller-Rabin
//需预定义: Miller-Rabin 的 is_prime / mul_mod(见 MillerRabin.cpp)
//入口: factor(n, fac);  结果存入 fac(无序, 可 sort)
//注意: n = 1 或 0 时特判; 分解后记得 sort 并按需计数

ll Pollard_Rho(ll n) {
    if(n % 2 == 0)    return 2;
    if(n % 3 == 0)    return 3;
    while(true) {
        ll c = rand() % (n - 1) + 1;       //随机常数, 失败换一个重来
        ll x = rand() % n, y = x;          //龟兔双指针
        ll d = 1;
        for(int step = 1; ; step <<= 1) {  //倍增阶段: 每 2^k 步取一次 gcd, 减少 gcd 次数
            x = y;
            for(int i = 0; i < step; i++) {
                y = (mul_mod(y, y, n) + c) % n;    //兔走一步: y -> y^2 + c
                d = mul_mod(d, abs(x - y), n);     //累乘 |x-y| 一起求 gcd(分块 gcd 优化)
            }
            if(d == 0)    d = n;           //x == y 落入环起点, 本轮失败
            d = gcd(d, n);
            if(d != 1)    return d;        //找到非平凡因子
        }
    }
}

void factor(ll n, vector<ll>& fac) {       //递归分解, 结果存 fac
    if(n <= 1)    return;
    if(is_prime(n)) {                      //Miller-Rabin 判素
        fac.push_back(n);
        return;
    }
    ll d = Pollard_Rho(n);
    factor(d, fac);
    factor(n / d, fac);
}
//配套: 求 n 的约数个数/约数和: 分解后 d(n) = prod(ei + 1), sigma(n) = prod((p^(ei+1) - 1) / (p - 1))

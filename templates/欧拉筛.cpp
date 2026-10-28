//欧拉筛(线性筛): O(n) 筛出 [1, n] 所有素数
//关键: 每个合数只被它的最小质因子筛掉一次(内层 if(i % primes[j] == 0) break 保证)
//配套: 同时筛积性函数(phi/mu/d/sigma)见 线性筛积性函数.cpp
vector<int> euler_sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    if(n < 2)   return primes;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= n; i++) {
        if(is_prime[i])
            primes.push_back(i);
        for(int j = 0; j < primes.size() && i * primes[j] <= n; j++) {  //i * primes[j] <= n
            is_prime[i * primes[j]] = false;
            if(i % primes[j] == 0)  break;
        }
    }
    return primes;
}
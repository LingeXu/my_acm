//后缀数组 SA: O(n log n) 倍增 + 基数排序
//sa[i] = 排名第 i 的后缀的起始下标(1-based);  rk[i] = 后缀 i 的排名
//height[i] = LCP(sa[i-1], sa[i])(排名相邻两后缀的最长公共前缀), height[1] = 0
//需预定义: int sa[MAXN], rk[MAXN << 1], oldrk[MAXN << 1], id[MAXN], cnt[MAXN], height[MAXN];
//         rk 开两倍防越界(旧 rk[i+w] 可能超 n);  串 s 下标从 1 开始
//入口: build_sa(s); build_height(s);  之后任意两后缀的 LCP = height 区间最小值(配合 ST表)

void build_sa(const string& s) {
    int n = s.size() - 1, m = 128;         //初始值域 = 字符集大小(ASCII 用 128)
    for(int i = 0; i <= m; i++)    cnt[i] = 0;    //多次调用 build_sa 时清空残留
    for(int i = 1; i <= n; i++)    cnt[rk[i] = s[i]]++;
    for(int i = 1; i <= m; i++)    cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i--)    sa[cnt[rk[i]]--] = i;        //按首字符排序(计数排序)
    for(int w = 1; w < n; w <<= 1) {                           //倍增: 每次比较长度翻倍
        int p = 0;                                             //按第二关键字(rk[i+w])排序
        for(int i = n - w + 1; i <= n; i++)    id[++p] = i;     //第二关键字为空(超出串尾)的最前
        for(int i = 1; i <= n; i++)
            if(sa[i] > w)    id[++p] = sa[i] - w;               //其余按 sa 序取第二关键字
        for(int i = 0; i <= m; i++)    cnt[i] = 0;
        for(int i = 1; i <= n; i++)    cnt[rk[i]]++;
        for(int i = 1; i <= m; i++)    cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i--)    sa[cnt[rk[id[i]]]--] = id[i];   //按第一关键字稳定排序
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        p = 0;
        for(int i = 1; i <= n; i++)                             //重新离散化排名
            rk[sa[i]] = (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                         oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) ? p : ++p;
        m = p;                                                 //值域缩小为排名个数
        if(m == n)    break;                                   //排名互不相同, 排序完成
    }
}

void build_height(const string& s) {   //利用性质 height[rk[i]] >= height[rk[i-1]] - 1, 均摊 O(n)
    int n = s.size() - 1;
    for(int i = 1, k = 0; i <= n; i++) {
        if(rk[i] == 1)    continue;                    //排名第一没有前驱, height[1] = 0
        if(k)    k--;                                  //k 至多减 1
        int j = sa[rk[i] - 1];                         //排名前一位的后缀
        while(i + k <= n && j + k <= n && s[i + k] == s[j + k])    k++;
        height[rk[i]] = k;
    }
}

//配套:
//1. 两后缀 LCP: lcp(i, j) = min(height[rk[i]+1 .. rk[j]]), ST 表 O(1) 查询(见 ST表.cpp)
//2. 本质不同子串数 = n(n+1)/2 - sum(height[i])   (每个后缀贡献的重复前缀 = height)
//3. 两串最长公共子串: s1 + '#' + s2 建 SA, 相邻且分属两串的 height 最大值(注意分隔符唯一)
//4. 比较两子串字典序: 二分 + LCP 比较第一个不同字符, 或 (rk[a], 长度) 二元组比较
//5. 最小循环位移: 把 s 拼一遍 s + s, 取 sa[1..n] 中起始 <= n 且后缀长度 >= n 的最前一个

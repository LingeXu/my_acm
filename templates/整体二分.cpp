//整体二分: 离线同时二分所有询问, 每次 O((n + q) log n) 把询问分成"答案在左半/右半"两组
//适用: 多次"区间第 k 小"类查询; 复杂度 O((n + q) log n log V)
//思想: solve(q[], l, r) 假设这些询问的答案都在值域 [l, r] 内, 取 mid 后
//      用 BIT 统计每个询问区间内 <= mid 的个数, 够 k 的分左, 不够的分右
//需预定义: 树状数组 BIT;  数组 a[1..n];  询问存 struct Query { int l, r, k, id; };
//入口: solve(qs, 1, 值域上界)

//int cur;  //当前按值 <= mid 加入 BIT 的指针: 分治每层重置, 保证总复杂度 O((n+q) log V) 的关键
void solve(vector<Query>& qs, int L, int R) {     //qs 中每个询问的答案都在 [L, R] 内
    if(qs.empty())    return;
    if(L == R) {
        for(auto& q : qs)    ans[q.id] = L;       //确定答案
        return;
    }
    int mid = (L + R) >> 1;
    while(cur < mid)    BIT_add(++cur, 1);        //把值 <= mid 的 a 位置陆续加进 BIT
    while(cur > mid)    BIT_add(cur--, -1);       //cur 只在整层范围内单调移动
    vector<Query> ql, qr;
    for(auto& q : qs) {
        int cnt = BIT_query(q.r) - BIT_query(q.l - 1);   //区间内 <= mid 的个数
        if(cnt >= q.k)    ql.push_back(q);       //第 k 小在 [L, mid] 内
        else {
            q.k -= cnt;                          //左半贡献掉 cnt 个, 去右半找第 k-cnt 小
            qr.push_back(q);
        }
    }
    while(cur > 0)    BIT_add(cur--, -1);        //清空 BIT(cur 回到 0, 下轮从左扫起)
    solve(ql, L, mid);
    solve(qr, mid + 1, R);
}
//配套:
//1. 静态区间第 k 小: 上面框架; 动态(带修改)第 k 小: 把修改也作为事件参与二分, 三维 (时间, 位置, 值)
//2. 单点修改 + 区间第 k 大: 修改拆成"删旧值/加新值"事件, 用 BIT 按值维护位置
//3. 单调性判定类问题(不用 BIT, 用 check(mid) 分批)也能整体二分, 如"第 k 个满足条件的值"

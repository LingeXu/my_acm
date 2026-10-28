//线段树合并: 动态开点权值线段树的合并, 总复杂度 O(总节点数 log n)(每合并一层删一层)
//适用: 树上统计子树内信息(颜色出现次数等)、整体权值分布合并; 配合树上差分
//需预定义: int sum[MAXN * 20], ls[MAXN * 20], rs[MAXN * 20], root[N], node_cnt;
//         MAXN * 20 按"每次操作新增 log n 个节点"估, 常见 20 倍
//入口: dfs 时 root[u] = merge(root[u], root[v]);
//注意: 合并是破坏性的(会修改两棵树), 若后面还要用原树需新建节点(可持久化合并)

int new_node() {
    return ++node_cnt;
}

void update(int& p, int l, int r, int pos, int val) {   //动态开点单点修改
    if(!p)    p = new_node();
    sum[p] += val;
    if(l == r)    return;
    int mid = (l + r) >> 1;
    if(pos <= mid)    update(ls[p], l, mid, pos, val);
    else    update(rs[p], mid + 1, r, pos, val);
}

int merge(int x, int y, int l, int r) {                 //合并两棵树, 返回合并后的根
    if(!x || !y)    return x + y;                       //一边为空直接接上(O(1) 剪枝)
    if(l == r) {                                        //叶子: 合并信息(按题目, 如求和)
        sum[x] += sum[y];
        return x;
    }
    int mid = (l + r) >> 1;
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid + 1, r);
    sum[x] = sum[ls[x]] + sum[rs[x]];
    return x;
}

int query(int p, int l, int r, int ql, int qr) {        //区间查询(如颜色种数 = 区间内 cnt > 0 的个数)
    if(!p)    return 0;
    if(ql <= l && r <= qr)    return sum[p];
    int mid = (l + r) >> 1, res = 0;
    if(ql <= mid)    res += query(ls[p], l, mid, ql, qr);
    if(qr > mid)     res += query(rs[p], mid + 1, r, ql, qr);
    return res;
}
//配套:
//1. 树上差分 + 合并: 每条链修改转为 4 个点的差分标记, 每点建一棵线段树, 自底向上合并
//2. 第 k 大合并树: 叶子存计数, 合并后直接在树上二分第 k 大
//3. 可持久化合并: merge 内新建节点复制 x, 保留两棵原树(空间翻倍)

//FHQ Treap: 无旋平衡树, 按值 split + 随机优先级 merge, 支持排名/第k大/前驱后继/插入删除
//优势: 比 Splay 好写且可持久化; 期望 O(log n), 随机优先级保证期望平衡
//需预定义: int ls[MAXN], rs[MAXN], val[MAXN], sz[MAXN];  mt19937 rng;
//         int root, node_cnt;   (可持久化版本见配套)
//入口: root = build(a, 1, n) 或逐次 root = insert(root, x);  空树 root = 0
//应用: 文艺平衡树(区间翻转/区间加) = 按大小 split 的版本, 见配套

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int ls[MAXN], rs[MAXN], val[MAXN], sz[MAXN];
unsigned prio[MAXN];                       //随机优先级(大根堆: 父亲 prio 大于儿子)
int root, node_cnt;

int new_node(int x) {
    int p = ++node_cnt;
    ls[p] = rs[p] = 0;
    val[p] = x;
    sz[p] = 1;
    prio[p] = rng();
    return p;
}

void push_up(int p) {
    sz[p] = sz[ls[p]] + sz[rs[p]] + 1;
}

//按值 split: 左树所有值 <= k, 右树所有值 > k
void split(int p, int k, int& x, int& y) {
    if(!p) {
        x = y = 0;
        return;
    }
    if(val[p] <= k) {                      //p 及其左子树归左树, 右子树继续拆
        x = p;
        split(rs[p], k, rs[p], y);
    }
    else {                                 //p 及其右子树归右树
        y = p;
        split(ls[p], k, x, ls[p]);
    }
    push_up(p);
}

//merge: 左树所有值 < 右树所有值(严格), 按 prio 合并保持堆性质
int merge(int x, int y) {
    if(!x || !y)    return x + y;
    if(prio[x] > prio[y]) {
        rs[x] = merge(rs[x], y);
        push_up(x);
        return x;
    }
    else {
        ls[y] = merge(x, ls[y]);
        push_up(y);
        return y;
    }
}

int insert(int root, int k) {              //插入值 k(重复值可多次插入)
    int x, y;
    split(root, k, x, y);
    return merge(merge(x, new_node(k)), y);
}

int erase(int root, int k) {               //删除一个值为 k 的节点
    int x, y, z;
    split(root, k, x, z);                  //x: <= k
    split(x, k - 1, x, y);                 //y: == k 的所有节点
    y = merge(ls[y], rs[y]);               //丢掉 y 的根(删一个 k), 或直接丢整棵 y(删全部 k)
    return merge(merge(x, y), z);
}

int rank(int root, int k) {                //k 的排名(有多少个数 < k, 再 +1)
    int x, y;
    split(root, k - 1, x, y);
    int res = sz[x] + 1;
    root = merge(x, y);
    return res;
}

int kth(int p, int k) {                    //第 k 小(1 <= k <= sz[p])
    while(true) {
        if(sz[ls[p]] >= k)    p = ls[p];
        else if(sz[ls[p]] + 1 == k)    return val[p];
        else {
            k -= sz[ls[p]] + 1;
            p = rs[p];
        }
    }
}

int prev(int root, int k) {                //k 的前驱(严格小于 k 的最大值), 不存在返回极小值
    int x, y;
    split(root, k - 1, x, y);
    int res = (x ? kth(x, sz[x]) : -INF);
    root = merge(x, y);
    return res;
}

int next(int root, int k) {                //k 的后继(严格大于 k 的最小值), 不存在返回极大值
    int x, y;
    split(root, k, x, y);
    int res = (y ? kth(y, 1) : INF);
    root = merge(x, y);
    return res;
}
//配套:
//1. 按大小 split(区间操作): split(p, k, x, y) 按"前 k 个元素"拆(比较 sz[ls]+1 <= k);
//   区间翻转: 懒标记 rev, 翻转 [l, r] = split 出中间段, 打标记, merge 回去, 下传时交换 ls/rs
//2. 可持久化: split/merge 时不改原节点, 新建副本(路径复制), 每次操作返回新根
//3. 集合判重: 插入前先查 prev/next 或维护 cnt 计数

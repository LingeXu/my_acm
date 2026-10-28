//trie 字典树: 字符串集合的插入/查询; 二进制 trie 处理异或类问题
//思想: 每条边代表一个字符, 节点代表"从根走到它的前缀"; 公共前缀共享路径, 空间 = 总字符数
//需预定义: int trie[MAXN][MAXC], trie_node_cnt;
//         const int MAXC = 26(小写字母) 或 2(二进制 trie);  MAXN = 总字符数 + 1(按题目开)

//---------------- 基础字符串 trie ----------------
void trie_init() {                         //与 AC自动机 的 ac_init 区分, 避免重名
    trie_node_cnt = 0;
    memset(trie, 0, sizeof(trie));
}

void insert(const string& s) {             //插入一个串
    int cur = 0;                           //根为 0
    for(char c : s) {
        int idx = c - 'a';
        if(!trie[cur][idx])    trie[cur][idx] = ++trie_node_cnt;
        cur = trie[cur][idx];
    }
    //end_cnt[cur]++: 标记 cur 为单词结尾(计数或布尔, 按题目)
}

bool trie_query(const string& s) {         //查询串是否存在/是否前缀(与 AC自动机 的 query 区分)
    int cur = 0;
    for(char c : s) {
        int idx = c - 'a';
        if(!trie[cur][idx])    return false;
        cur = trie[cur][idx];
    }
    return true;                           //或 return end_cnt[cur] > 0
}

//---------------- 二进制 trie: 异或最值等 ----------------
//每个数按二进制从高到低插入(位宽固定), 根到叶的路径就是数本身
//需预定义: const int MAX_BITS = 30;   (比最大值的最高位大 1, 如值 <= 1e9 用 30)

void InsertNode(int num) {
    int current = 0;
    for(int i = MAX_BITS; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if(!trie[current][bit])
            trie[current][bit] = ++trie_node_cnt;
        current = trie[current][bit];
    }
}

int QueryMaxXor(int num) {                 //集合中与 num 异或的最大值: 每位贪心走"相反位"
    int cur = 0, res = 0;
    for(int i = MAX_BITS; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if(trie[cur][bit ^ 1]) {           //能走相反位就走, 异或结果该位为 1
            res |= 1 << i;
            cur = trie[cur][bit ^ 1];
        }
        else    cur = trie[cur][bit];      //否则被迫走同向位, 该位结果为 0
    }
    return res;
}
//配套: 第 k 小 = 节点存子树大小, 从高到低判左子树够不够 k;  全局异或 tag = 懒标记交换左右子树
//      可持久化 trie(前缀版本相减)可做"区间内与 x 异或的最大值"

//---------------- AC自动机: 多模式串匹配, 文本走一遍同时匹配所有模式串 ----------------
//思想: trie + KMP 的 fail 指针; fail[x] = "x 代表的串的最长真后缀"所在节点,
//      匹配失败时跳 fail 而不是回退文本指针
//约定: 根为节点 1(不用 0, 留作虚根); build 时把 trie 补全成"转移图":
//      节点 x 的字符 i 转移不存在时, trie[x][i] 直接指到 trie[fail[x]][i], 匹配时不用判空
//需预定义: int trie[MAXN][MAXC], fail[MAXN], end_cnt[MAXN], trie_node_cnt;
//         const int MAXC = 26;   MAXN = 所有模式串总长度 + 1
//入口: ac_init(); 对每个模式串 Insert(s); build();  之后 query(text) 统计出现次数
//复杂度: 建图 O(总长度 * 字符集), 匹配 O(|text| + 答案)

void ac_init() {
    trie_node_cnt = 1;                     //根为 1
    memset(trie, 0, sizeof(trie));
    memset(end_cnt, 0, sizeof(end_cnt));
    memset(fail, 0, sizeof(fail));
    for(int i = 0; i < MAXC; i++)
        trie[0][i] = 1;                    //虚根 0 的所有转移指向根, 使"根的孩子的 fail"自然为根
}

void Insert(const string& s) {             //插入模式串
    int cur = 1;
    for(char c : s) {
        int idx = c - 'a';
        if(!trie[cur][idx])
            trie[cur][idx] = ++trie_node_cnt;
        cur = trie[cur][idx];
    }
    end_cnt[cur]++;                        //该节点为一个模式串结尾
}

void build() {                             //BFS 按层求 fail 并补全转移
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = 0; i < MAXC; i++) {
            if(trie[x][i]) {
                fail[trie[x][i]] = trie[fail[x]][i];   //儿子的 fail = 父亲 fail 的对应转移
                q.push(trie[x][i]);                    //(父亲的 fail 已算好, 直接跳)
            }
            else trie[x][i] = trie[fail[x]][i];        //转移不存在: 补全为 fail 的转移
        }
    }
}

int query(const string& text) {            //所有模式串在 text 中的总出现次数(可重复计)
    int cur = 1, ans = 0;
    for(char c : text) {
        int idx = c - 'a';
        cur = trie[cur][idx];              //转移图已补全, 直接走, 绝不回退文本指针
        for(int i = cur; i; i = fail[i])   //cur 及其所有 fail 祖先都可能以该位置结尾
            ans += end_cnt[i];
    }
    return ans;
}

bool contain(const string& text) {         //text 是否包含任意一个模式串(找着即停)
    int cur = 1;
    for(char c : text) {
        int idx = c - 'a';
        cur = trie[cur][idx];
        for(int i = cur; i; i = fail[i])
            if(end_cnt[i])
                return true;
    }
    return false;
}
//配套:
//1. 求每个模式串的出现次数: 逐位置跳 fail 链最坏 O(|text| * 最长模式串) 会 TLE;
//   优化: 匹配时只给 cur 打标记 cnt[cur]++, 最后按 BFS 逆序(BFS 序的拓扑序)累加
//   cnt[fail[x]] += cnt[x], 则 cnt[x] 即以 x 结尾的模式串出现次数(每个位置 O(1))
//2. 只计一次(每个模式串至多计一次): 匹配到后把 end_cnt 清零/打负, 或 visited 标记
//3. fail 树: fail 指针构成以根为根的树, x 的 fail 子树 = 以 x 为后缀的所有节点;
//   配合 dfs 序 + 树状数组可做在线多串问题
//4. 自动机 DP: 状态就是自动机节点, 可做"不含某些子串"的计数(数位 DP/矩阵快速幂转移)

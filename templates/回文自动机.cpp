//回文自动机 PAM: O(n) 构建, 每个本质不同的回文子串对应一个节点(节点数 = 本质不同回文数 + 2)
//状态 v 表示一个回文串; len[v] = 回文长度; fail[v] = 最长回文后缀所在状态
//两个根: 1 = 奇根(len = -1), 0 = 偶根(len = 0); fail[0] = 1
//需预定义: int nxt[MAXN][26], fail[MAXN], len[MAXN], cnt[MAXN], last;
//         MAXN = 串长 + 5(每个字符最多新增一个节点)
//入口: pam_init(); 对每个字符 pam_extend(s, i);
//在线性质: 可边读边处理; last 始终 = 以当前字符结尾的最长回文后缀

int nxt[MAXN][26], fail[MAXN], len[MAXN], cnt[MAXN];
int pam_node_cnt, last;                    //last = 上一次插入后所在的状态

int get_fail(int x, int i, const string& s) {   //沿 fail 跳, 找"能在 s[i] 处接上"的最长回文后缀
    while(i - len[x] - 1 < 0 || s[i - len[x] - 1] != s[i])    x = fail[x];
    return x;
}

void pam_init() {
    pam_node_cnt = 1;
    last = 0;
    memset(nxt, 0, sizeof(nxt));
    fail[0] = 1;
    len[1] = -1;                           //奇根: 长度为 -1, 保证单字符回文 len = 1 正确
}

void pam_extend(const string& s, int i) {  //把 s[i] 插入自动机
    int c = s[i] - 'a';
    int cur = get_fail(last, i, s);
    if(!nxt[cur][c]) {                    //新回文串, 新建节点
        int now = ++pam_node_cnt;
        len[now] = len[cur] + 2;
        fail[now] = nxt[get_fail(fail[cur], i, s)][c];
        nxt[cur][c] = now;
    }
    last = nxt[cur][c];
    cnt[last]++;                           //出现次数(每次插入给最长回文后缀 +1, 最后 fail 树累加)
}
//配套:
//1. 本质不同回文子串数 = pam_node_cnt - 1(节点数减奇根)
//2. 每个回文串的出现次数: 从后往前(节点编号就是拓扑序) cnt[fail[v]] += cnt[v]
//3. 以每个位置结尾的回文串: 从 last 沿 fail 链走, 链长 = 个数(len 各不相同)
//4. 回文子串计数 DP: dp[v] = 该状态转移出去的所有回文串数 + 1, 用于求第 k 小回文子串
//5. 最小回文划分(把串切成若干回文段的最少段数): 配合 fail 链的等差优化(难), 朴素 O(n^2)

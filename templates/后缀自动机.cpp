//后缀自动机 SAM: O(n) 构建, 用最少状态表示串的所有子串(状态数 <= 2n, 转移数 <= 3n)
//状态 v 代表"endpos 集合相同的一组子串", 其长度构成区间 (len[link[v]], len[v]]
//link[v] = 后缀链接, 指向"最长真后缀所在状态"; 沿 link 走到根 = 枚举所有后缀
//需预定义: struct 或全局数组: nxt[MAXN][26], link[MAXN], len[MAXN];
//         MAXN = 2 * 串长 + 5;  字符集 26 按需改
//入口: sam_init(); 对每个字符 sam_extend(c);  状态从 1 开始, 根 = 1

int nxt[MAXN][26], link[MAXN], len[MAXN];
int sam_node_cnt, sam_last;                //当前节点数 / 整个串所在的状态

void sam_init() {
    sam_node_cnt = 1;
    sam_last = 1;
    memset(nxt, 0, sizeof(nxt));
    link[1] = 0;                           //根的后缀链接指向空状态 0
    len[1] = 0;
}

void sam_extend(int c) {                   //末尾追加字符 c, 更新 last
    int cur = ++sam_node_cnt;              //新状态: 代表以新字符结尾的所有新后缀
    len[cur] = len[sam_last] + 1;
    int p = sam_last;
    while(p && !nxt[p][c]) {              //从 last 沿 link 往上, 给没有 c 转移的状态补转移
        nxt[p][c] = cur;
        p = link[p];
    }
    if(!p)    link[cur] = 1;               //走到空状态: 所有后缀都是新后缀, 直接连根
    else {
        int q = nxt[p][c];
        if(len[q] == len[p] + 1)    link[cur] = q;    //q 正好是 p 的后缀, 直接连
        else {                                      //否则拆状态: 复制 q, 长的留 q, 短的给 clone
            int clone = ++sam_node_cnt;
            len[clone] = len[p] + 1;
            memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
            link[clone] = link[q];
            while(p && nxt[p][c] == q) {           //把指向 q 且"经过 p"的转移改指 clone
                nxt[p][c] = clone;
                p = link[p];
            }
            link[q] = link[cur] = clone;
        }
    }
    sam_last = cur;
}

//配套:
//1. 本质不同子串数 = sum(len[v] - len[link[v]]), v 从 2 到 sam_node_cnt(在线: 每次加字符累加 len[cur]-len[link[cur]])
//2. 某子串是否出现/出现次数: 从根沿字符走; 出现次数 = 状态 v 的 endpos 大小:
//   cnt[cur] = 1(每次 extend 的新状态), 按 len 桶排序从大到小 cnt[link[v]] += cnt[v]
//   则 cnt[v] = 该状态代表的子串出现次数
//3. 两串最长公共子串: 对 s1 建 SAM, 用 s2 在自动机上跑, 失配跳 link, 维护当前匹配长度, 取 max
//4. 第 k 小子串: 按 len 桶排序后 DP 出每个状态出发的路径数, 从根贪心走
//5. 最小循环位移: 串 s+s 在 SAM 上贪心走 n 步取最小字符
//6. 与后缀数组的关系: 后缀树 = SAM 的 link 树(反串); SAM 的 link 树 = 后缀树的压缩

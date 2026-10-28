//KMP: 单模式串匹配, O(n + m) 返回模式串 pat 在文本 ob 中所有出现位置(下标 0-based)
//核心: next 数组 = "前缀的最长真前后缀长度"的位移版, 失配时跳 next 而不是回退文本指针
//约定: next[0] = -1, next[i] = pat[0..i-1] 的最长真前后缀长度

vector<int> init(const string& pat) {      //求 next 数组
    int n = pat.size();
    vector<int> res(n + 1);
    res[0] = -1;
    int i = 0, j = -1;                     //i 逐步后移, j 维护当前最长真前后缀长度
    while(i < n) {
        if(j == -1 || pat[i] == pat[j])    //能延伸
            res[++i] = ++j;
        else    j = res[j];                //失配, j 回退到次长真前后缀
    }
    return res;
}

vector<int> KMP(const string& ob, const string& pat) {   //返回所有匹配起始下标
    vector<int> res;
    int n = ob.size(), m = pat.size();
    vector<int> next = init(pat);
    int i = 0, j = 0;
    while(i < n) {
        if(j == -1 || ob[i] == pat[j]) {
            i++;
            j++;
        }
        else    j = next[j];
        if(j == m) {                       //匹配到一次
            res.push_back(i - m);
            j = next[j];                   //继续找下一个(允许重叠)
        }
    }
    return res;
}
//配套: 最短循环节: 若 n % (n - next[n]) == 0, 则循环节长度 = n - next[n]
//      多模式串匹配见 trie.cpp 的 AC自动机

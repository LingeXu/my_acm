//CDQ分治: 离线分治, 用"前一半对后一半的贡献"解决偏序/带修改查询类问题
//核心: solve(l, r) = 递归处理左半、右半, 再统计"左半元素对右半元素的贡献"(线性合并)
//以三维偏序(陌上花开)为例: 统计每个点被多少个点"三维都不超过"
//思路: 按 a 排序消除第一维, CDQ 分治按 b 归并消除第二维, 树状数组按 c 消除第三维
//复杂度: O(n log^2 n)
//需预定义: struct Node { int a, b, c, id; };  Node p[N];  int ans[N];  树状数组见 树状数组.cpp

//示例框架(二维偏序思路, 三维加 BIT):
void cdq(int l, int r) {
    if(l == r)    return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    //--- 统计左半对右半的贡献: 此时两半内部已按 b 有序 ---
    //双指针归并: 扫右半的每个点, 把左半 b 满足条件的按 c 加入 BIT, 查询 c 前缀和
    int i = l;
    for(int j = mid + 1; j <= r; j++) {
        while(i <= mid && p[i].b <= p[j].b) {
            BIT_add(p[i].c, 1);           //左半元素入树状数组(第三维)
            i++;
        }
        ans[p[j].id] += BIT_query(p[j].c); //统计 c <= p[j].c 的左半元素个数
    }
    for(int k = l; k < i; k++)    BIT_add(p[k].c, -1);   //撤销 BIT, 不能用 memset(会退化)
    //--- 按 b 归并排序, 保证上层递归时两半有序 ---
    inplace_merge(p + l, p + mid + 1, p + r + 1, [](Node x, Node y) { return x.b < y.b; });
}
//调用: sort(p + 1, p + n + 1, 按 a);  cdq(1, n);
//注意: 完全相同元素要合并计数(去重)再拆贡献, 否则互相统计不到; 或用 a <= 等的带等号版本

//配套:
//1. 带修改的离线查询(时间维): 每个修改拆成"在 t 时刻 +val", 查询 = 前缀和差, 三维 (t, pos, 类型)
//2. 二维偏序/逆序对: cdq 里的 BIT 去掉即 O(n log n) 归并统计
//3. 决策单调性 DP 的 cdq 分治优化: solve(l, r, optL, optR) 转移区间劈半, 复杂度 O(n log n)

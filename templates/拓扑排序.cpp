//拓扑排序: 有向无环图(DAG)的线性序列, 每条边 u->v 都满足 u 在 v 前面
//应用: 判环 / DAG 上 DP(按拓扑序转移) / 缩点后处理; O(n + m)
//需预定义: vector<int> graph[N];  int in_deg[N];
//入口: topo();  返回序列存于 vector topo 中, 长度 < n 说明有环
vector<int> graph[N];
int in_deg[N];
void topo() {
    vector<int> topo;
    memset(in_deg, 0, sizeof(in_deg));
    for(int i = 1; i <= n; i++) 
        for(int to : graph[i])
            in_deg[to]++;
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(in_deg[i] == 0)
            q.push(i);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        topo.push_back(x);
        for(int to : graph[x])
            if(--in_deg[to] == 0)
                q.push(to);
    }
    if(topo.size() != n)
        cout << "存在环";
}
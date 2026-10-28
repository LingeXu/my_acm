//dijkstra: 单源最短路(堆优化), O((V + E) log V), 要求边权非负
//需预定义: vector< pair<int, int> > graph[N];  (pair 为 (边权, 邻点));  int dist[N];
//入口: dijkstra(s);  结果在 dist[i], 不可达为 INF
vector< pair<int, int> > graph[N];
void dijkstra(int s) {
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    pq.push({0, s});
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    while(!pq.empty()) {
        auto x = pq.top();
        pq.pop();
        if(x.first > dist[x.second])   continue;      //堆里的过期状态, 跳过(懒删除)
        for(auto& e : graph[x.second]) {
            if(dist[e.second] > dist[x.second] + e.first) {
                dist[e.second] = dist[x.second] + e.first;
                pq.push({dist[e.second], e.second});
            }
        }
    }
}
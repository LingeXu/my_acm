//bellmanford: 单源最短路(可负权边) + 判负环, O(nm)
//需预定义: struct edge { int u, v, w; };  vector<edge> graph;  int dist[N];
//入口: bellmanford(s);  判负环: 第 n 轮仍能松弛说明 s 可达的路径上存在负环
struct edge {
    int u, v, w;
};
vector<edge> graph;
int dist[N];
void bellmanford(int s) {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    for(int i = 1; i <= n - 1; i++) {
        bool updated = false;
        for(auto& e : graph) {
            if(dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if(!updated)    break;
    }
    for(auto& e : graph)
        if(dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
            cout << "存在负环";
}
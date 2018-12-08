class Dinic{
private:
  using CapT = int64_t;
  struct Edge{
    int to, rev;
    CapT cap;
  };
  int n, st, ed;
  vector<vector<Edge>> G;
  vector<int> lv;
  bool BFS(){
    fill(lv.begin(), lv.end(), -1);
    queue<int> bfs;
    bfs.push(st);
    lv[st] = 0;
    while(!bfs.empty()){
      int u = bfs.front(); bfs.pop();
      for(auto e: G[u]){
        if(e.cap <= 0 or lv[e.to]!=-1) continue;
        lv[e.to] = lv[u] + 1;
        bfs.push(e.to);
      }
    }
    return (lv[ed]!=-1);
  }
  CapT DFS(int u, CapT f){
    if(u == ed) return f;
    CapT ret = 0;
    for(auto& e: G[u]){
      if(e.cap <= 0 or lv[e.to]!=lv[u]+1) continue;
      CapT nf = DFS(e.to, min(f, e.cap));
      ret += nf; e.cap -= nf; f -= nf;
      G[e.to][e.rev].cap += nf;
      if(f == 0) return ret;
    }
    if(ret == 0) lv[u] = -1;
    return ret;
  }
public:
  void init(int n_, int st_, int ed_){
    n = n_, st = st_, ed = ed_;
    G.resize(n); lv.resize(n);
    fill(G.begin(), G.end(), vector<Edge>());
  }
  void add_edge(int u, int v, CapT c){
    G[u].push_back({v, (int)(G[v].size()), c});
    G[v].push_back({u, (int)(G[u].size())-1, 0});
  }
  CapT max_flow(){
    CapT ret = 0;
    while(BFS()){
      CapT f = DFS(st, numeric_limits<CapT>::max());
      ret += f;
      if(f == 0) break;
    }
    return ret;
  }
} flow;

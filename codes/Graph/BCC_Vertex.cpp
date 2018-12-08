class BCC{
private:
  vector<vector<pair<int,int>>> G;
  vector<int> dfn, low, id, sz;
  vector<bool> vis, ap;
  int n, ecnt, bcnt;
  void tarjan(int u, int f, int d){
    vis[u] = true;
    dfn[u] = low[u] = d;
    int child = 0;
    for(auto e: G[u]) if(e.first != f){
      int v = e.first;
      if(vis[v]){
        low[u] = min(low[u], dfn[v]);
      }else{
        tarjan(v, u, d+1);
        if(low[v] >= dfn[u]) ap[u] = true;
        low[u] = min(low[u], low[v]);
        child += 1;
      }
    }
    if(dfn[u]==0 and child <= 1) ap[u] = false;
  }
  void bfs_bcc(int x){
    // not sure
    queue<int> bfs;
    bfs.push(x); vis[x] = true;
    while(!bfs.empty()){
      int u = bfs.front(); bfs.pop();
      for(auto e: G[u]){
        id[e.second] = bcnt;
        if(ap[e.first] or vis[e.first]) continue;
        bfs.push(e.first); vis[e.first] = true;
        sz[bcnt] += 1;
      }
    }
  }
public:
  void init(int n_){
    n = n_; G.clear(); G.resize(n);
    dfn.resize(n); low.resize(n);
    vis.clear(); vis.resize(n);
    ap.clear(); ap.resize(n);
    ecnt = 0, bcnt = 0;
  }
  void add_edge(int u, int v){
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    G[u].emplace_back(v, ecnt);
    G[v].emplace_back(u, ecnt);
    ecnt += 1;
  }
  void solve(){
    for(int i=0;i<n;i++) if(!vis[i]) {
      tarjan(i, i, 0);
    }
    id.resize(ecnt);
    vis.clear(); vis.resize(n);
    sz.clear(); sz.resize(n);
    for(int i=0;i<n;i++) if(ap[i]){
      bfs_bcc(i); bcnt += 1;
    }
  }
  bool isAP(int x){return ap[x];}
  int count(){return bcnt;}
  // bcc_id of edges by insert order (0-base)
  int get_id(int x){return id[x];}
  // bcc size by bcc_id
  int get_size(int x){return sz[x];}
} bcc;

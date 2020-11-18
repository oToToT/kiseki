class BCC_Bridge {
  private:
    int n, ecnt;
    vector<vector<pair<int,int>>> G;
    vector<int> dfn, low;
    vector<bool> bridge;
    void dfs(int u, int f) {
      dfn[u] = low[u] = dfn[f] + 1;
      for (auto [v, t]: G[u]) {
        if (v == f) continue;
        if (dfn[v]) {
          low[u] = min(low[u], dfn[v]);
          continue;
        }
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] > dfn[u]) bridge[t] = true;
      }
    }
  public:
    void init(int n_) {
      G.clear(); G.resize(n = n_);
      low.assign(n, ecnt = 0);
      dfn.assign(n, 0);
    }
    void add_edge(int u, int v) {
      G[u].emplace_back(v, ecnt);
      G[v].emplace_back(u, ecnt++);
    }
    void solve() {
      bridge.assign(ecnt, false);
      for (int i = 0; i < n; ++i)
        if (not dfn[i]) dfs(i, i);
    }
    bool is_bridge(int x) { return bridge[x]; }
} bcc_bridge;

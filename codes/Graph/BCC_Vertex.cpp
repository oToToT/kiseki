class BCC_AP {
  private:
    int n, ecnt;
    vector<vector<pair<int,int>>> G;
    vector<int> bcc, dfn, low, st;
    vector<bool> ap, ins;
    void dfs(int u, int f) {
      dfn[u] = low[u] = dfn[f] + 1;
      int ch = 0;
      for (auto [v, t]: G[u]) if (v != f) {
        if (not ins[t]) {
          st.push_back(t);
          ins[t] = true;
        }
        if (dfn[v]) {
          low[u] = min(low[u], dfn[v]);
          continue;
        } ++ch; dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          ap[u] = true;
          while (true) {
            int eid = st.back(); st.pop_back();
            bcc[eid] = ecnt;
            if (eid == t) break;
          }
          ecnt++;
        }
      }
      if (ch == 1 and u == f) ap[u] = false;
    }
  public:
    void init(int n_) {
      G.clear(); G.resize(n = n_);
      ecnt = 0; ap.assign(n, false);
      low.assign(n, 0); dfn.assign(n, 0);
    }
    void add_edge(int u, int v) {
      G[u].emplace_back(v, ecnt);
      G[v].emplace_back(u, ecnt++);
    }
    void solve() {
      ins.assign(ecnt, false);
      bcc.resize(ecnt); ecnt = 0;
      for (int i = 0; i < n; ++i)
        if (not dfn[i]) dfs(i, i);
    }
    int get_id(int x) { return bcc[x]; }
    int count() { return ecnt; }
    bool is_ap(int x) { return ap[x]; }
} bcc_ap;

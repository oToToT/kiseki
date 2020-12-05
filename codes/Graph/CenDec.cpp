struct Centroid {
  vector<vector<int64_t>> Dist;
  vector<int> Parent, Depth;
  vector<int64_t> Sub, Sub2;
  vector<int> Sz, Sz2;
  Centroid(vector<vector<pair<int, int>>> g) {
    int N = g.size();
    vector<bool> Vis(N);
    vector<int> sz(N), mx(N);
    vector<int> Path;
    Dist.resize(N);
    Parent.resize(N);
    Depth.resize(N);
    auto DfsSz = [&](auto dfs, int x) -> void {
      Vis[x] = true; sz[x] = 1; mx[x] = 0;
      for (auto [u, w] : g[x]) {
        if (Vis[u]) continue;
        dfs(dfs, u);
        sz[x] += sz[u];
        mx[x] = max(mx[x], sz[u]);
      }
      Path.push_back(x);
    };
    auto DfsDist = [&](auto dfs, int x, int64_t D = 0)
      -> void {
      Dist[x].push_back(D);Vis[x] = true;
      for (auto [u, w] : g[x]) {
        if (Vis[u]) continue;
        dfs(dfs, u, D + w);
      }
    };
    auto Dfs = [&]
      (auto dfs, int x, int D = 0, int p = -1)->void {
      Path.clear(); DfsSz(DfsSz, x);
      int M = Path.size();
      int C = -1;
      for (int u : Path) {
        if (max(M - sz[u], mx[u]) * 2 <= M) C = u;
        Vis[u] = false;
      }
      DfsDist(DfsDist, C);
      for (int u : Path) Vis[u] = false;
      Parent[C] = p; Vis[C] = true;
      Depth[C] = D;
      for (auto [u, w] : g[C]) {
        if (Vis[u]) continue;
        dfs(dfs, u, D + 1, C);
      }
    };
    Dfs(Dfs, 0); Sub.resize(N); Sub2.resize(N);
    Sz.resize(N); Sz2.resize(N);
  }
  void Mark(int v) {
    int x = v, z = -1;
    for (int i = Depth[v]; i >= 0; --i) {
      Sub[x] += Dist[v][i]; Sz[x]++;
      if (z != -1) {
        Sub2[z] += Dist[v][i];
        Sz2[z]++;
      }
      z = x; x = Parent[x];
    }
  }
  int64_t Query(int v) {
    int64_t res = 0;
    int x = v, z = -1;
    for (int i = Depth[v]; i >= 0; --i) {
      res += Sub[x] + 1LL * Sz[x] * Dist[v][i];
      if (z != -1) res-=Sub2[z]+1LL*Sz2[z]*Dist[v][i];
      z = x; x = Parent[x];
    }
    return res;
  }
};

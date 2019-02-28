struct KM{
  static constexpr lld INF = 1LL<<60;
  lld w[N][N], lx[N], ly[N], slack[N];
  int match[N], n, vx[N], vy[N], step_;
  void init(int n_){
    n=n_,step=0;
    memset(w,0,sizeof(w));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(slack,0,sizeof(slack));
    memset(match,0,sizeof(match));
    memset(vx,0,sizeof(vx));
    memset(vy,0,sizeof(vy));
  }
  void add_edge(int u,int v,lld w){w[u][v]=w;}
  bool dfs(int x) {
    vx[x] = step_;
    for (int i = 0; i < n; ++i) {
      if (vy[i]==step_) continue;
      if (lx[x] + ly[i] > w[x][i]) {
        slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
        continue;
      }
      vy[i] = step_;
      if (match[i] == -1 || dfs(match[i])) {
        match[i] = x;
        return true;
      }
    }
    return false;
  }
  lld solve() {
    fill_n(match, n, -1);
    fill_n(lx, n, -INF);
    fill_n(ly, n, 0);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        lx[i] = max(lx[i], w[i][j]);
    for (int i = 0; i < n; ++i) {
      fill_n(slack, n, INF);
      while (true) {
        step_++;
        if (dfs(i)) break;
        lld dlt = INF;
        for (int j = 0; j < n; ++j) if (vy[j] != step_)
          dlt = min(dlt, slack[j]);
        for (int j = 0; j < n; ++j) {
          if (vx[j]==step_) lx[j] -= dlt;
          if (vy[j]==step_) ly[j] += dlt;
          else slack[j] -= dlt;
        }
      }
    }
    lld res = 0;
    for (int i = 0; i < n; ++i) res += w[match[i]][i];
    return res;
  }
} km;
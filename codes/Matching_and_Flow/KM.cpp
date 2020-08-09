class KM {
private:
  static constexpr lld INF = 1LL << 60;
  vector<lld> hl,hr,slk;
  vector<int> fl,fr,pre,qu;
  vector<vector<lld>> w;
  vector<bool> vl,vr;
  int n, ql, qr;
  bool check(int x) {
    if (vl[x] = true, fl[x] != -1)
      return vr[qu[qr++] = fl[x]] = true;
    while (x != -1) swap(x, fr[fl[x] = pre[x]]);
    return false;
  }
  void bfs(int s) {
    fill(slk.begin(), slk.end(), INF);
    fill(vl.begin(), vl.end(), false);
    fill(vr.begin(), vr.end(), false);
    ql = qr = 0;
    qu[qr++] = s;
    vr[s] = true;
    while (true) {
      lld d;
      while (ql < qr) {
        for (int x = 0, y = qu[ql++]; x < n; ++x) {
          if(!vl[x]&&slk[x]>=(d=hl[x]+hr[y]-w[x][y])){
            if (pre[x] = y, d) slk[x] = d;
            else if (!check(x)) return;
          }
        }
      }
      d = INF;
      for (int x = 0; x < n; ++x)
        if (!vl[x] && d > slk[x]) d = slk[x];
      for (int x = 0; x < n; ++x) {
        if (vl[x]) hl[x] += d;
        else slk[x] -= d;
        if (vr[x]) hr[x] -= d;
      }
      for (int x = 0; x < n; ++x)
        if (!vl[x] && !slk[x] && !check(x)) return;
    }
  }
public:
  void init( int n_ ) {
    n = n_; qu.resize(n);
    fl.clear(); fl.resize(n, -1);
    fr.clear(); fr.resize(n, -1);
    hr.clear(); hr.resize(n); hl.resize(n);
    w.clear(); w.resize(n, vector<lld>(n));
    slk.resize(n); pre.resize(n);
    vl.resize(n); vr.resize(n);
  }
  void set_edge( int u, int v, lld x ) {w[u][v] = x;}
  lld solve() {
    for (int i = 0; i < n; ++i)
      hl[i] = *max_element(w[i].begin(), w[i].end());
    for (int i = 0; i < n; ++i) bfs(i);
    lld res = 0;
    for (int i = 0; i < n; ++i) res += w[i][fl[i]];
    return res;
  }
} km;
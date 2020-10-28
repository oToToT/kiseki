struct cmp_y {
  bool operator()(const P& p, const P& q) const {
    return p.y < q.y;
  }
};
multiset<P, cmp_y> s;
void solve(P a[], int n) {
  sort(a, a + n, [](const P& p, const P& q) {
    return tie(p.x, p.y) < tie(q.x, q.y);
  });
  llf d = INF; int pt = 0;
  for (int i = 0; i < n; ++i) {
    while (pt < i and a[i].x - a[pt].x >= d)
      s.erase(s.find(a[pt++]));
    auto it = s.lower_bound(P(a[i].x, a[i].y - d));
    while (it != s.end() and it->y - a[i].y < d)
      d = min(d, dis(*(it++), a[i]));
    s.insert(a[i]);
  }
}

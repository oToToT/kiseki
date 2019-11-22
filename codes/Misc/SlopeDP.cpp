inline lld DivCeil(lld n, lld d) { // ceil(n/d)
  return n / d + (((n < 0) != (d > 0)) && (n % d));
}
struct Line {
  static bool flag;
  lld a, b, l, r; // y=ax+b in [l, r)
  lld operator()(lld x) const { return a * x + b; }
  bool operator<(const Line& i) const {
    return flag ? tie(a, b) < tie(i.a, i.b) : l < i.l;
  }
  lld operator&(const Line& i) const {
    return DivCeil(b - i.b, i.a - a);
  }
};
bool Line::flag = true;
class ConvexHullMax {
  set<Line> L;
 public:
  ConvexHullMax() { Line::flag = true; }
  void InsertLine(lld a, lld b) { // add y = ax + b
    Line now = {a, b, -INF, INF};
    if (L.empty()) {
      L.insert(now);
      return;
    }
    Line::flag = true;
    auto it = L.lower_bound(now);
    auto prv = it == L.begin() ? it : prev(it);
    if (it != L.end() && ((it != L.begin() &&
      (*it)(it->l) >= now(it->l) &&
      (*prv)(prv->r - 1) >= now(prv->r - 1)) ||
      (it == L.begin() && it->a == now.a))) return;
    if (it != L.begin()) {
      while (prv != L.begin() &&
        (*prv)(prv->l) <= now(prv->l))
          prv = --L.erase(prv);
      if (prv == L.begin() && now.a == prv->a)
        L.erase(prv);
    }
    if (it != L.end())
      while (it != --L.end() &&
        (*it)(it->r) <= now(it->r))
          it = L.erase(it);
    if (it != L.begin()) {
      prv = prev(it);
      const_cast<Line*>(&*prv)->r=now.l=((*prv)&now);
    }
    if (it != L.end())
      const_cast<Line*>(&*it)->l=now.r=((*it)&now);
    L.insert(it, now);
  }
  lld Query(lld a) const { // query max at x=a
    if (L.empty()) return -INF;
    Line::flag = false;
    auto it = --L.upper_bound({0, 0, a, 0});
    return (*it)(a);
  }
};
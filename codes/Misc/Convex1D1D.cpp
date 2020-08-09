struct segment {
  int i, l, r;
  segment() {}
  segment(int a, int b, int c): i(a), l(b), r(c) {}
};
inline lld f(int l, int r){return dp[l] + w(l+1, r);}
void solve() {
  dp[0] = 0;
  deque<segment> dq; dq.push_back(segment(0, 1, n));
  for (int i = 1; i <= n; ++i) {
    dp[i] = f(dq.front().i, i);
    while(dq.size()&&dq.front().r<i+1) dq.pop_front();
    dq.front().l = i + 1;
    segment seg = segment(i, i + 1, n);
    while (dq.size() &&
      f(i, dq.back().l)<f(dq.back().i, dq.back().l))
        dq.pop_back();
    if (dq.size()) {
      int d = 1 << 20, c = dq.back().l;
      while (d >>= 1) if (c + d <= dq.back().r)
        if(f(i, c+d) > f(dq.back().i, c+d)) c += d;
      dq.back().r = c; seg.l = c + 1;
    }
    if (seg.l <= n) dq.push_back(seg);
  }
}
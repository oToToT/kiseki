VI inverse(const VI &v, int n) {
  VI q(1, fpow(v[0], mod - 2));
  for (int i = 2; i <= n; i <<= 1) {
    VI fv(v.begin(), v.begin() + i); 
    VI fq(q.begin(), q.end());
    fv.resize(2 * i), fq.resize(2 * i);
    ntt(fq, 2 * i), ntt(fv, 2 * i);
    for (int j = 0; j < 2 * i; ++j)
      fv[j] = fv[j]*1ll*fq[j]%mod*fq[j]%mod;
    intt(fv, 2 * i);
    VI res(i);
    for (int j = 0; j < i; ++j) {
      res[j] = mod - fv[j];
      if (j < (i>>1)) (res[j] += 2*q[j]%mod) %= mod;
    }
    q = res;
  }
  return q;
}
VI divide(const VI &a, const VI &b) {
  // leading zero should be trimmed
  int n = (int)a.size(), m = (int)b.size();
  int k = 2;
  while (k < n - m + 1) k <<= 1;
  VI ra(k), rb(k);
  for (int i = 0; i < min(n, k); ++i) ra[i] = a[n-i-1];
  for (int i = 0; i < min(m, k); ++i) rb[i] = b[m-i-1];
  VI rbi = inverse(rb, k);
  VI res = convolution(rbi, ra);
  res.resize(n - m + 1);
  reverse(res.begin(), res.end());
  return res;
}
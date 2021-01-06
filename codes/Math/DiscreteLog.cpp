lld BSGS(lld P, lld B, lld N) {
  // find B^L = N mod P
  unordered_map<lld, int> R;
  lld sq = (lld)sqrt(P);
  lld t = 1;
  for (int i = 0; i < sq; i++) {		
    if (t == N)	return i; 		
    if (!R.count(t)) R[t] = i;
    t = (t * B) % P;
  }
  lld f = inverse(t, P);
  for(int i=0;i<=sq+1;i++) {
    if (R.count(N))
      return i * sq + R[N];
    N = (N * f) % P;
  }
  return -1;
}

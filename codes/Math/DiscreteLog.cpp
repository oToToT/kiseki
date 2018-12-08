// Baby-step Giant-step Algorithm
// a x + by = g
void exgcd(long long  x, long long y, long long &g, long long &a, long long &b) {
  if (y == 0)
    g = x, a = 1, b = 0;
  else
    exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long inverse(long long x, long long p) {
  long long g, b, r;
  exgcd(x, p, g, r, b);
  if (g < 0)	r = -r;
  return (r%p + p)%p;
}
long long BSGS(long long P, long long B, long long N) {
  // find B^L = N mod P
  unordered_map<long long, int> R;
  long long sq = (long long) sqrt(P);
  long long t = 1, f;
  for (int i = 0; i < sq; i++) {		
    if (t == N)	
      return i; 		
    if (!R.count(t))
      R[t] = i;
    t = (t * B) % P;
  }
  
  f = inverse(t, P);
  for (int i = 0; i <= sq+1; i++) {
    if (R.count(N))
      return i * sq + R[N];
    N = (N * f) % P;
  }
  return -1;
}
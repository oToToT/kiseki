static constexpr int N = 1000000 + 5;
lld pi[N];
vector<int> primes;
bool sieved[N];
lld cube_root(lld x){
  lld s = static_cast<lld>(cbrt(x - static_cast<long double>(0.1)));
  while(s*s*s <= x) ++s;
  return s-1;
}
lld square_root(lld x){
  lld s = static_cast<lld>(sqrt(x - static_cast<long double>(0.1)));
  while(s*s <= x) ++s;
  return s-1;
}
void init(){
  primes.reserve(N);
  primes.push_back(1);
  for(int i=2;i<N;i++) {
    if(!sieved[i]) primes.push_back(i);
    pi[i] = !sieved[i] + pi[i-1];
    for(int p: primes) if(p > 1) {
      if(p * i >= N) break;
      sieved[p * i] = true;
      if(p % i == 0) break;
    }
  }
}
lld phi(lld m, lld n) {
  static constexpr int MM = 80000, NN = 500;
  static lld val[MM][NN];
  if(m < MM and n < NN and val[m][n]) return val[m][n] - 1;
  if(n == 0) return m;
  if(primes[n] >= m) return 1;
  lld ret = phi(m, n - 1) - phi(m / primes[n], n - 1);
  if(m < MM and n < NN) val[m][n] = ret + 1;
  return ret;
}
lld pi_count(lld);
lld P2(lld m, lld n) {
  lld sm = square_root(m), ret = 0;
  for(lld i = n+1;primes[i]<=sm;i++)
    ret += pi_count(m / primes[i]) - pi_count(primes[i]) + 1;
  return ret;
}
lld pi_count(lld m) {
  if(m < N) return pi[m];
  lld n = pi_count(cube_root(m));
  return phi(m, n) + n - 1 - P2(m, n);
}
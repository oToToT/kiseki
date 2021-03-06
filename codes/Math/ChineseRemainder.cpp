lld crt(lld ans[], lld pri[], int n){
  lld M = 1, ret = 0;
  for(int i=0;i<n;i++) M *= pri[i];
  for(int i=0;i<n;i++){
    lld iv = (gcd(M/pri[i],pri[i]).FF+pri[i])%pri[i];
    ret += (ans[i]*(M/pri[i])%M * iv)%M;
    ret %= M;
  }
  return ret;
}
/*
Another:
x = a1 % m1
x = a2 % m2
g = gcd(m1, m2)
assert((a1-a2)%g==0)
[p, q] = exgcd(m2/g, m1/g)
return a2+m2*(p*(a1-a2)/g)
0 <= x < lcm(m1, m2)
*/

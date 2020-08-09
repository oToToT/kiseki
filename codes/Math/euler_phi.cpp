/*
   extended euler:
   a^b mod p
   if gcd(a, p)==1: a^(b%phi(p))
   elif b < phi(p): a^b mod p
   else a^(b%phi(p) + phi(p))
 */
lld euler_phi(int x){
  lld r=1;
  for(int i=2;i*i<=x;++i){
    if(x%i==0){
      x/=i; r*=(i-1);
      while(x%i==0){
        x/=i; r*=i;
      }
    }
  }
  if(x>1) r*=x-1;
  return r;
}
vector<int> primes;
bool notprime[N];
lld phi[N];
void euler_sieve(int n){
  for(int i=2;i<n;i++){
    if(!notprime[i]){
      primes.push_back(i); phi[i] = i-1;
    }
    for(auto j: primes){
      if(i*j >= n) break;
      notprime[i*j] = true;
      phi[i*j] = phi[i] * phi[j];
      if(i % j == 0){
        phi[i*j] = phi[i] * j;
        break;
      }
    }
  }
}

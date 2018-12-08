void Sieve(int n){
  for(int i=2;i<=n;i++){
    if(notprime[i]) continue;
    primes.push_back(i);
    for(int j=i*i;j<=n;j+=i) notprime[i]=true;
  }
}

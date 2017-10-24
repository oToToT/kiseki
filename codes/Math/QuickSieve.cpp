bool notprime[N];
vector<int> primes;

void Sieve(int n){
	// reverse true false for quicker
	for(int i=2;i<=n;i++){
		if(!notprime[i]){
			primes.push_back(i);
			for(int j=i*i;j<=n;j+=i) notprime[i]=true;
		}
	}
}

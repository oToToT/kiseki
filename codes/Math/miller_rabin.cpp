template<typename T>
inline T pow(T a,T b,T mod){// a^b mod mod
	T ret=1;
	while(b){
		if(b&1) ret=(ret*a)%mod;
		b>>=1;
		a = (a*a)%mod;
	}
	return ret%mod;
}
int sprp[3]={2,7,61};// for int range
int llsprp[7]={2,325,9375,28178,450775,9780504,1795265022};// at least unsigned long long

template<typename T>
inline bool isprime(T n,int *sprp,int num){
	if(n==2)return 1;
	if(n<2||n%2==0)return 0;
	int t=0;
	T u=n-1;
	for(;u%2==0;++t)u>>=1;
	for(int i=0;i<num;++i){
		T a=sprp[i]%n;
		if(a==0 or a==1 or a==n-1)continue;
		T x=pow(a,u,n);
		if(x==1 or x==n-1)continue;
		for(int j=0;j<t;++j){
			x=(x*x)%n;
			if(x==1)return 0;
			if(x==n-1)break;
		}
		if(x==n-1)continue;
		return 0;
	}
	return 1;
}

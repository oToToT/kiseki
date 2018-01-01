// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
// Make sure testing integer is in range [2, n−2] if
// you want to use magic.
#include <type_traits>
#include <cstdint>
typedef long long lld;

lld mul(lld a, lld b, lld m){
	// return (a*b)%m;
	lld ret = 0;
	while(b){
		if(b&1) ret = (ret+a)%m;
		a = (a+a)%m;
		b>>=1;
	}
	return ret;
}

lld qPow(lld a, lld n, lld m){
	lld ret = 1;
	while(n){
		if(n&1) ret = ret*a%m;
		n >>= 1;
		a = a*a%m;
	}
	return ret%m;
}
bool witness(lld a,lld n,lld u,int t){
	lld x=qPow(a,u,n);
	for(int i=0;i<t;i++) {
		lld nx=mul(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool miller_rabin(lld n,int s=100) {
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n == 2;
	lld u=n-1; int t=0;
	// n-1 = u*2^t
	while(!(u&1)) u>>=1, t++;
	while(s--){
		lld a=r64()%(n-1)+1;
		if(witness(a,n,u,t)) return 0;
	}
	return 1;
}
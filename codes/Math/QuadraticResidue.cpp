struct Status{
	ll x,y;
};
ll w;
Status mult(const Status& a,const Status& b,ll mod){
	Status res;
	res.x=(a.x*b.x+a.y*b.y%mod*w)%mod;
	res.y=(a.x*b.y+a.y*b.x)%mod;
	return res;
}
inline Status qpow(Status _base,ll _pow,ll _mod){
	Status res;
	res.x=1,res.y=0;
	while(_pow>0){
		if(_pow&1) res=mult(res,_base,_mod);
		_base=mult(_base,_base,_mod);
		_pow>>=1;
	}
	return res;
}
inline ll check(ll x,ll p){
	return qpow_mod(x,(p-1)>>1,p);
}
inline ll get_root(ll n,ll p){
	if(p==2) return 1;
	if(check(n,p)==p-1) return -1;
	ll a;
	while(true){
		a=rand()%p;
		w=((a*a-n)%p+p)%p;
		if(check(w,p)==p-1) break;
	}
	Status res;
	res.x=a;
	res.y=1;
	res=qpow(res,(p+1)>>1,p);
	return res.x;
}
// does not work when n is prime
// return any non-trivial factor
llu pollard_rho(llu n){
  static auto f=[](llu x,llu k,llu m){
    return add(k,mul(x,x,m),m);
  };
  if (!(n&1)) return 2;
  mt19937 rnd(120821011);
  while(true){
    llu y=2,yy=y,x=rnd()%n,t=1;
    for(llu sz=2;t==1;sz<<=1) {
      for(llu i=0;i<sz;++i){
        if(t!=1)break;
        yy=f(yy,x,n);
        t=gcd(yy>y?yy-y:y-yy,n);
      }
      y=yy;
    }
    if(t!=1&&t!=n) return t;
  }
}
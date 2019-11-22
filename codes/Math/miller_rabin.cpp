bool isprime(llu x){
  static llu magic[]={2,325,9375,28178,\
                    450775,9780504,1795265022};
  static auto witn=[](llu a,llu u,llu n,int t){
    a = mpow(a,u,n);
    if (!a)return 0;
    while(t--){
      llu a2=mul(a,a,n);
      if(a2==1 && a!=1 && a!=n-1)
        return 1;
      a = a2;
    }
    return a!=1;
  };
  if(x<2)return 0;
  if(!(x&1))return x==2;
  llu x1=x-1;int t=0;
  while(!(x1&1))x1>>=1,t++;
  for(llu m:magic)if(witn(m,x1,x,t))return 0;
  return 1;
}
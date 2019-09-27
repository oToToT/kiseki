#define mod 998244353 
const int N=1000010;
int n,k,m,f[N],h[N],a[N],b[N],ib[N];
int pw(int x,int y){
  int re=1;
  if(y<0)y+=mod-1;
  while(y){
    if(y&1)re=(ll)re*x%mod;
    y>>=1;x=(ll)x*x%mod;
  }
  return re;
}
void inc(int&x,int y){x+=y;if(x>=mod)x-=mod;}
namespace poly{
  const int G=3;
  int rev[N],L;
  void ntt(int*A,int len,int f){
    for(L=0;(1<<L)<len;++L);
    for(int i=0;i<len;++i){
      rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
      if(i<rev[i])swap(A[i],A[rev[i]]);
    }
    for(int i=1;i<len;i<<=1){
      int wn=pw(G,f*(mod-1)/(i<<1));
      for(int j=0;j<len;j+=i<<1){
        int w=1;
        for(int k=0;k<i;++k,w=(ll)w*wn%mod){
          int x=A[j+k],y=(ll)w*A[j+k+i]%mod;
          A[j+k]=(x+y)%mod,A[j+k+i]=(x-y+mod)%mod;
        }
      }
    }
    if(!~f){
      int iv=pw(len,mod-2);
      for(int i=0;i<len;++i)A[i]=(ll)A[i]*iv%mod;
    }
  }
  void cls(int*A,int l,int r){
    for(int i=l;i<r;++i)A[i]=0;}
  void cpy(int*A,int*B,int l){
    for(int i=0;i<l;++i)A[i]=B[i];}
  void inv(int*A,int*B,int l){
    if(l==1){B[0]=pw(A[0],mod-2);return;}
    static int t[N];
    int len=l<<1;
    inv(A,B,l>>1);
    cpy(t,A,l);cls(t,l,len);
    ntt(t,len,1);ntt(B,len,1);
    for(int i=0;i<len;++i)
      B[i]=(ll)B[i]*(2-(ll)t[i]*B[i]%mod+mod)%mod;
    ntt(B,len,-1);cls(B,l,len);
  }
  void pmod(int*A){
    static int t[N];
    int l=k+1,len=1;while(len<=(k<<1))len<<=1;
    cpy(t,A,(k<<1)+1);
    reverse(t,t+(k<<1)+1);
    cls(t,l,len);
    ntt(t,len,1);
    for(int i=0;i<len;++i)t[i]=(ll)t[i]*ib[i]%mod;
    ntt(t,len,-1);
    cls(t,l,len);
    reverse(t,t+l);
    ntt(t,len,1);
    for(int i=0;i<len;++i)t[i]=(ll)t[i]*b[i]%mod;
    ntt(t,len,-1);
    cls(t,l,len);
    for(int i=0;i<k;++i)A[i]=(A[i]-t[i]+mod)%mod;
    cls(A,k,len);
  }
  void pow(int*A,int n){
    if(n==1){cls(A,0,k+1);A[1]=1;return;}
    pow(A,n>>1);
    int len=1;while(len<=(k<<1))len<<=1;
    ntt(A,len,1);
    for(int i=0;i<len;++i)A[i]=(ll)A[i]*A[i]%mod;
    ntt(A,len,-1);
    pmod(A);
    if(n&1){
      for(int i=k;i;--i)A[i]=A[i-1];A[0]=0;
      pmod(A);
    }
  }
}
int main(){
  n=rd();k=rd();
  for(int i=1;i<=k;++i)f[i]=(mod+rd())%mod;
  for(int i=0;i<k;++i)h[i]=(mod+rd())%mod;
  for(int i=a[k]=b[k]=1;i<=k;++i)
    a[k-i]=b[k-i]=(mod-f[i])%mod;
  int len=1;while(len<=(k<<1))len<<=1;
  reverse(a,a+k+1);
  poly::inv(a,ib,len);
  poly::cls(ib,k+1,len);
  poly::ntt(b,len,1);
  poly::ntt(ib,len,1);
  poly::pow(a,n);
  int ans=0;
  for(int i=0;i<k;++i)inc(ans,(ll)a[i]*h[i]%mod);
  printf("%d\n",ans);
  return 0;
}
/*
   polynomial multiply:
   DFT(a, len);
   DFT(b, len);
   for(int i=0;i<len;i++) c[i] = a[i]*b[i];
   iDFT(c, len);
   yeah~ go result in c
   (len must be 2^k and >= 2*(max(a, b)))
   Hand written Cplx would be 2x faster
 */
Cplx omega[2][N];
void init_omega(int n) {
	static constexpr llf PI=acos(-1);
	const llf arg=(PI+PI)/n;
	for(int i=0;i<n;++i) 
		omega[0][i]={cos(arg*i),sin(arg*i)};
	for(int i=0;i<n;++i)
		omega[1][i]=conj(omega[0][i]);
}
void tran(Cplx arr[],int n,Cplx omg[]) {
	for(int i=0,j=0;i<n;++i){
		if(i>j)swap(arr[i],arr[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	for (int l=2;l<=n;l<<=1){
		int m=l>>1;
		for(auto p=arr;p!=arr+n;p+=l){
			for(int i=0;i<m;++i){
				Cplx t=omg[n/l*i]*p[m+i];
				p[m+i]=p[i]-t;
				p[i]+=t;
			}
		}
	}
}
void DFT(Cplx arr[],int n){
  tran(arr,n,omega[0]);
}
void iDFT(Cplx arr[],int n){
	tran(arr,n,omega[1]);
	for(int i=0;i<n;++i)arr[i]/=n;
}
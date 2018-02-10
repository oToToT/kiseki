/*
polynomial multiply:
FFT(a, N, true);
FFT(b, N, true);
for(int i=0;i<MAXN;i++) c[i] = a[i]*b[i];
FFT(c, N, false);
yeah~ go result in c
(N must be 2^k and >= len(a)+len(b))
*/
typedef long double llf;
typedef complex<llf> cplx;
const int MAXN = 262144;
const llf PI = acos((llf)-1);

cplx A[MAXN], B[MAXN], C[MAXN], omega[MAXN+1];

void init_omega(){
	const cplx I = {0, 1};
	for(int i=0;i<=MAXN;i++) omega[i] = exp(i*2*PI/MAXN*I);
}

void FFT(cplx arr[], int n, bool ori){
	// n must be 2^k
	int theta = MAXN / n;
	for(int len=n;len>=2;len>>=1){
		int tot = len>>1;
		for(int i=0;i<tot;i++){
			cplx omg = omega[ori?i*theta%MAXN:MAXN-(i*theta%MAXN)];
			for(int j=i;j<n;j+=len){
				int k = j+tot;
				cplx x = arr[j] - arr[k];
				arr[j] += arr[k];
				arr[k] = omg * x;
			}
		}
		theta = (theta * 2) % MAXN;
	}
	int i = 0;
	for(int j=1;j<n-1;j++){
		for(int k=n>>1;k>(i^=k);k>>=1);
		if(j < i) swap(arr[j], arr[i]);
	}
	if(ori) return;
	for(int i=0;i<n;i++) arr[i] /= n;
}
#include <cmath>
#include <algorithm>
typedef long double llf;
const int N = 300;
const llf EPS = 1e-8;

// make m[i][i] = x, m[i][j] = 0
// v is for solving equation
bool Gauss(llf m[N][N], llf v[N], int n){
	// right-top
	for(int i=0;i<n;i++){
		int pos = -1;
		for(int j=i;j<n;j++){
			if(fabsl(m[j][i]) > EPS){
				swap(m[i], m[j]);
				swap(v[i], v[j]);
				pos = j;
				break;
			}
		}
		if(pos == -1) return false;
		for(int j=i+1;j<n;j++){
			llf xi = m[j][i]/m[i][i];
			for(int k=0;k<n;k++){
				m[j][k] -= m[i][k]*xi;
			}
			v[j] -= v[i]*xi;
		}
	}
	// left-bottom
	for(int i=n-1;i>=0;i--){
		int pos = -1;
		for(int j=i;j>=0;j--){
			if(fabsl(m[j][i]) > EPS){
				swap(m[i], m[j]);
				swap(v[i], v[j]);
				pos = j;
				break;
			}
		}
		if(pos == -1) return false;
		for(int j=i-1;j>=0;j--){
			llf xi = m[j][i]/m[i][i];
			for(int k=n-1;k>=0;k--){
				m[j][k] -= m[i][k]*xi;
			}
			v[j] -= v[i]*xi;
		}
	}
	return true;
}
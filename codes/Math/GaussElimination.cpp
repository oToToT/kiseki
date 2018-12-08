typedef long double llf;
const int N = 300;
const llf EPS = 1e-8;

// make m[i][i] = x, m[i][j] = 0
// v is for solving equation:
// for(int i=0;i<n;i++) ans[pos[i]] = val[i]/mtx[i][pos[i]];
// for(int i=0;i<n;i++) cout << ans[i] << '\n';
bool Gauss(llf m[N][N], llf v[N], int n, int pos[N]){
  for(int i=0;i<n;i++){
    int x=-1, y=-1; llf e = 0;
    for(int j=i;j<n;j++) for(int k=i;k<n;k++){
      if(fabs(m[j][pos[k]])>e){
        e = fabs(m[j][pos[k]]);
        x = j, y = k;
      }
    }
    if(x==-1 or y==-1) return false;
    swap(m[x], m[i]);
    swap(v[x], v[i]);
    swap(pos[y], pos[i]);
    for(int j=i+1;j<n;j++){
      llf xi = m[j][pos[i]]/m[i][pos[i]];
      for(int k=0;k<n;k++) m[j][pos[k]] -= xi*m[i][pos[k]];
      v[j] -= xi*v[i];
    }
  }
  for(int i=n-1;i>=0;i--){
    for(int j=i-1;j>=0;j--){
      llf xi = m[j][pos[i]]/m[i][pos[i]];
      for(int k=0;k<n;k++) m[j][pos[k]] -= xi*m[i][pos[k]];
      v[j] -= xi*v[i];
    }
  }
  return true;
}

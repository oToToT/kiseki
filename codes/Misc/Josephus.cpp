// n people kill m for each turn
int f(int n, int m) {
  int s = 0;
  for (int i = 2; i <= n; i++)
    s = (s + m) % i;
  return s;
}
// died at kth
int kth(int n, int m, int k){
  if (m == 1) return n-1;
  for (k = k*m+m-1; k >= n; k = k-n+(k-n)/(m-1));
  return k;
}
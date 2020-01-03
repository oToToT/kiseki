int TernarySearch(int l, int r) {
  // max value @ (l, r]
  while (r - l > 1){
    int m = (l + r)>>1;
    if (f(m) > f(m + 1)) r = m;
    else l = m; 
  }
  return l+1;
}

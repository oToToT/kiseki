int TernarySearch(int l, int r) {
  // (l, r]
  while (r - l > 1){
    int mid = (l + r)>>1;
    if (f(mid) > f(mid + 1)) r = mid;
    else l = mid; 
  }
  return l+1;
}
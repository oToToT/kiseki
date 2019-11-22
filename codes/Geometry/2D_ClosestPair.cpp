struct Pt{
  llf x, y, d;
} arr[N];
inline llf dis(Pt a, Pt b){
  return hypot(a.x-b.x, a.y-b.y);
}
llf solve(){
  int cur = rand() % n;
  for(int i=0;i<n;i++) arr[i].d = dis(arr[cur], arr[i]);
  sort(arr, arr+n, [](Pt a, Pt b){return a.d < b.d;});
  llf ans = 1e50;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(arr[j].d - arr[i].d > ans) break;
      ans = min(ans, dis(arr[i], arr[j]));
    }
  }
  return ans;
}

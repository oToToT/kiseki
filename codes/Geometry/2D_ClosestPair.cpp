struct Point{
  llf x, y;
  llf dis;
} arr[N];

inline llf get_dis(Point a, Point b){
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

llf solve(){
  int cur = rand()%n;
  for(int i=0;i<n;i++) arr[i].dis = get_dis(arr[cur], arr[i]);
  sort(arr, arr+n, [](Point a, Point b){return a.dis < b.dis;});
  llf ans = 1e50;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(arr[j].dis - arr[i].dis > ans) break;
      ans = min(ans, get_dis(arr[i], arr[j]));
    }
  }
  return ans;
}
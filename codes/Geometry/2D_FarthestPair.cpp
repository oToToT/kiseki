// stk is from convex hull
n = (int)(stk.size());
int pos = 1, ans = 0; stk.push_back(stk[0]);
for(int i=0;i<n;i++) {
  while(abs(cross(stk[i+1]-stk[i],
      stk[(pos+1)%n]-stk[i])) >
      abs(cross(stk[i+1]-stk[i],
      stk[pos]-stk[i]))) pos = (pos+1)%n;
  ans = max({ans, dis(stk[i], stk[pos]),
    dis(stk[i+1], stk[pos])});
}
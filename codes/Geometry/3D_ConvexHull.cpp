// return the faces with pt indexes
int flag[MXN][MXN];
struct Point{
  ld x,y,z;
  Point operator * (const ld &b) const {
    return (Point){x*b,y*b,z*b};}
  Point operator * (const Point &b) const {
    return(Point){y*b.z-b.y*z,z*b.x-b.z*x,x*b.y-b.x*y};
  }
};
Point ver(Point a, Point b, Point c) {
  return (b - a) * (c - a);}
vector<Face> convex_hull_3D(const vector<Point> pt) {
  int n = SZ(pt), ftop = 0;
  REP(i,n) REP(j,n) flag[i][j] = 0;
  vector<Face> now;
  now.emplace_back(0,1,2);
  now.emplace_back(2,1,0);
  for (int i=3; i<n; i++){
    ftop++; vector<Face> next;
    REP(j, SZ(now)) {
      Face& f=now[j]; int ff = 0;
      ld d=(pt[i]-pt[f.a]).dot(
          ver(pt[f.a], pt[f.b], pt[f.c]));
      if (d <= 0) next.push_back(f);
      if (d > 0) ff=ftop;
      else if (d < 0) ff=-ftop;
      flag[f.a][f.b]=flag[f.b][f.c]=flag[f.c][f.a]=ff;
    }
    REP(j, SZ(now)) {
      Face& f=now[j];
      if (flag[f.a][f.b] > 0 &&
          flag[f.a][f.b] != flag[f.b][f.a])
        next.emplace_back(f.a,f.b,i);
      if (flag[f.b][f.c] > 0 &&
          flag[f.b][f.c] != flag[f.c][f.b])
        next.emplace_back(f.b,f.c,i);
      if (flag[f.c][f.a] > 0 &&
          flag[f.c][f.a] != flag[f.a][f.c])
        next.emplace_back(f.c,f.a,i);
    }
    now=next;
  }
  return now;
}

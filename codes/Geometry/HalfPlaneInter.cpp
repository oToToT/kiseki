inline int dcmp ( double x ) {
  if( fabs( x ) < eps ) return 0;
  return x > 0 ? 1 : -1;
}
struct Line {
  Point st, ed;
  double ang;
  Line(Point _s=Point(), Point _e=Point()):
   st(_s),ed(_e),ang(atan2(_e.y-_s.y,_e.x-_s.x)){}
  inline bool operator< ( const Line& rhs ) const {
    if(dcmp(ang - rhs.ang) != 0) return ang < rhs.ang;
    return dcmp( cross( st, ed, rhs.st ) ) < 0;
  }
};
// cross(pt, line.ed-line.st)>=0 <-> pt in half plane
vector< Line > lns;
deque< Line > que;
deque< Point > pt;
double HPI() {
  sort( lns.begin(), lns.end() );
  que.clear(); pt.clear();
  que.push_back( lns[ 0 ] );
  for ( int i = 1 ; i < (int)lns.size() ; i ++ ) {
    if(!dcmp(lns[i].ang - lns[i-1].ang)) continue;
    while ( pt.size() > 0 &&
     dcmp(cross(lns[i].st,lns[i].ed,pt.back()))<0){
      pt.pop_back();que.pop_back();
    }
    while ( pt.size() > 0 &&
     dcmp(cross(lns[i].st,lns[i].ed,pt.front()))<0){
      pt.pop_front(); que.pop_front();
    }
    pt.push_back(get_point( que.back(), lns[ i ] ));
    que.push_back( lns[ i ] );
  }
  while ( pt.size() > 0 && 
   dcmp(cross(que[0].st, que[0].ed, pt.back()))<0){
    que.pop_back();
    pt.pop_back();
  }
  while ( pt.size() > 0 &&
   dcmp(cross(que.back().st,que.back().ed,pt[0]))<0){
    que.pop_front();
    pt.pop_front();
  }
  pt.push_back(get_point(que.front(), que.back()));
  vector< Point > conv;
  for ( int i = 0 ; i < (int)pt.size() ; i ++ )
    conv.push_back( pt[ i ] );
  double ret = 0;
  for ( int i = 1 ; i + 1 < (int)conv.size() ; i ++ )
    ret += abs(cross(conv[0], conv[i], conv[i + 1]));
  return ret / 2.0;
}
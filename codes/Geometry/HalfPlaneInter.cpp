inline int dcmp ( double x ) {
  if( fabs( x ) < eps ) return 0;
  return x > 0 ? 1 : -1;
}
struct Line {
  Point st, ed;
  double ang;
  Line( Point _st=Point(), Point _ed=Point()):
   st(_st),ed(_ed),ang(atan2(_ed.y-_st.y,_ed.x-_st.x)){}
  inline bool operator< ( const Line& rhs ) const {
    if(dcmp( ang - rhs.ang ) != 0) return ang < rhs.ang;
    return dcmp( cross( st, ed, rhs.st ) ) < 0;
  }
};
vector< Line > lines;
deque< Line > que;
deque< Point > pt;
double HPI() {
  sort( lines.begin(), lines.end() );
  que.clear();
  pt.clear();
  que.push_back( lines[ 0 ] );
  for ( int i = 1 ; i < (int)lines.size() ; i ++ ) {
    if(!dcmp(lines[i].ang - lines[i - 1].ang)) continue;
    while ( pt.size() > 0 &&
     dcmp(cross(lines[i].st,lines[i].ed,pt.back()))<0){
      pt.pop_back();
      que.pop_back();
    }
    while ( pt.size() > 0 &&
     dcmp(cross(lines[i].st,lines[i].ed,pt.front()))<0){
      pt.pop_front();
      que.pop_front();
    }
    pt.push_back( get_point( que.back(), lines[ i ] ) );
    que.push_back( lines[ i ] );
  }
  while ( pt.size() > 0 && 
   dcmp(cross(que[0].st, que[0].ed, pt.back()))<0){
    que.pop_back();
    pt.pop_back();
  }
  while ( pt.size() > 0 &&
   dcmp(cross(que.back().st, que.back().ed, pt[0]))<0) {
    que.pop_front();
    pt.pop_front();
  }
  pt.push_back( get_point( que.front(), que.back() ) );
  vector< Point > conv;
  for ( int i = 0 ; i < (int)pt.size() ; i ++ )
    conv.push_back( pt[ i ] );
  double ret = 0;
  for ( int i = 1 ; i + 1 < (int)conv.size() ; i ++ )
    ret += abs(cross(conv[0], conv[i], conv[i + 1]));
  return ret / 2.0;
}
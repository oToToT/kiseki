template < typename T, typename Cmp_ = less< T > >
class SparseTable {
private:
  vector< vector< T > > tbl;
  vector< int > lg;
  T cv( T a, T b ) {
    return Cmp_()( a, b ) ? a : b;
  }
public:
  void init( T arr[], int n ) {
    // 0-base
    lg.resize( n + 1 );
    lg[ 0 ] = -1;
    for( int i=1 ; i<=n ; ++i ) lg[i] = lg[i>>1] + 1;
    tbl.resize( lg[n] + 1 );
    tbl[ 0 ].resize( n );
    copy( arr, arr + n, tbl[ 0 ].begin() );
    for ( int i = 1 ; i <= lg[ n ] ; ++ i ) {
      int len = 1 << ( i - 1 ), sz = 1 << i;
      tbl[ i ].resize( n - sz + 1 );
      for ( int j = 0 ; j <= n - sz ; ++ j )
        tbl[i][j] = cv(tbl[i-1][j], tbl[i-1][j+len]);
    }
  }
  T query( int l, int r ) {
    // 0-base [l, r)
    int wh = lg[ r - l ], len = 1 << wh;
    return cv( tbl[ wh ][ l ], tbl[ wh ][ r - len ] );
  }
};

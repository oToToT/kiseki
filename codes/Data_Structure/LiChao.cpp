struct Line{
  int m, k, id;
  Line() : id( -1 ) {}
  Line( int a, int b, int c )
    : m( a ), k( b ), id( c ) {}
  int at( int x ) { return m * x + k; }
};
class LiChao {
  private:
    int n; vector< Line > nodes;
    inline int lc( int x ) { return 2 * x + 1; }
    inline int rc( int x ) { return 2 * x + 2; }
    void insert( int l, int r, int id, Line ln ) {
      int m = ( l + r ) >> 1;
      if ( nodes[ id ].id == -1 ) {
        nodes[ id ] = ln;
        return;
      }
      bool atLeft = nodes[ id ].at( l ) < ln.at( l );
      if ( nodes[ id ].at( m ) < ln.at( m ) ) {
        atLeft ^= 1;
        swap( nodes[ id ], ln );
      }

      if ( r - l == 1 ) return;
      if ( atLeft ) insert( l, m, lc( id ), ln );
      else insert( m, r, rc( id ), ln );
    }
    int query( int l, int r, int id, int x ) {
      int ret = 0;
      if ( nodes[ id ].id != -1 )
        ret = nodes[ id ].at( x );
      int m = ( l + r ) >> 1;
      if ( r - l == 1 ) return ret;
      else if ( x < m )
        return max( ret, query( l, m, lc( id ), x ) );
      else
        return max( ret, query( m, r, rc( id ), x ) );
    }
  public:
    void build( int n_ ) {
      n = n_; nodes.clear();
      nodes.resize( n << 2, Line() );
    }
    void insert( Line ln ) {
      insert( 0, n, 0, ln );
    }
    int query( int x ) {
      return query( 0, n, 0, x );
    }
} lichao;

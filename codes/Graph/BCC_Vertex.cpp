class BCC{
  private:
    int n, ecnt;
    vector< vector< pair< int, int > > > G;
    vector< int > low, dfn, id;
    vector< bool > vis, ap;
    void dfs( int u, int f, int d ) {
      int child = 0;
      dfn[ u ] = low[ u ] = d; vis[ u ] = true;
      for ( auto e : G[ u ] ) if ( e.first != f ) {
        if ( vis[ e.first ] ) {
          low[ u ] = min( low[ u ], dfn[ e.first ] );
        } else {
          dfs( e.first, u, d + 1 ); child ++;
          low[ u ] = min( low[ u ], low[ e.first ] );
          if ( low[ e.first ] >= d ) ap[ u ] = true;
        }
      }
      if ( u == f and child <= 1 ) ap[ u ] = false;
    }
    void mark( int u, int idd ) {
      // really??????????
      if ( ap[ u ] ) return;
      for ( auto e : G[ u ] )
        if( id[ e.second ] != -1 ) {
          id[ e.second ] = idd;
          mark( e.first, idd );
        }
    }
  public:
    void init( int n_ ) {
      ecnt = 0, n = n_;
      G.clear(); G.resize( n );
      low.resize( n ); dfn.resize( n );
      ap.clear(); ap.resize( n );
      vis.clear(); vis.resize( n );
    }
    void add_edge( int u, int v ) {
      G[ u ].emplace_back( v, ecnt );
      G[ v ].emplace_back( u, ecnt ++ );
    }
    void solve() {
      for ( int i = 0 ; i < n ; ++ i )
        if ( not vis[ i ] ) dfs( i, i, 0 );
      id.resize( ecnt );
      fill( id.begin(), id.end(), -1 );
      ecnt = 0;
      for ( int i = 0 ; i < n ; ++ i ) 
        if ( ap[ i ] ) for ( auto e : G[ i ] )
          if( id[ e.second ] != -1 ) {
            id[ e.second ] = ecnt;
            mark( e.first, ecnt ++ );
          }
    }
    int get_id( int x ) { return id[ x ]; }
    int count() { return ecnt; }
    bool is_ap( int u ) { return ap[ u ]; }
} bcc;
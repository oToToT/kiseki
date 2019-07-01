class BCC{
  private:
    int n, ecnt;
    vector< vector< pair< int, int > > > G;
    vector< int > low, id;
    vector< bool > vis, ap;
    void dfs( int u, int f, int dfn ) {
      low[ u ] = dfn; vis[ u ] = true;
      for ( auto e : G[ u ] ) if ( e.first != f ) {
        if ( vis[ e.first ] ) {
          low[ u ] = min( low[ u ], low[ e.first ] );
        } else {
          dfs( e.first, u, dfn + 1 );
          if ( low[ e.first ] >= dfn ) ap[ u ] = true;
        }
      }
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
      G.clear();
      G.resize( n );
      low.clear();
      low.resize( n );
      ap.clear();
      ap.resize( n );
      vis.clear();
      vis.resize( n );
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
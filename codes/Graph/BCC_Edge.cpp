class BCC{
private:
  vector< int > low, dfn;
  int cnt;
  vector< bool > bridge;
  vector< vector< PII > > G;
  void dfs( int w, int f ) {
    dfn[ w ] = cnt++;
    low[ w ] = dfn[ w ];
    for ( auto [ u, t ] : G[ w ] ) {
      if ( u == f ) continue;
      if ( dfn[ u ] != 0 ) {
        low[ w ] = min( low[ w ], dfn[ u ] );
      }else{
        dfs( u, w );
        low[ w ] = min( low[ w ], low[ u ] );
        if ( low[ u ] > dfn[ w ] ) bridge[ t ] = true;
      }
    }
  }
public:
  void init( int n, int m ) {
    G.resize( n );
    fill( G.begin(), G.end(), vector< PII >() );
    bridge.clear(); bridge.resize( m );
    low.clear(); low.resize( n );
    dfn.clear(); dfn.resize( n );
    cnt = 0;
  }
  void add_edge( int u, int v ) {
    // should check for multiple edge
    G[ u ].emplace_back( v, cnt );
    G[ v ].emplace_back( u, cnt ++ );
  }
  void solve(){ cnt = 1; dfs( 0, 0 ); }
  // the id will be same as insert order, 0-base
  bool is_bridge( int x ) { return bridge[ x ]; }
} bcc;

class LowbitDecomp{
private:
  int time_, chain_, LOG_N;
  vector< vector< int > > G, fa;
  vector< int > tl, tr, chain, chain_st;
  // chain_ : number of chain
  // tl, tr[ u ] : subtree interval in the seq. of u
  // chain_st[ u ] : head of the chain contains u
  // chian[ u ] : chain id of the chain u is on
  inline int lowbit( int x ) {
    return x & ( -x );
  }
  void predfs( int u, int f ) {
    chain[ u ] = 0;
    for ( int v : G[ u ] ) {
      if ( v == f ) continue;
      predfs( v, u );
      if( lowbit( chain[ u ] ) < lowbit( chain[ v ] ) )
        chain[ u ] = chain[ v ];
    }
    if ( not chain[ u ] )
      chain[ u ] = chain_ ++;
  }
  void dfschain( int u, int f ) {
    fa[ u ][ 0 ] = f;
    for ( int i = 1 ; i < LOG_N ; ++ i )
      fa[ u ][ i ] = fa[ fa[ u ][ i - 1 ] ][ i - 1 ];
    tl[ u ] = time_++;
    if ( not chain_st[ chain[ u ] ] )
      chain_st[ chain[ u ] ] = u;
    for ( int v : G[ u ] ) 
      if ( v != f and chain[ v ] == chain[ u ] )
        dfschain( v, u );
    for ( int v : G[ u ] )
      if ( v != f and chain[ v ] != chain[ u ] )
        dfschain( v, u );
    tr[ u ] = time_;
  }
  inline bool anc( int u, int v ) {
    return tl[ u ] <= tl[ v ] \
      and tr[ v ] <= tr[ u ];
  }
public:
  inline int lca( int u, int v ) {
    if ( anc( u, v ) ) return u;
    for ( int i = LOG_N - 1 ; i >= 0 ; -- i )
      if ( not anc( fa[ u ][ i ], v ) )
        u = fa[ u ][ i ];
    return fa[ u ][ 0 ];
  }
  void init( int n ) {
    n ++;
    for ( LOG_N = 0 ; ( 1 << LOG_N ) < n ; ++ LOG_N );
    fa.clear();
    fa.resize( n, vector< int >( LOG_N ) );
    G.clear(); G.resize( n );
    tl.clear(); tl.resize( n );
    tr.clear(); tr.resize( n );
    chain.clear(); chain.resize( n );
    chain_st.clear(); chain_st.resize( n );
  }
  void add_edge( int u , int v ) {
    // 1-base
    G[ u ].push_back( v );
    G[ v ].push_back( u );
  }
  void decompose(){
    chain_ = 1;
    predfs( 1, 1 );
    time_ = 0;
    dfschain( 1, 1 );
  }
  PII get_inter( int u ) { return {tl[ u ], tr[ u ]}; }
  vector< PII > get_path( int u , int v ){
    vector< PII > res;
    int g = lca( u, v );
    while ( chain[ u ] != chain[ g ] ) {
      int s = chain_st[ chain[ u ] ];
      res.emplace_back( tl[ s ], tl[ u ] + 1 );
      u = fa[ s ][ 0 ];
    }
    res.emplace_back( tl[ g ], tl[ u ] + 1 );
    while ( chain[ v ] != chain[ g ] ) {
      int s = chain_st[ chain[ v ] ];
      res.emplace_back( tl[ s ], tl[ v ] + 1 );
      v = fa[ s ][ 0 ];
    }
    res.emplace_back( tl[ g ] + 1, tl[ v ] + 1 );
    return res;
    /* res : list of intervals from u to v
     * ( note only nodes work, not edge )
     * usage :
     * vector< PII >& path = tree.get_path( u , v )
     * for( auto [ l, r ] : path ) {
     *   0-base [ l, r )
     * }
     */
  }
} tree;
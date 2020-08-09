// contain a self loop u to u, than u won't in clique
template < size_t MAXN >
class MaxClique{
private:
  using bits = bitset< MAXN >;
  bits popped, G[ MAXN ], ans;
  size_t deg[ MAXN ], deo[ MAXN ], n;
  void sort_by_degree() {
    popped.reset();
    for ( size_t i = 0 ; i < n ; ++ i )
        deg[ i ] = G[ i ].count();
    for ( size_t i = 0 ; i < n ; ++ i ) {
        size_t mi = MAXN, id = 0;
        for ( size_t j = 0 ; j < n ; ++ j )
            if ( not popped[ j ] and deg[ j ] < mi )
                mi = deg[ id = j ];
        popped[ deo[ i ] = id ] = 1;
        for( size_t u = G[ i ]._Find_first() ;
          u < n ; u = G[ i ]._Find_next( u ) )
            -- deg[ u ];
    }
  }
  void BK( bits R, bits P, bits X ) {
    if (R.count()+P.count() <= ans.count()) return;
    if ( not P.count() and not X.count() ) {
      if ( R.count() > ans.count() ) ans = R;
      return;
    }
    /* greedily chosse max degree as pivot
    bits cur = P | X; size_t pivot = 0, sz = 0;
    for ( size_t u = cur._Find_first() ;
      u < n ; u = cur._Find_next( u ) )
        if ( deg[ u ] > sz ) sz = deg[ pivot = u ];
    cur = P & ( ~G[ pivot ] );
    */ // or simply choose first
    bits cur = P & (~G[ ( P | X )._Find_first() ]);
    for ( size_t u = cur._Find_first() ; 
      u < n ; u = cur._Find_next( u ) ) {
      if ( R[ u ] ) continue;
      R[ u ] = 1;
      BK( R, P & G[ u ], X & G[ u ] );
      R[ u ] = P[ u ] = 0, X[ u ] = 1;
    }
  }
public:
  void init( size_t n_ ) {
    n = n_;
    for ( size_t i = 0 ; i < n ; ++ i )
      G[ i ].reset();
    ans.reset();
  }
  void add_edges( int u, bits S ) { G[ u ] = S; }
  void add_edge( int u, int v ) {
    G[ u ][ v ] = G[ v ][ u ] = 1;
  }
  int solve() {
    sort_by_degree(); // or simply iota( deo... )
    for ( size_t i = 0 ; i < n ; ++ i )
      deg[ i ] = G[ i ].count();
    bits pob, nob = 0; pob.set();
    for (size_t i=n; i<MAXN; ++i) pob[i] = 0;
    for ( size_t i = 0 ; i < n ; ++ i ) {
      size_t v = deo[ i ];
      bits tmp; tmp[ v ] = 1;
      BK( tmp, pob & G[ v ], nob & G[ v ] );
      pob[ v ] = 0, nob[ v ] = 1;
    }
    return static_cast< int >( ans.count() );
  }
};
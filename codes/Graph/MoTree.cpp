int q; vector< int > G[N];
struct Que{
  int u, v, id;
} que[ N ];
int dfn[N], dfn_, block_id[N], block_, stk[N], stk_;
void dfs( int u, int f ) {
  dfn[ u ] = dfn_++; int saved_rbp = stk_;
  for ( int v : G[ u ] ) {
    if ( v == f ) continue;
    dfs( v, u );
    if ( stk_ - saved_rbp < SQRT_N ) continue;
    for ( ++ block_ ; stk_ != saved_rbp ; )
       block_id[ stk[ -- stk_ ] ] = block_;
  }
  stk[ stk_ ++ ] = u;
}
bool inPath[ N ];
void Diff( int u ) {
  if ( inPath[ u ] ^= 1 ) { /*remove this edge*/ }
  else { /*add this edge*/ }
}
void traverse( int& origin_u, int u ) {
  for ( int g = lca( origin_u, u ) ; 
    origin_u != g ; origin_u = parent_of[ origin_u ] )
      Diff( origin_u );
  for (int v = u; v != origin_u; v = parent_of[v])
    Diff( v );
  origin_u = u;
}
void solve() {
  dfs( 1, 1 );
  while ( stk_ ) block_id[ stk[ -- stk_ ] ] = block_;
  sort( que, que + q, [](const Que& x, const Que& y) {
    return tie( block_id[ x.u ], dfn[ x.v ] )
            < tie( block_id[ y.u ], dfn[ y.v ] );
  } );
  int U = 1, V = 1;
  for ( int i = 0 ; i < q ; ++ i ) {
    pass( U, que[ i ].u );
    pass( V, que[ i ].v );
    // we could get our answer of que[ i ].id
  }
}
/*
Method 2:
dfs u:
  push u
  iterate subtree
  push u
Let P = LCA(u, v), and St(u)<=St(v)
if (P == u) query[St(u), St(v)]
else query[Ed(u), St(v)], query[St(P), St(P)]
*/

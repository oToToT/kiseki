class SCC {
private:
  int n, num_;
  vector< vector< int > > G, rG;
  vector< int > ord, num;
  vector< bool > vis;
  void dfs( int u ) {
    if ( vis[ u ] ) return;
    vis[ u ] = 1;
    for ( int v : G[ u ] ) dfs( v );
    ord.push_back( u );
  }
  void rdfs( int u ) {
    if ( vis[ u ] ) return;
    num[ u ] = num_;
    vis[ u ] = 1;
    for ( int v : rG[ u ] ) rdfs(v);
  }
public:
  inline void init( int n_ ) {
    n = n_, num_ = 0;
    G.clear(); G.resize( n );
    rG.clear(); rG.resize( n );
    vis.clear(); vis.resize( n );
    num.resize( n );
  }
  inline void add_edge( int st, int ed ) {
    G[ st ].push_back( ed );
    rG[ ed ].push_back( st );
  }
  void solve() {
    fill( vis.begin(), vis.end(), 0 );
    for ( int i = 0 ; i < n ; ++ i )
      if ( not vis[ i ] ) dfs( i );
    reverse( ord.begin(), ord.end() );
    fill( vis.begin(), vis.end(), 0 );
    for ( int i : ord ) {
      if( not vis[ i ] ) {
        rdfs( i ); num_++;
      }
    }
  }
  inline int get_id( int x ) { return num[ x ]; }
  inline int count() { return num_; }
} scc;

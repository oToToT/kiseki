bool vis[ N ]; size_t la[ K ];
void dfs( int u, vector< int >& vec ) {
  while ( la[ u ] < G[ u ].size() ) {
    if( vis[ G[ u ][ la[ u ] ].second ] ) {
      ++ la[ u ];
      continue;
    }
    int v = G[ u ][ la[ u ] ].first;
    vis[ G[ u ][ la[ u ] ].second ] = true;
    ++ la[ u ]; dfs( v, vec );
    vec.push_back( v );
  }
}
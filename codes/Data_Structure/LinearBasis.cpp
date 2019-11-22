struct LinearBasis {
private:
  int n, sz;
  vector< llu > B;
  inline llu two( int x ){ return ( ( llu ) 1 ) << x; }
public:
  void init( int n_ ) {
    n = n_; B.clear(); B.resize( n ); sz = 0;
  }
  void insert( llu x ) {
    // add x into B
    for ( int i = n-1; i >= 0 ; --i ) if( two(i) & x ){
      if ( B[ i ] ) x ^= B[ i ];
      else {
        B[ i ] = x; sz++;
        for ( int j = i - 1 ; j >= 0 ; -- j )
          if( B[ j ] && ( two( j ) & B[ i ] ) )
            B[ i ] ^= B[ j ];
        for (int j = i + 1 ; j < n ; ++ j )
          if ( two( i ) & B[ j ] )
            B[ j ] ^= B[ i ];
        break;
      }
    }
  }
  inline int size() { return sz; }
  bool check( llu x ) {
    // is x in span(B) ?
    for ( int i = n-1 ; i >= 0 ; --i ) if( two(i) & x )
      if( B[ i ] ) x ^= B[ i ];
      else return false;
    return true;
  }
  llu kth_small(llu k) {
    /** 1-base would always > 0 **/
    /** should check it **/
    /* if we choose at least one element
       but size(B)(vectors in B)==N(original elements)
       then we can't get 0 */
    llu ret = 0;
    for ( int i = 0 ; i < n ; ++ i ) if( B[ i ] ) {
      if( k & 1 ) ret ^= B[ i ];
      k >>= 1;
    }
    return ret;
  }
} base;
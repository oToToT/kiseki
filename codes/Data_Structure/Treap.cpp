namespace Treap{
  #define sz( x ) ( ( x ) ? ( ( x )->size ) : 0 )
  #define sm( x ) ( ( x ) ? ( ( x )->sum ) : 0 )
  struct node{
    int size, cnt, sum;
    uint32_t pri;
    node *lc, *rc;
    node(): size( 0 ), cnt( 0 ), sum( 0 ), pri( rand() ),
            lc( nullptr ), rc( nullptr ) {}
    node( int x ): size( 1 ), cnt( x ), sum( x ), pri( rand() ),
            lc( nullptr ), rc( nullptr ) {}
    void pull() {
      sum = cnt;
      if ( lc ) sum += lc->sum;
      if ( rc ) sum += rc->sum;
      size = 1;
      if ( lc ) size += lc->size;
      if ( rc ) size += rc->size;
    }
  };
  node* merge( node* L, node* R ) {
    if ( not L or not R ) return L ? L : R;
    if ( L->pri > R->pri ) {
      L->rc = merge( L->rc, R );
      L->pull();
      return L;
    } else {
      R->lc = merge( L, R->lc );
      R->pull();
      return R;
    }
  }
  void split_by_size( node* rt, int k, node*& L, node*& R ) {
    if ( not rt ) L = R = nullptr;
    else if( sz( rt->lc ) + 1 <= k ) {
      L = rt;
      split_by_size( rt->rc, k - sz( rt->lc ) - 1, L->rc, R );
      L->pull();
    } else {
      R = rt;
      split_by_size( rt->lc, k, L, R->lc );
      R->pull();
    }
  }
  void split_by_sum( node* rt, int k, node*& L, node*& R ) {
    if ( not rt ) L = R = nullptr;
    else if( sm( rt->lc ) + rt->cnt <= k ) {
      L = rt;
      split_by_sum( rt->rc, k - sm( rt->lc ) - rt->cnt, L->rc, R );
      L->pull();
    } else {
      R = rt;
      split_by_sum( rt->lc, k, L, R->lc );
      R->pull();
    }
  }
  #undef sz
  #undef sm
}
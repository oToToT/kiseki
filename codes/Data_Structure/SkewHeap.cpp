template < typename T, typename cmp = less< T > >
class SkewHeap{
private:
  struct SkewNode{
    T x;
    SkewNode *lc, *rc;
    SkewNode( T a = 0 ) : x( a ), lc( 0 ), rc( 0 ) {}
  } *root;
  cmp CMP_;
  size_t count;
  SkewNode* Merge( SkewNode* a, SkewNode* b ) {
    if ( !a or !b ) return a ? a : b;
    if ( CMP_( a->x, b->x ) ) swap( a, b );
    a -> rc = Merge( a->rc, b );
    swap( a -> lc, a->rc );
    return a;
  }
public:
  SkewHeap(): root( 0 ), count( 0 ) {}
  size_t size() { return count; }
  bool empty() { return count == 0; }
  T top() { return root->x; }
  void clear(){ root = 0; count = 0; }
  void push ( const T& x ) {
    SkewNode* a = new SkewNode( x );
    count += 1; root = Merge( root, a );
  }
  void join( SkewHeap& a ) {
    count += a.count; a.count = 0;
    root = Merge( root, a.root );
  }
  void pop() {
    count--; root = Merge( root->lc, root->rc );
  }
  friend void swap( SkewHeap& a, SkewHeap& b ) {
    swap( a.root, b.root ); swap( a.count, b.count );
  }
};

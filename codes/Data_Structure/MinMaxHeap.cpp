template < class T, class Compare = less< T > >
class SymmetricMinMaxHeap{
private:
	Compare cmp;
	vector< T > data;
	size_t adjust_sibling( size_t i ) {
		const size_t L = i >> 1 << 1, R = i >> 1 << 1 | 1;
		if ( R < data.size() and cmp( data[ R ], data[ L ] ) ) {
			swap( data[ L ], data[ R ] );
			return i ^ 1;
		}
		return i;
	}
	size_t adjust_children( size_t i ) {
		if ( ( i << 1 ) >= data.size() )
			return i;
		if ( i & 1 ) {
			const size_t R = i << 1 | 1, L = ( i - 1 ) << 1 | 1;
			const size_t idx = ( R >= data.size() or cmp( data[ R ], data[ L ] ) ) ? L : R ;
			if ( cmp( data[ i ], data[ idx ] ) ) {
				swap( data[ idx ], data[ i ] );
				return idx;
			}
		} else {
			const size_t L = i << 1, R = ( i + 1 ) << 1;
			const size_t idx = ( R >= data.size() or cmp( data[ L ], data[ R ] ) ) ? L : R;
			if ( cmp( data[ idx ], data[ i ] ) ) {
				swap( data[ idx ], data[ i ] );
				return idx;
			}
		}
		return i;
	}
	void adjust_popped( size_t x_ ) {
		for ( size_t i = x_ ; i < data.size() ; ) {
			i = adjust_sibling( i );
			size_t j = adjust_children( i );
			if ( i == j ) break;
			i = j;
		}
	}
public:
	SymmetricMinMaxHeap() : 
		data( vector< T >( 2 ) ) {}
	bool empty() const { return data.size() == 2; }
	size_t size() const { return data.size() - 2; }
	T getMin() const {
		if ( empty() )
			throw runtime_error( "heap is empty" );
		return data[ 2 ];
	}
	T getMax() const {
		if ( empty() )
			throw runtime_error( "heap is empty" );
		return size() == 1 ? data[ 2 ] : data[ 3 ];
	}
	void push( T x ) {
		data.push_back( x );
		for ( size_t i = data.size() - 1 ; i != 1 ; ) {
			i = adjust_sibling( i );
			if ( i == 2 or i == 3 ) break;
			const size_t fL = i >> 2 << 1, fR = i >> 2 << 1 | 1;
			if ( not cmp( data[ i ], data[ fL ] ) and not cmp( data[ fR ], data[ i ] ) )
				break;
			if ( cmp( data[ i ], data[ fL ] ) ) {
				swap( data[ i ], data[ fL ] );
				i = fL;
			} else {
				swap( data[ i ], data[ fR ] );
				i = fR;
			}
		}
	}
	void popMin() {
		if ( empty() )
			throw runtime_error( "heap is empty" );
		if ( size() == 1 ) {
			data.pop_back();
			return;
		}
		data[ 2 ] = data.back();
		data.pop_back();
		adjust_popped( 2 );
	}
	void popMax() {
		if ( empty() )
			throw runtime_error( "heap is empty" );
		if ( size() <= 2 ) {
			data.pop_back();
			return;
		}
		data[ 3 ] = data.back();
		data.pop_back();
		adjust_popped( 3 );
	}
};
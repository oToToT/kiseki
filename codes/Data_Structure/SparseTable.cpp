#include <algorithm>
using std::min;
 
const int N = 1<<20;
const int LOG_N = 21;
 
class SparseTable{
	private:
		int table[N][LOG_N];
	public:
		void build(int n, int arr[]){
			// [1, n]
			for(int i=1;i<=n;i++) table[i][0] = arr[i];
			for(int j=1;(1<<j)<=n;j++){
				for(int i=1;i+(1<<j)-1<=n;i++){
					table[i][j] = min(table[i][j-1], table[i+(1<<(j-1))][j-1]);
				}
			}
		}
		int query(int l, int r){
			// 1-base [l, r]
			int k = 31-__builtin_clz(r-l+1);
			return min(table[l][k], table[r-(1<<k)+1][k]);
		}
};
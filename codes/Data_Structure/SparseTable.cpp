#include <algorithm>
using std::min;

class SparseTable{
	private:
		int table[30][N];
	public:
		void init(int n, int arr[]){
			for(int i=0;i<n;i++)
				table[0][i]=arr[i];
			for(int i=1;(1<<i)<=n;i++)
				for(int j=0;(1<<i)+j<=N;j++)
					table[i][j]=min(table[i-1][j],table[i-1][j+(1<<(i-1))]);
		}
		void query(int l, int r){
			//0-base [l, r]
			int k = 31-__builtin_clz(r-l);
			return min(minSTable[k][l], minSTable[k][r-(1<<k)+1]);
		}
};
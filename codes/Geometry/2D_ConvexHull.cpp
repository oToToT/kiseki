#include <bits/stdc++.h>
using namespace std;
typedef long long lld;
typedef pair<lld, lld> PLL;

template<typename A, typename B>
pair<A, B> operator-(const pair<A, B>& a, const pair<A, B>& b){
	return {a.first-b.first, a.second-b.second};
}

class ConvexHull_2D{
	#define x first
	#define y second
	private:
		vector<PLL> dots, down, up;
		inline lld cross(PLL a, PLL b){
			return a.x*b.y-b.x*a.y;
		}
	public:
		void insert(PLL x){dots.push_back(x);}
		void solve(){
			down.clear();up.clear();
			sort(dots.begin(), dots.end());
			for(auto i: dots){
				while(up.size()>1){
					if(cross(i-up[up.size()-2], up.back()-up[up.size()-2]) <= 0) up.pop_back();
					else break;
				}
				up.push_back(i);
			}
			reverse(dots.begin(), dots.end());
			for(auto i: dots){
				while(down.size()>1){
					if(cross(i-down[down.size()-2], down.back()-down[down.size()-2]) <= 0) down.pop_back();
					else break;
				}
				down.push_back(i);
			}
			dots.clear();
			dots.insert(dots.end(), down.begin(), down.end());
			dots.insert(dots.end(), up.begin(), up.end());
			sort(dots.begin(), dots.end());
			dots.resize(distance(dots.begin(), unique(dots.begin(), dots.end())));
			down.clear();up.clear();
		}
		vector<PLL> get(){
			return dots;
		}
		bool IsThis(PLL x){
			auto ret = lower_bound(dots.begin(), dots.end(), x);
			return *ret==x;
		}
		int count(){return dots.size();}
	#undef x
	#undef y
} cv;


int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n; cin>>n;
	for(int i=0;i<n;i++){
		lld a,b;cin>>a>>b;
		cv.insert({a, b});
	}
	cv.solve();
	cout<<cv.count()<<'\n';
	return 0;
}

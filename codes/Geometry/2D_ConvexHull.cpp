template<typename T>
class ConvexHull_2D{
	private:
		typedef Point<T> PT;
		vector<PT> dots;
		struct myhash{
			uint64_t operator()(const PT& a) const {
				uint64_t xx, yy;
				memcpy(&xx, &a.x, sizeof(a.x));
				memcpy(&yy, &a.y, sizeof(a.y));
				uint64_t ret = xx*17+yy*31;
				ret = (ret ^ (ret >> 16))*0x9E3779B1;
				ret = (ret ^ (ret >> 13))*0xC2B2AE35;
				ret = ret ^ xx;
				return (ret ^ (ret << 3)) * yy;
			}	
		};
		unordered_set<PT, myhash> in_hull;
	public:
		inline void init(){in_hull.clear();dots.clear();}
		void insert(const PT& x){dots.PB(x);}
		void solve(){
			sort(ALL(dots), [](const PT& a, const PT& b){
				return tie(a.x, a.y) < tie(b.x, b.y);
			});
			vector<PT> stk(SZ(dots)<<1);
			int top = 0;
			for(auto p: dots){
				while(top >= 2 and cross(p-stk[top-2], stk[top-1]-stk[top-2]) <= 0)
					top --;
				stk[top++] = p;
			}
			for(int i=SZ(dots)-2, t = top+1;i>=0;i--){
				while(top >= t and cross(dots[i]-stk[top-2], stk[top-1]-stk[top-2]) <= 0)
					top --;
				stk[top++] = dots[i];
			}
			stk.resize(top-1);
			swap(stk, dots);
			for(auto i: stk) in_hull.insert(i);
		}
		vector<PT> get(){return dots;}
		inline bool in_it(const PT& x){
			return in_hull.find(x)!=in_hull.end();
		}
};
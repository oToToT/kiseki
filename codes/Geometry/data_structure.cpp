namespace Geometry{
	const long double EPS = 1e-8;
	const long double PI = acos((long double)-1);
	template<typename T>
	struct Point{
		typedef long double llf;
		T x, y;
		Point(): x(0), y(0){}
		Point(T _, T __): x(_), y(__){}
		template<typename T2>
		Point(const Point<T2>& a): x(a.x), y(a.y){}
		inline llf theta() const {
			return atan2((llf)y, (llf)x);
		}
		inline llf dis() const {
			return hypot((llf)x, (llf)y);
		}
		inline llf dis(const Point& o) const {
			return hypot((llf)(x-o.x), (llf)(y-o.y));
		}
		Point operator-(const Point& o) const {
			return Point(x-o.x, y-o.y);
		}
		Point operator-=(const Point& o){
			x-=o.x, y-=o.y;
			return *this;
		}
		Point operator+(const Point& o) const {
			return Point(x+o.x, y+o.y);
		}
		Point operator+=(const Point& o){
			x+=o.x, y+=o.y;
			return *this;
		}
		Point operator*(const T& k) const {
			return Point(x*k, y*k);
		}
		Point operator*=(const T& k){
			x*=k, y*=k;
			return *this;
		}
		Point operator/(const T& k) const {
			return Point(x/k, y/k);
		}
		Point operator/=(const T& k){
			x/=k, y/=k;
			return *this;
		}
		Point operator-() const {
			return Point(-x, -y);
		}
		template<class = typename is_floating_point<T>::type>
		bool operator==(const Point& o) const {
			return fabs(x-o.x) < EPS and fabs(y-o.y) < EPS;
		}
		bool operator==(const Point& o) const {
			return x==o.x and y==o.y;
		}
		bool operator!=(const Point& o) const {
			return !(*this == o);
		}
		friend inline T cross(const Point& a, const Point& b){
			return a.x*b.y - b.x*a.y;
		}
		friend inline T dot(const Point& a, const Point &b){
			return a.x*b.x + a.y*b.y;
		}
		friend ostream& operator<<(ostream& ss, const Point& o){
			ss<<"("<<o.x<<", "<<o.y<<")";
			return ss;
		}
	};
	const Point<long double> INF_P(-1e20, 1e20);
	const Point<long double> NOT_EXIST(1e20, 1e-20);
	template<typename T>
	struct Line{
		// ax+by+c = 0
		T a, b, c;
		Line(): a(0), b(1), c(0){}
		Line(T _, T __, T ___): a(_), b(__), c(___){
			assert(fabs(a)>EPS or fabs(b)>EPS);
		}
		template<typename T2>
		Line(const Line<T2>& x): a(x.a), b(x.b), c(x.c){}
		typedef Point<long double> Pt;
		template<class = typename is_floating_point<T>::type>
		bool operator==(const Line& o) const {
			return fabs(a-o.a) < EPS and fabs(b-o.b) < EPS and fabs(c-o.b) < EPS;
		}
		bool operator==(const Line& o) const {
			return a==o.a and b==o.b and c==o.c;
		}
		bool operator!=(const Line& o) const {
			return !(*this == o);
		}
		template<class = typename is_floating_point<T>::type>
		friend inline bool on_line(const Point<T>& p, const Line& l){
			return fabs(l.a*p.x + l.b*p.y + l.c) < EPS;
		}
		friend inline bool on_line(const Point<T>& p, const Line& l){
			return l.a*p.x + l.b*p.y + l.c == 0;
		}
		template<class = typename is_floating_point<T>::type>
		friend inline bool is_parallel(const Line& x, const Line& y){
			return fabs(x.a*y.b - x.b*y.a) < EPS;
		}
		friend inline bool is_parallel(const Line& x, const Line& y){
			return x.a*y.b == x.b*y.a;
		}
		friend inline Pt get_inter(const Line& x, const Line& y){
			typedef long double llf;
			if(x==y) return INF_P;
			if(is_parallel(x, y)) return NOT_EXIST;
			llf delta = x.a*y.b - x.b*y.a;
			llf delta_x = x.b*y.c - x.c*y.b;
			llf delta_y = x.c*y.a - x.a*y.c;
			return Pt(delta_x / delta, delta_y / delta);
		}
		friend ostream& operator<<(ostream& ss, const Line& o){
			ss<<o.a<<"x+"<<o.b<<"y+"<<o.c<<"=0";
			return ss;
		}
	};
	template<typename T>
	inline Line<T> get_line(const Point<T>& a, const Point<T>& b){
		return Line<T>(a.y-b.y, b.x-a.x, (b.y-a.y)*a.x-(b.x-a.x)*a.y);
	}
	template<typename T>
	struct Segment{
		// p1.x < p2.x 
		Line<T> base;
		Point<T> p1, p2;
		Segment(): base(Line<T>()), p1(Point<T>()), p2(Point<T>()){
			assert(on_line(p1, base) and on_line(p2, base));
		}
		Segment(Line<T> _, Point<T> __, Point<T> ___): base(_), p1(__), p2(___){
			assert(on_line(p1, base) and on_line(p2, base));
		}
		template<typename T2>
		Segment(const Segment<T2>& _): base(_.base), p1(_.p1), p2(_.p2) {}
		typedef Point<long double> Pt;
		friend bool on_segment(const Point<T>& p, const Segment& l){
			if(on_line(p, l.base))
				return (l.p1.x-p.x)*(p.x-l.p2.x)>=0 and (l.p1.y-p.y)*(p.y-l.p2.y)>=0;
			return false;
		}
		friend bool have_inter(const Segment& a, const Segment& b){
			if(is_parallel(a.base, b.base)){
				return on_segment(a.p1, b) or on_segment(a.p2, b) or on_segment(b.p1, a) or on_segment(b.p2, a);
			}
			Pt inter = get_inter(a.base, b.base);
			return on_segment(inter, a) and on_segment(inter, b);
		}
		friend inline Pt get_inter(const Segment& a, const Segment& b){
			if(!have_inter(a, b)){
				return NOT_EXIST;
			}else if(is_parallel(a.base, b.base)){
				if(a.p1 == b.p1){
					if(on_segment(a.p2, b) or on_segment(b.p2, a)) return INF_P;
					else return a.p1;
				}else if(a.p1 == b.p2){
					if(on_segment(a.p2, b) or on_segment(b.p1, a)) return INF_P;
					else return a.p1;
				}else if(a.p2 == b.p1){
					if(on_segment(a.p1, b) or on_segment(b.p2, a)) return INF_P;
					else return a.p2;
				}else if(a.p2 == b.p2){
					if(on_segment(a.p1, b) or on_segment(b.p1, a)) return INF_P;
					else return a.p2;
				}
				return INF_P;
			}
			return get_inter(a.base, b.base);
		}
		friend ostream& operator<<(ostream& ss, const Segment& o){
			ss<<o.base<<", "<<o.p1<<" ~ "<<o.p2;
			return ss;
		}
	};
	template<typename T>
	inline Segment<T> get_segment(const Point<T>& a, const Point<T>& b){
		return Segment<T>(get_line(a, b), a, b);
	}
};
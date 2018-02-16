const long double EPS = 1e-8;
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
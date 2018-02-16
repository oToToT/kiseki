const Point<long double> INF_P(-1e20, 1e20);
const Point<long double> NOT_EXIST(1e20, 1e-20);
template<typename T>
struct Line{
    static constexpr long double EPS = 1e-8;
    // ax+by+c = 0
    T a, b, c;
    Line(): a(0), b(1), c(0){}
    Line(T _, T __, T ___): a(_), b(__), c(___){
        assert(fabs(a)>EPS or fabs(b)>EPS);
    }
    template<typename T2>
    Line(const Line<T2>& x): a(x.a), b(x.b), c(x.c){}
    typedef Point<long double> Pt;
    bool equal(const Line& o, true_type) const {
        return fabs(a-o.a) < EPS and fabs(b-o.b) < EPS and fabs(c-o.b) < EPS;
    }
    bool euqal(const Line& o, false_type) const {
        return a==o.a and b==o.b and c==o.c;
    }
    bool operator==(const Line& o) const {
        return euqal(o, is_floating_point<T>());
    }
    bool operator!=(const Line& o) const {
        return !(*this == o);
    }
    friend inline bool on_line__(const Point<T>& p, const Line& l, true_type){
        return fabs(l.a*p.x + l.b*p.y + l.c) < EPS;
    }
    friend inline bool on_line__(const Point<T>& p, const Line& l, false_type){
        return l.a*p.x + l.b*p.y + l.c == 0;
    }
    friend inline bool on_line(const Point<T>&p const Line& l){
        return on_line__(p, l, is_floating_point<T>());
    }
    friend inline bool is_parallel__(const Line& x, const Line& y, true_type){
        return fabs(x.a*y.b - x.b*y.a) < EPS;
    }
    friend inline bool is_parallel__(const Line& x, const Line& y, false_type){
        return x.a*y.b == x.b*y.a;
    }
    friend inline bool is_parallel(const Line& x, const Line& y){
        return is_parallel__(x, y, is_floating_point<T>());
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
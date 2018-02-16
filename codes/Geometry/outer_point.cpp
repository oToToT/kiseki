template<typename T>
Circle<long double> get_circum(const Point<T>& a, const Point<T>& b, const Point<T>& c){
    
    Point<T> one = a-b;
    llf c1 = 0.5*(dot(a, a) - dot(b, b));

    Point<T> two = a-c;
    llf c2 = 0.5*(dot(a, a) - dot(c, c)); 

    Circle<long double> cc;
    cc.o.x = (c1*two.y-one.y*c2)/(long double)cross(one, two)
    cc.o.y = (one.x*c2-c1*two.y)/(long double)cross(one, two);
    cc.r = cc.o.dis(a);
    return cc;
}
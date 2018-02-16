template<typename T>
struct Circle{
    Point<T> o;
    T r;
    vector<Point<llf>> operator&(const Circle& aa) const {
        // https://www.cnblogs.com/wangzming/p/8338142.html
        llf d=o.dis(aa.o);
        if(d > r+aa.r+EPS or d < fabs(r-aa.r)-EPS) return {};
        llf dt = (r*r - aa.r*aa.r)/d, d1 = (d+dt)/2;
        Point<llf> dir = (aa.o-o); dir /= d;
        Point<llf> pcrs = dir*d1 + o;
        dt=sqrt(max(0.0L, r*r - d1*d1)), dir=dir.rot90();
        return {pcrs + dir*dt, pcrs - dir*dt};
    }
};
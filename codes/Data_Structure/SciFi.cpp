struct SciFi{
  typedef double base_t;
  base_t x; int p;
  SciFi(){x=0;p=0;}
  SciFi(base_t k){
    p = floor(log10(k));
    x = k / pow((base_t)10, p);
  }
  SciFi(base_t a, int b){
    x=a;p=b;
  }
  SciFi operator=(base_t k){
    p = floor(log10(k));
    x = k / pow((base_t)10, p);
    return *this;
  }
  SciFi operator*(SciFi k)const{
    int nP = p+k.p;
    base_t nX = x*k.x;
    int tp = floor(log10(nX));
    return SciFi(nX/pow((base_t)10, tp), nP+tp);
  }
  SciFi operator*=(SciFi k){
    p+=k.p;
    x*=k.x;
    int tp = floor(log10(x));
    p+=tp;
    x/=pow((base_t)10, tp);
    return *this;
  }
  SciFi operator+(SciFi k)const{
    int newP = std::min(k.p, p);
    base_t x1 = x*pow((base_t)10, p-newP);
    base_t x2 = k.x*pow((base_t)10, k.p-newP);
    x1+=x2;
    int tp = floor(log10(x1));
    newP+=tp;
    x1 /= pow((base_t)10, tp);
    return SciFi(x1, newP);
  }
  SciFi operator+=(SciFi k){
    int newP = std::min(k.p, p);
    base_t x1 = x*pow((base_t)10, p-newP);
    base_t x2 = k.x*pow((base_t)10, k.p-newP);
    x1+=x2;
    int tp = floor(log10(x1));
    newP+=tp;
    x1 /= pow((base_t)10, tp);
    x=x1;p=newP;
    return *this;
  }
  bool operator<(SciFi a)const{
    if(p == a.p) return x<a.x;
    return p<a.p;
  }
  bool operator>(SciFi a)const{
    if(p == a.p) return x>a.x;
    return p>a.p;
  }
  bool operator==(SciFi a)const{
    return p==a.p and x==a.x;
  }
};

int main(){
  double a; scanf("%lf",&a);
  SciFi aa=a, x;
  x = aa*SciFi(2);
  printf("%.2lfe%c%03d\n", x.x, "+-"[x.p<0], abs(x.p));
  return 0;
}

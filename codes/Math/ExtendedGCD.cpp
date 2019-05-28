// ax+ny = 1, ax+ny == ax == 1 (mod n)
void exgcd(lld x,lld y,lld &g,lld &a,lld &b) {
  if (y == 0) g=x,a=1,b=0;
  else
    exgcd(y,x%y,g,b,a),b-=(x/y)*a;
}
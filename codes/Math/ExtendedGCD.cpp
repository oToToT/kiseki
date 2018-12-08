// By Adrien1018 (not knowing how to use.
// ax+ny = 1, ax+ny == ax == 1 (mod n)
tuple<int, int, int> extended_gcd(int a, int b) {
  if (!b) return make_tuple(a, 1, 0);
  int d, x, y;
  tie(d, x, y) = extended_gcd(b, a % b);
  return make_tuple(d, y, x - (a / b) * y);
}
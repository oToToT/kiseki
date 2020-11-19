uint64_t hsah(int u, int f) {
  uint64_t r = 127;
  for (int v : G[ u ]) if (v != f) {
    uint64_t hh = hsah(v, u);
    r=(r+(hh*hh)%1010101333)%1011820613;
  }
  return r;
}

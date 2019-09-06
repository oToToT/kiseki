const int mod = (119 << 23) + 1;
int inv_temp[400010];
void poly_inv(int *f, int *inv, int len) {
  int *inv_t = inv_temp, *g = inv;
  g[0] = get_inv(f[0]);
  for (int l = 2; l <= len; l <<= 1, swap(g, inv_t)) {
    for (int i = 0; i < l; i++) {
      inv_t[i] = f[i];
      g[i + l] = inv_t[i + l] = 0;
    }
    exec_ntt(inv_t, l << 1, 1);
    exec_ntt(g, l << 1, 1);
    for (int i = 0; i < 2 * l; i++)
      inv_t[i] = (ll)inv_t[i] * g[i] % mod;
    for (int i = 0; i < 2 * l; i++) {
      if (inv_t[i])
        inv_t[i] = mod - inv_t[i];
      inv_t[i] += 2, inv_t[i] %= mod;
    }
    for (int i = 0; i < 2 * l; i++)
      inv_t[i] = (ll)inv_t[i] * g[i] % mod;
    exec_ntt(inv_t, l << 1, -1);
    for (int i = 0; i < l; i++)
      inv_t[i + l] = 0;
  }
  for (int i = 0; i < len; i++)
    inv[i] = g[i];
}
int sqrt_temp[400010], inv_t[400010];
void poly_sqrt(int *f, int *sqrt_pol, int len) {
  int *g = sqrt_pol, *t = sqrt_temp, inv2 = get_inv(2);
  g[0] = 1;
  for (int l = 2; l <= len; l <<= 1, swap(g, t)) {
    for (int i = 0; i < l; i++)
      t[i] = f[i], t[i + l] = g[i + l] = inv_t[i] = 0;
    poly_inv(g, inv_t, l);
    for (int i = l; i < 2 * l; i++)
      inv_t[i] = 0;
    exec_ntt(g, l << 1, 1);
    exec_ntt(inv_t, l << 1, 1);
    exec_ntt(t, l << 1, 1);
    for (int i = 0; i < (l << 1); i++)
      t[i]=(ll)inv2*(g[i]+(ll)t[i]*inv_t[i] % mod)%mod;
    exec_ntt(t, l << 1, -1);
    for (int i = 0; i < l; i++)
      t[i + l] = 0;
  }
  for (int i = 0; i < len; i++)
    sqrt_pol[i] = g[i];
}
int c[400010], inv[400010], sqrt_pol[400010];
int main(){
  int n, m, x;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &x);
    if (x <= m)
      c[x] = mod - 4;
  }
  c[0]++, c[0] %= mod;
  int len = 1;
  while (len <= m)len <<= 1;
  poly_sqrt(c, sqrt_pol, len);
  sqrt_pol[0]++, sqrt_pol[0] %= mod;
  poly_inv(sqrt_pol, inv, len);
  for (int i = 1; i <= m; i++)
    printf("%d\n", (inv[i] + inv[i]) % mod);
  puts("");
  return 0;
}
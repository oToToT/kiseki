llf solve(vector<P> v) {
  shuffle(v.begin(), v.end(), mt19937());
  unordered_map<lld, unordered_map<lld,
    unordered_map<lld, int>>> m;
  llf d = dis(v[0], v[1]);
  auto Idx = [&d] (llf x) -> lld {
    return round(x * 2 / d) + 0.1; };
  auto rebuild_m = [&m, &v, &Idx](int k) {
    m.clear();
    for (int i = 0; i < k; ++i)
      m[Idx(v[i].x)][Idx(v[i].y)]
        [Idx(v[i].z)] = i;
  }; rebuild_m(2);
  for (size_t i = 2; i < v.size(); ++i) {
    const lld kx = Idx(v[i].x), ky = Idx(v[i].y),
          kz = Idx(v[i].z); bool found = false;
    for (int dx = -2; dx <= 2; ++dx) {
      const lld nx = dx + kx;
      if (m.find(nx) == m.end()) continue;
      auto& mm = m[nx];
      for (int dy = -2; dy <= 2; ++dy) {
        const lld ny = dy + ky;
        if (mm.find(ny) == mm.end()) continue;
        auto& mmm = mm[ny];
        for (int dz = -2; dz <= 2; ++dz) {
          const lld nz = dz + kz;
          if (mmm.find(nz) == mmm.end()) continue;
          const int p = mmm[nz];
          if (dis(v[p], v[i]) < d) {
            d = dis(v[p], v[i]);
            found = true;
          }
        }
      }
    }
    if (found) rebuild_m(i + 1);
    else m[kx][ky][kz] = i;
  }
  return d;
}

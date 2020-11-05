llf solve(vector<P> v) {
  shuffle(v.begin(), v.end(), mt19937());
  // maybe could replace vector<P> with only P
  unordered_map<lld, unordered_map<lld,
    unordered_map<lld, vector<P>>>> m;
  llf d = dis(v[0], v[1]);
  auto Idx = [&d] (lld x) -> lld {
    return round(x * 2 / d) + 0.1; };
  auto rebuild_m = [&m, &v, &Idx](int k) {
    m.clear();
    for (int i = 0; i < k; ++i)
      m[Idx(v[i].x)][Idx(v[i].y)]
        [Idx(v[i].z)].push_back(v[i]);
  };
  rebuild_m(2);
  for (size_t i = 2; i < v.size(); ++i) {
    const lld kx = Idx(v[i].x), ky = Idx(v[i].y),
          kz = Idx(v[i].z); bool found = false;
    for (int x = -2; x <= 2; ++x) {
      const lld nx = x + kx;
      if (m.find(nx) == m.end()) continue;
      auto& mm = m[nx];
      for (int y = -2; y <= 2; ++y) {
        const lld ny = y + ky;
        if (mm.find(ny) == mm.end()) continue;
        auto& mmm = mm[ny];
        for (int z = -2; z <= 2; ++z) {
          const lld nz = z + kz;
          if (mmm.find(nz) == mmm.end()) continue;
          for (auto p: mmm[nz]) {
            if (dis(p, v[i]) < d) {
              d = dis(p, v[i]);
              found = true;
            }
          }
        }
      }
    }
    if (found) rebuild_m(i + 1);
    else m[kx][ky][kz].push_back(v[i]);
  }
  return d;
}

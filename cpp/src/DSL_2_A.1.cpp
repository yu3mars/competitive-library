#include "../include/structure/starry_sky_tree.cpp"
#include "../include/template/typedef.hpp"

int main() {
  int n, q, com, x, y;
  scanf("%d%d", &n, &q);
  StarrySkyTree<ll> seg(n);
  seg.update(0, n, INT_MAX);
  while (q--) {
    scanf("%d%d%d", &com, &x, &y);
    if (com)
      printf("%lld\n", seg.query(x, y + 1));
    else {
      int val = seg.query(x, x + 1);
      seg.update(x, x + 1, y - val);
    }
  }
  return 0;
}

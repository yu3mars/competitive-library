#include "../include/structure/monoid.hpp"
#include "../include/structure/segment_tree_lazy.cpp"
#include "../include/structure/semi_group.hpp"

struct RangeUpdateRMQ {
  using Monoid = RMQ<long long>;
  using Update = LeftHandSide<long long>;
  using value_type = typename Monoid::value_type;
  using update_type = typename Update::value_type;
  static value_type evaluate(const update_type &update, const value_type &) {
    return update;
  }
};

int main() {
  int n, q, com, s, t, x;
  scanf("%d%d", &n, &q);
  SegmentTreeLazy<RangeUpdateRMQ> seg(n, INT_MAX);
  while (q--) {
    scanf("%d", &com);
    if (com) {
      scanf("%d%d", &s, &t);
      printf("%lld\n", seg.query(s, t + 1));
    }
    else {
      scanf("%d%d%d", &s, &t, &x);
      seg.update(s, t + 1, x);
    }
  }
  return 0;
}

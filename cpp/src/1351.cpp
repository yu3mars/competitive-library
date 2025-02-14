#include "../include/structure/starry_sky_tree.cpp"
#include "../include/template/range.hpp"

using namespace std;

char s[301000];

int main() {
  int N, Q, p;
  scanf("%d%d%s", &N, &Q, s);
  StarrySkyTree<int> seg(N);
  set<int> right;
  for (int i : range(N)) {
    if (s[i] == '(') {
      seg.update(i, N, 1);
    }
    else {
      seg.update(i, N, -1);
      right.insert(i);
    }
  }
  while (Q--) {
    scanf("%d", &p);
    --p;
    if (right.find(p) == end(right)) {
      right.insert(p);
      int l = *begin(right);
      seg.update(l, p, 2);
      right.erase(l);
      cout << l + 1 << endl;
    }
    else {
      right.erase(p);
      seg.update(p, N, 2);
      int lb = -1, ub = N;
      while (ub - lb > 1) {
        const int mid = (lb + ub) / 2;
        if (seg.query(mid, N) >= 2)
          ub = mid;
        else
          lb = mid;
      }
      seg.update(ub, N, -2);
      right.insert(ub);
      cout << ub + 1 << endl;
    }
  }
  return 0;
}

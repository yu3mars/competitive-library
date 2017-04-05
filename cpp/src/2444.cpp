#include "../include/rolling_hash.cpp"

char str[512000];
char op[8];

int main() {
  int n, m;
  scanf("%d%d%s", &n, &m, str);
  RollingHash rh(string(str, n));
  int l = 0, r = 1;
  vector<pair<ll,ll>> vec;
  while (m--) {
    scanf("%s", op);
    *(op[0] == 'L' ? &l : &r) += (op[1] == '+' ? 1 : -1);
    vec.push_back(rh.query(l, r));
  }
  sort(begin(vec), end(vec));
  vec.erase(unique(begin(vec), end(vec)), end(vec));
  printf("%d\n", int(vec.size()));
  return 0;
}

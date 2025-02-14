#include "../include/structure/skew_heap.cpp"
#include "../include/structure/unionfind.cpp"
#include "../include/template/typedef.hpp"

// #define BEGIN_STACK_EXTEND(size) void * stack_extend_memory_ =
// malloc(size);void * stack_extend_origin_memory_;char *
// stack_extend_dummy_memory_ = (char*)alloca((1+(int)(((long
// long)stack_extend_memory_)&127))*16);*stack_extend_dummy_memory_ = 0;asm
// volatile("mov %%rsp, %%rbx\nmov %%rax,
// %%rsp":"=b"(stack_extend_origin_memory_):"a"((char*)stack_extend_memory_+(size)-1024));
// #define END_STACK_EXTEND asm volatile("mov %%rax,
// %%rsp"::"a"(stack_extend_origin_memory_));free(stack_extend_memory_);

using namespace std;

using Heap = skew_heap<tuple<int, int, int>> *;

vector<pair<int, int>> g[128000];
vector<tuple<int, int, int>> t[128000];

int res[256000];
bool visited[128000];

void merge(set<int> &s1, set<int> &s2) {
  if (s1.size() < s2.size()) s1.swap(s2);
  for (int i : s2) s1.insert(i);
}

pair<set<int>, Heap> dfs(int v) {
  visited[v] = true;
  set<int> se;
  Heap heap = nullptr;
  for (auto e : t[v]) {
    int w, c, id;
    tie(w, c, id) = e;
    if (visited[w]) continue;
    set<int> s;
    Heap h = nullptr;
    tie(s, h) = dfs(w);
    int cost = 11e8, from, to;
    bool ok = false;
    while (h) {
      tie(cost, from, to) = h->val;
      if (s.find(from) == end(s) || s.find(to) == end(s)) {
        ok = true;
        break;
      }
      h = pop(h);
    }
    res[id] = (ok ? cost - c : -1);
    heap = meld(heap, h);
    merge(se, s);
  }
  se.insert(v);
  for (auto e : g[v]) {
    int w, c;
    tie(w, c) = e;
    heap = push(heap, make_tuple(c, v, w));
  }
  return make_pair(move(se), heap);
}

int main() {
  // BEGIN_STACK_EXTEND(128*1024*1024);
  int n, m;
  cin >> n >> m;
  UnionFind uf(n);
  ll sum = 0;
  vector<tuple<int, int, int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    edges.emplace_back(c, u - 1, v - 1, i);
  }
  sort(begin(edges), end(edges));
  int cnt = 0;
  for (auto e : edges) {
    int c, u, v, i;
    tie(c, u, v, i) = e;
    if (uf.unite(u, v)) {
      sum += c;
      t[u].emplace_back(v, c, i);
      t[v].emplace_back(u, c, i);
      ++cnt;
    }
    else {
      g[u].emplace_back(v, c);
      g[v].emplace_back(u, c);
    }
  }
  dfs(0);
  for (int i = 0; i < m; ++i) {
    cout << (res[i] == -1 || cnt < n - 1 ? -1 : res[i] + sum) << endl;
  }
  // END_STACK_EXTEND;
  return 0;
}

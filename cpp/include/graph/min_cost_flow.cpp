#pragma once

#include "../template/const_value.hpp"
#include "definition.hpp"

template <typename edge_t, typename cap_type = typename edge_t::capacity_type,
          typename cost_type = typename edge_t::cost_type>
cost_type min_cost_flow(graph_t<edge_t> &g, int s, int t, cap_type f,
                        bool init = true) {
  static_assert(std::is_integral<cap_type>::value,
                "capacity must be of integer type");
  static_assert(!std::is_floating_point<cap_type>::value,
                "use float_tolerance<float_type, ...> instead of float_type");
  const int V = g.size();
  static std::vector<cost_type> h(V, zero<cost_type>()),
    dist(V, zero<cost_type>());
  static std::vector<int> prevv(V), preve(V);
  if (init) {
    std::fill(begin(h), end(h), zero<cost_type>());
    std::fill(begin(dist), end(dist), zero<cost_type>());
    std::fill(begin(prevv), end(prevv), 0);
    std::fill(begin(preve), end(preve), 0);
  }
  using P = std::pair<cost_type, int>;
  cost_type res = zero<cost_type>();
  while (f > zero<cap_type>()) {
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    std::fill(begin(dist), end(dist), inf<cost_type>());
    dist[s] = zero<cost_type>();
    que.push(P(zero<cost_type>(), s));
    while (!que.empty()) {
      P p = que.top();
      que.pop();
      int v = p.second;
      if (dist[v] < p.first) continue;
      for (int i = 0; i < (int)g[v].size(); ++i) {
        const auto &e = g[v][i];
        if (e.cap <= zero<cap_type>()) continue;
        if (dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
          dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
          prevv[e.to] = v;
          preve[e.to] = i;
          que.push(P(dist[e.to], e.to));
        }
      }
    }
    if (dist[t] == inf<cost_type>()) return -1;
    for (int i = 0; i < V; ++i) {
      h[i] += dist[i];
    }
    cap_type d = f;
    for (int v = t; v != s; v = prevv[v]) {
      d = std::min(d, g[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for (int v = t; v != s; v = prevv[v]) {
      auto &e = g[prevv[v]][preve[v]];
      e.cap -= d;
      g[v][e.rev].cap += d;
    }
  }
  return res;
}

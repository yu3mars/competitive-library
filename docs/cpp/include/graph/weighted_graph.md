{% include mathjax.html %}

## add_edge

{% highlight cpp %}
void add_edge(WeightedGraph< Cost > &g, int from, int to, Cost cost);
{% endhighlight %}

## Member functions

### [1] (constructor)
{% highlight cpp %}
WeightedEdge(int, int t, cost_type c);
{% endhighlight %}


---------------------------------------

## Implementation

- [GitHub]({{ site.github.repository_url }}/blob/master/cpp/include/graph/weighted_graph.hpp)

{% highlight cpp %}
#include "definition.hpp"

template <typename Cost> class WeightedEdge {
public:
  using cost_type = Cost;
  int to;
  cost_type cost;
  WeightedEdge(int, int t, cost_type c) : to(t), cost(c) { ; }
};

template <typename Cost> using WeightedGraph = graph_t<WeightedEdge<Cost>>;

template <typename Cost>
void add_edge(WeightedGraph<Cost> &g, int from, int to, Cost cost) {
  g[from].emplace_back(from, to, cost);
}
{% endhighlight %}

### Includes

- [definition.hpp](definition)

[Back](../..)

{% include mathjax.html %}

## LUPDecomposition

{% highlight cpp %}
LUP<T> LUPDecomposition(Matrix< T > A);
{% endhighlight %}

## LUPBackSubstitution

{% highlight cpp %}
Vec<T> LUPBackSubstitution(const LUP< T > &lup, Vec< T > a);
{% endhighlight %}

## Implementation

- [GitHub]({{ site.github.repository_url }}/blob/master/cpp/include/math/lup_decomposition.cpp)

{% highlight cpp %}
#include "matrix.cpp"

template <typename T> using LUP = std::pair<Matrix<T>, std::vector<int>>;

template <typename T> LUP<T> LUPDecomposition(Matrix<T> A) {
  assert(A.Y() == A.X());
  int n = A.Y();
  std::vector<int> perm(n);
  iota(begin(perm), end(perm), 0);
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    for (int j = i + 1; j < n; ++j) {
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    }
    std::swap(A[pivot], A[i]);
    std::swap(perm[pivot], perm[i]);
    for (int j = i + 1; j < n; ++j) {
      A[j][i] /= A[i][i];
      for (int k = i + 1; k < n; ++k) {
        A[j][k] -= A[i][k] * A[j][i];
      }
    }
  }
  return std::make_pair(A, perm);
}

template <typename T> Vec<T> LUPBackSubstitution(const LUP<T> &lup, Vec<T> a) {
  const Matrix<T> &LU = lup.first;
  const std::vector<int> &perm = lup.second;
  const int n = LU.Y();
  Vec<T> tmp(n);
  for (int i = 0; i < n; ++i) {
    tmp[i] = a[perm[i]];
  }
  std::swap(tmp, a);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      a[i] -= a[j] * LU[i][j];
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      a[i] -= a[j] * LU[i][j];
    }
    a[i] /= LU[i][i];
  }
  return a;
}
{% endhighlight %}

### Includes

- [matrix.cpp](matrix)

[Back](../..)

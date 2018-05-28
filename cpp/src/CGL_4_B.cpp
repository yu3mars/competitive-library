#include "../include/geometry/convex.cpp"

using namespace std;

using P = Point<float11>;

int main() {
  cout << setprecision(12) << fixed;
  int n;
  cin >> n;
  std::vector<P> ps;
  for (int i = 0; i < n; ++i) {
    P p;
    cin >> p;
    ps.push_back(p);
  }
  cout << max_distance(ps) << endl;
}

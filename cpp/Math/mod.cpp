const int mod = 1000000007;

struct Mod {
  int n;
  Mod () : n(0) {;}
  Mod (int n) : n(n) { if (n >= mod) n %= mod; }
  operator int() { return n; }
  bool operator==(const Mod &a) { return n == a.n; }
  Mod operator+=(const Mod &a) { n += a.n; if (n >= mod) n -= mod; return *this; }
  Mod operator-=(const Mod &a) { n -= a.n; if (n < 0) n += mod; return *this; }
  Mod operator*=(const Mod &a) { n = ((long long)n * a.n) % mod; return *this; }
};

int inv(int a, int p) { return (a == 1 ? 1 : (1 - p * inv(p%a, a)) / a + p); }
Mod operator+(Mod a, const Mod &b) { return a += b; }
Mod operator-(Mod a, const Mod &b) { return a -= b; }
Mod operator*(Mod a, const Mod &b) { return a *= b; }
Mod operator/(Mod a, Mod b) { return a * Mod(inv(b, mod)); }
Mod operator^(const Mod &a, int n) {
  if (n == 0) return Mod(1);
  Mod res = (a * a) ^ (n / 2);
  if (n % 2) res = res * a;
  return res;
}

#define MAX_N 1024000

Mod fact[MAX_N], factinv[MAX_N];
void init() {
  fact[0] = Mod(1); factinv[0] = 1;
  REP(i,MAX_N-1) {
    fact[i+1] = fact[i] * Mod(i+1);
    factinv[i+1] = factinv[i] / Mod(i+1);
  }
}
Mod comb(int a, int b) {
  return fact[a] * factinv[b] * factinv[a-b];
}

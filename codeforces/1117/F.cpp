#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

using pi = std::pair<int32_t, int32_t>;
using pl = std::pair<int64_t, int64_t>;
using vi = std::vector<int32_t>;
using vl = std::vector<int64_t>;
using vpi = std::vector<pi>;
using vpl = std::vector<pl>;
using str = std::string;
using db = double;
using ld = long double;

// templates
#define tcT template <class T
#define tcTU tcT, class U
#define tcTUU tcT, class... U

// pairs
#define mp make_pair
#define f first
#define s second

// loops
#define FOR(i, a, b) for (int32_t i = (a); i < (b); i++)
#define ROF(i, a, b) for (int32_t i = (b) - 1; i >= (a); i--)
#define trav(a, x) for (auto &(a) : (x))

// vectors
#define sz(a) (int32_t)(a).size()
#define all(x) (x).begin(), (x).end()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

const int32_t MOD = 998244353;
const int32_t MAXN = 1e6 + 5;
const int64_t INF = 1e18;
const double PI = acos(-1);
const int32_t tSZ = (1 << 21);
const int32_t dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}; // for grid problems
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

constexpr int pcnt(int x) { return __builtin_popcount(x); } // number of bits

namespace MO {
int32_t add(int64_t x, int64_t y) {
  return ((x % MOD) + (y % MOD) + MOD) % MOD;
}
int32_t mul(int64_t x, int64_t y) { return ((x % MOD) * (y % MOD)) % MOD; }

int32_t pow(int32_t x, int32_t y) {
  int32_t res = 1;

  while (y) {
    if (y & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}

int32_t inverse(int32_t x) { return pow(x, MOD - 2); }
}; // namespace MO

// input
tcT > void re(complex<T> &c);
tcTU > void re(pair<T, U> &p);
tcT > void re(vector<T> &v);

tcT > void re(T &x) { cin >> x; }
void re(db &d) {
  str t;
  cin >> t;
  d = stod(t);
}
void re(ld &d) {
  str t;
  cin >> t;
  d = stold(t);
}
tcTUU > void re(T &x, U &...u) {
  re(x);
  re(u...);
}

tcT > void re(complex<T> &x) {
  T a, b;
  re(a, b);
  x = {a, b};
}
tcTU > void re(pair<T, U> &p) { re(p.f, p.s); }
tcT > void re(vector<T> &v) { trav(x, v) re(x); }

// to string
#define ts to_string
str ts(char c) { return str(1, c); }
str ts(const char *s) { return (str)s; }
str ts(str s) { return s; }
str ts(bool x) { return x ? "YES" : "NO"; }

// output
tcT > void pr(const T &x) { cout << ts(x); }
tcTUU > void pr(const T &t, const U &...u) {
  pr(t);
  pr(u...);
}
void ps() { pr("\n"); }
tcTUU > void ps(const T &t, const U &...u) {
  pr(t);
  if (sizeof...(u)) {
    pr(" ");
  }
  ps(u...);
}

void setIn(const str &f_name) { freopen(f_name.c_str(), "r", stdin); }
void setOut(const str &f_name) { freopen(f_name.c_str(), "w", stdout); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(false); }
void setIO(str st = "") {
  unsyncIO();
  if (sz(st)) {
    setIn(st + ".in"), setOut(st + ".out");
  }
}

// DEBUG
void DBG() { cerr << "]\n"; }
tcTUU > void DBG(const T &t, const U &...u) {
  cerr << ts(t);
  if (sizeof...(u)) {
    cerr << ", ";
  }
  DBG(u...);
}

int32_t n, x, q;
int32_t a[MAXN], b[MAXN];
using node_type = std::array<std::array<int64_t, 5>, 5>;

node_type tree[tSZ];

struct segm_tree {
  int32_t N;
  segm_tree(int32_t n) {
    N = 1;
    while (N < n) {
      N <<= 1;
    }
    N <<= 1;

    FOR(i, 0, N) {
      FOR(j, 0, 5) {
        FOR(z, 0, 5) { tree[i][j][z] = INF; }
      }
    }
  }

  // need to keep only X nodes from the beginning and end
  inline node_type merge_nodes(const node_type &l, const node_type &r) {
    if (l[0][0] == -1) {
      return r;
    } else if (r[0][0] == -1) {
      return l;
    }

    node_type res;
    int32_t d = x;

    while (d > 0 && l[d - 1][0] == INF) {
      d--;
    }
    FOR(i, 0, x - d) {
      FOR(j, 0, x) { res[d + i][j] = r[i][j]; }
    }

    for (int32_t left_left{0}; left_left < d; left_left++) {
      for (int32_t right_right{0}; right_right < x; right_right++) {
        res[left_left][right_right] = INF;
        for (int32_t middle{0}; middle < x; middle++) {
          if (r[middle][right_right] == INF) {
            break;
          }
          res[left_left][right_right] =
              min(res[left_left][right_right],
                  l[left_left][middle] + r[middle][right_right]);
        }
      }
    }
    return res;
  }

  inline void update_node(int32_t k, int32_t len, int32_t pen) {
    FOR(i, 0, min(len, x)) {
      FOR(j, 0, x) {
        int64_t len_to_jump = len + j - i;

        tree[k][i][j] = ((len_to_jump + x - 1) / x) * pen;

        tree[k][i][j] -= pen;
      }
    }
  }

  void update(int32_t k, int32_t i, int32_t new_len, int32_t new_pen) {
    int32_t l = 1, r = N / 2;

    while (true) {
      if (l == r) {
        update_node(k, new_len, new_pen);

        k >>= 1;

        do {
          tree[k] = merge_nodes(tree[k << 1], tree[k << 1 | 1]);
          k >>= 1;
        } while (k != 1);

        return;
      }
      int32_t middle = (l + r) >> 1;

      if (i > middle) {
        l = middle + 1;
        k <<= 1;
        k |= 1;
      } else {
        r = middle;
        k <<= 1;
      }
    }
  }

  std::array<tuple<int32_t, int32_t, int32_t>, 22> ss;

  void query(int32_t i, int32_t j, node_type &fin) {
    int32_t kk = 0;
    // stack<tuple<int32_t, int32_t, int32_t>> ss;

    ss[kk++] = {1, 1, N / 2};

    while (kk > 0) {
      auto x = ss[kk - 1];
      kk--;

      int32_t k = get<0>(x);
      int32_t l = get<1>(x);
      int32_t r = get<2>(x);

      if (r < i || l > j) {
        continue;
      }

      if (r <= j && l >= i) {
        fin = merge_nodes(fin, tree[k]);
        continue;
      }

      int32_t middle = (l + r) >> 1;

      ss[kk++] = {k << 1 | 1, middle + 1, r};
      ss[kk++] = {k << 1, l, middle};
    }
  }

  void build_tree() {
    for (int32_t i{1}; i <= N / 2; i++) {
      if (i <= n) {
        update_node(i + N / 2 - 1, a[i], b[i]);
      } else {
        tree[i + N / 2 - 1][0][0] = -1;
      }
    }
    for (int32_t i{N / 2 - 1}; i >= 1; i--) {
      tree[i] = merge_nodes(tree[i << 1], tree[i << 1 | 1]);
    }
  }
};

void solve() {
  segm_tree sgm_tree(n);
  sgm_tree.build_tree();

  char t;
  int32_t v, w;
  node_type res;

  FOR(i, 0, q) {
    re(t, v, w);

    if (t == '1') {
      a[v] = w;

      sgm_tree.update(1, v, a[v], b[v]);
    } else if (t == '2') {
      b[v] = w;

      sgm_tree.update(1, v, a[v], b[v]);
    } else {
      res[0][0] = -1;
      if (v == w) {
        int64_t ans = int64_t(((a[v] - 1) + x - 1) / x) * b[v];
        ps(ans);
        continue;
      }
      int64_t ans = INT64_MAX;

      sgm_tree.query(v, w - 1, res);

      for (int32_t j{0}; j < x; j++) {
        if (res[0][j] != INF) {
          int64_t to_add = int64_t(((a[w] - j - 1) + x - 1) / x) * b[w];
          ans = min(ans, res[0][j] + to_add);
        }
      }

      ps(ans);
    }
  }
}

int main() {
  setIO();

  re(n, q, x);

  FOR(i, 1, n + 1) { re(a[i]); }
  FOR(i, 1, n + 1) { re(b[i]); }

  solve();

  return 0;
}

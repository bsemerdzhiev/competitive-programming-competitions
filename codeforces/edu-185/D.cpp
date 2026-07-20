#include <bits/stdc++.h>

using namespace std;

using pi = std::pair<int32_t, int32_t>;
using vi = std::vector<int32_t>;
using vpi = std::vector<pi>;
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
const int32_t MAXN = 2e5 + 5;
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

int32_t n, q;
str a;

void solve() {
  int32_t needed = 0;

  a = "#" + a + "#";
  str b = a;

  FOR(i, 1, n + 1) {
    if (b[i] == '?') {
      needed++;
      b[i] = 'I';
    }
  }
  // ps("AA");
  // DBG("AA");
  int32_t cur_ans = 0;
  FOR(i, 1, n + 1) {
    if (b[i] == 'X') {
      cur_ans += 10;
    } else if (b[i] == 'V') {
      cur_ans += 5;
    } else {
      if (b[i + 1] != 'I' && i + 1 <= n) {
        cur_ans -= 1;
      } else {
        cur_ans += 1;
      }
    }
  }
  // ps("AA");
  set<int32_t> ss[4];
  vi cur_color(n + 2, 0);
  cur_color[0] = cur_color[n + 1] = -1;

  auto calc_type = [&](int32_t i) {
    if (b[i - 1] == 'I' && (b[i + 1] != 'V' && b[i + 1] != 'X')) {
      return 0;
    } else if (b[i - 1] != 'I' && (b[i + 1] == 'V' || b[i + 1] == 'X')) {
      return 2;
    } else {
      return 1;
    }
  };

  FOR(i, 1, n + 1) {
    if (a[i] == '?') {
      int32_t cur_type = calc_type(i);
      ss[cur_type].ins(i);
      cur_color[i] = cur_type;
    } else {
      cur_color[i] = -1;
    }
  }
  vi ans_for(n + 1, 0);

  ans_for[needed] = cur_ans;

  for (int32_t z = needed - 1; z >= 0; z--) {
    // remove one
    FOR(g, 0, 4) {
      if (sz(ss[g])) {
        int32_t cur_ind = *ss[g].begin();
        ss[g].erase(cur_ind);

        if (g == 0) {
          cur_ans += 2;
        } else if (g == 1) {
          cur_ans += 4;
        } else if (g == 2) {
          cur_ans += 6;
        }
        cur_color[cur_ind] = -1;
        b[cur_ind] = 'V';

        // DBG("AAA");
        if (cur_color[cur_ind - 1] != -1 && cur_color[cur_ind - 1] <= 2) {
          ss[cur_color[cur_ind - 1]].erase(cur_ind - 1);

          int32_t cur_type = calc_type(cur_ind - 1);
          ss[cur_type].ins(cur_ind - 1);
          cur_color[cur_ind - 1] = cur_type;
        }
        if (cur_color[cur_ind + 1] != -1 && cur_color[cur_ind + 1] <= 2) {
          ss[cur_color[cur_ind + 1]].erase(cur_ind + 1);

          int32_t cur_type = calc_type(cur_ind + 1);
          ss[cur_type].ins(cur_ind + 1);
          cur_color[cur_ind + 1] = cur_type;
        }
        break;
      }
    }
    ans_for[z] = cur_ans;
    // ps(z, cur_ans);
  }
  // ps("AAAA");
  // cout.flush();
  // DBG("AA");
  int32_t v[3];
  FOR(i, 0, q) {
    re(v[0], v[1], v[2]);

    int32_t pp = needed;
    for (int32_t j = 2; j >= 0; j--) {
      int32_t to_use = min(pp, v[j]);
      pp -= to_use;

      v[j] = to_use;
    }

    int32_t new_ans = ans_for[v[2]] + (needed - v[2] - v[1]) * 5;
    ps(new_ans);
  }
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n, q);
    re(a);

    solve();
  }

  return 0;
}

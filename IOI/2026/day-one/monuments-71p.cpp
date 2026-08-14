#include <bits/stdc++.h>
#include <cstdint>
#include <unordered_map>

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

int32_t N, M;

int64_t solve_lines(const vpi &LA, const vpi &LB) {
  N /= 2;

  vl T(N + 1, 1e15);
  int32_t lock_cnt[2] = {0, 0};

  T[0] = 0;
  map<int32_t, int32_t> mm;
  mm[N] = 0;

  vi reserved[2][2];
  FOR(i, 0, 2) {
    FOR(j, 0, 2) { reserved[i][j].resize(N + 1); }
  }

  for (int32_t i{1}; i <= N; i++) {
    if (LA[i - 1].s == 0 && LB[i - 1].s == 0) {
      T[i] = min(T[i], T[i - 1] + abs(LA[i - 1].first - LB[i - 1].first));
    }
    lock_cnt[0] += LA[i - 1].second;
    lock_cnt[1] += LB[i - 1].second;

    int32_t jump = lock_cnt[0] + lock_cnt[1] - (i) + N;

    if (mm.find(jump) != mm.end()) {
      int32_t prev_ind = mm[jump];

      int64_t cur_ans = T[prev_ind];
      int32_t pointers[2][2] = {0};

      FOR(z, prev_ind, i) {
        reserved[0][LA[z].second][pointers[0][LA[z].second]++] = LA[z].first;
        reserved[1][LB[z].second][pointers[1][LB[z].second]++] = LB[z].first;
      }

      FOR(j, 0, pointers[0][0]) {
        cur_ans += abs(reserved[0][0][j] - reserved[1][1][j]);
      }

      FOR(j, 0, pointers[0][1]) {
        cur_ans += abs(reserved[0][1][j] - reserved[1][0][j]);
      }

      T[i] = min(T[i], cur_ans);
    }

    mm[jump] = i;
  }

  return T[N];
}

int64_t get_cost(vi X, vi P) {
  N = sz(X);
  M = sz(P);

  map<int32_t, int32_t> locked;
  trav(x, P) { locked[x] = 1; }

  map<pi, int32_t> d;

  for (int32_t i{0}; i < sz(X); i++) {
    // DBG(X[i]);
    d[{X[i], locked[i]}]++;
  }

  vpi rem;
  vpi LA;
  vpi LB;
  vpi LF;

  if (N % 2 == 1) {
    d[{0, 1}]++;
  }

  trav(x, d) {
    if (x.first.second == 1) {
      if (d.find({-x.first.first, x.first.second}) == d.end()) {
        // no mirrored self
        FOR(i, 0, x.second) {
          if (x.first.first < 0) {
            LA.pb({-x.first.first, x.first.second});
          } else {
            LB.pb({x.first.first, x.first.second});
          }
        }
      } else {
        int32_t to_add = max(x.second - d[{-x.first.first, x.first.second}], 0);

        if (x.first.first == 0) {
          to_add = x.second % 2;
        }

        FOR(i, 0, to_add) {
          if (x.first.first < 0) {
            LA.pb({-x.first.first, x.first.second});
          } else {
            LB.pb({x.first.first, x.first.second});
          }
        }
      }
    } else {
      FOR(i, 0, x.second) { LF.pb(x.first); }
    }
  }
  if (sz(LA) + sz(LB) > sz(LF)) {
    return -1;
  }

  // should be sorted, but doesnt hurt to do it again
  sort(LA.begin(), LA.end());
  sort(LB.begin(), LB.end());
  sort(LF.begin(), LF.end());

  N = sz(LA) + sz(LB) + sz(LF);

  int32_t need_left = N / 2 - sz(LA);
  // we go for a perfect match, so we need N/2 on the left side
  FOR(i, 0, sz(LF)) {
    if (need_left) {
      LA.pb({-LF[i].first, LF[i].second});
      need_left--;
    } else {
      LB.pb({LF[i].first, LF[i].second});
    }
  }
  sort(LA.begin(), LA.end());
  sort(LB.begin(), LB.end());
  return solve_lines(LA, LB);
}

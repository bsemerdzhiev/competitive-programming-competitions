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

int32_t n, m;

void solve() {
  int32_t op, car_ind;

  set<int32_t> indeces;
  map<int32_t, int32_t> car_to_ind;
  map<int32_t, int32_t> interval_lengths;

  auto custom_compare = [](const pi &lhs, const pi &rhs) {
    return (lhs.first + 1) / 2 < (rhs.first + 1) / 2 ||
           ((lhs.first + 1) / 2 == (rhs.first + 1) / 2 &&
            (lhs.second > rhs.second));
  };

  set<pi, decltype(custom_compare)> ss;

  for (int32_t i{0}; i < m; i++) {
    re(op, car_ind);

    // ps(op, car_ind);
    // for (auto x : ss) {
    //   DBG(x.first, x.second);
    // }
    // ps();

    if (op == 1) {
      // adding a new car
      if (sz(indeces) == 0) {
        indeces.insert(1);
        car_to_ind[car_ind] = 1;
        interval_lengths[1] = n - 1;

        ps(1);
      } else {
        int32_t first_ind = *indeces.begin();
        int32_t last_ind = *indeces.rbegin();

        int32_t dist_l = abs(first_ind - 1);
        int32_t dist_r = abs(last_ind - n);

        int32_t size_from_set = 0;
        pi from_set = {0, 0};
        if (ss.size()) {
          from_set = *ss.rbegin();
        }

        if ((from_set.first + 1) / 2 > max(dist_l, dist_r) ||
            ((from_set.first + 1) / 2 == dist_r && dist_r > dist_l)) {
          if (ss.find(from_set) != ss.end())
            ss.erase(ss.find(from_set));

          int32_t chos_ind = from_set.second;
          int32_t int_len = from_set.first;

          int32_t new_ind = chos_ind + (int_len + 1) / 2;
          ps(new_ind);
          car_to_ind[car_ind] = new_ind;
          indeces.insert(new_ind);

          int32_t new_len = int_len - (new_ind - chos_ind);

          interval_lengths[chos_ind] -= new_len + 1;
          ss.insert({interval_lengths[chos_ind], chos_ind});

          interval_lengths[new_ind] = new_len;
          ss.insert({interval_lengths[new_ind], new_ind});
        } else {
          if (dist_l >= dist_r) {
            ps(1);
            car_to_ind[car_ind] = 1;
            indeces.insert(1);

            interval_lengths[1] = dist_l - 1;
            ss.insert({dist_l - 1, 1});
          } else {
            ps(n);
            car_to_ind[car_ind] = n;
            indeces.insert(n);

            auto it = ss.find({interval_lengths[last_ind], last_ind});
            if (it != ss.end()) {
              ss.erase(it);
            }
            interval_lengths[last_ind] = dist_r - 1;
            ss.insert({dist_r - 1, last_ind});
          }
        }
      }
    } else {
      int32_t ind_to_remove = car_to_ind[car_ind];

      auto in_set = indeces.find(ind_to_remove);

      if (in_set == indeces.begin()) {
        indeces.erase(ind_to_remove);
        auto it = ss.find({interval_lengths[ind_to_remove], ind_to_remove});
        if (it != ss.end()) {
          ss.erase(it);
        }

        interval_lengths[ind_to_remove] = 0;
      } else {
        auto it = ss.find({interval_lengths[ind_to_remove], ind_to_remove});
        if (it != ss.end()) {
          ss.erase(it);
        }
        in_set = std::prev(in_set);

        it = ss.find({interval_lengths[*in_set], *in_set});
        if (it != ss.end()) {
          ss.erase(it);
        }

        interval_lengths[*in_set] += interval_lengths[ind_to_remove] + 1;

        if (ind_to_remove != *indeces.rbegin()) {
          ss.insert({interval_lengths[*in_set], *in_set});
        }

        indeces.erase(ind_to_remove);
      }
      interval_lengths[ind_to_remove] = 0;
    }
  }
}

int main() {
  setIO();

  re(n, m);
  solve();

  return 0;
}

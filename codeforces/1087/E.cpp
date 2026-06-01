#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 1e6 + 5;

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

int32_t n, q;
string a;

int32_t z_func[MAXN];

void z_function(int32_t st) {
  for (size_t i = 0; i < n; i++) {
    z_func[i] = 0;
  }

  int32_t l = st, r = st;
  for (int32_t i = st + 1; i < n; i++) {
    if (i < r) {
      z_func[i] = min(r - i, z_func[i - l + st]);
    }
    while (i + z_func[i] < n && a[i + z_func[i]] == a[st + z_func[i]]) {
      z_func[i]++;
    }

    if (z_func[i] + i >= r) {
      r = z_func[i] + i;
      l = i;
    }
  }
  for (int32_t i = st; i <= n; i++) {
    z_func[i] = min(z_func[i], i - st);
  }

  z_func[st] = n;
}

int64_t T[MAXN];

void solve_dp(int32_t l, int32_t r) {
  // multiset<int64_t> best_ans;
  // priority_queue<pair<int32_t, int64_t>> pq;

  stack<pair<int32_t, int64_t>> st;

  T[l] = 0;
  int64_t ans = 0;
  // best_ans.insert(0);
  st.push(make_pair(3 * n, 0));

  for (int32_t i = l; i <= r; i++) {
    // cout << i << " " << z_func[i] << endl;
    while (!st.empty()) {
      if (st.top().first < i) {
        st.pop();
      } else {
        break;
      }
    }

    // add the current
    if (z_func[i]) {
      int64_t best = st.top().second;
      while (!st.empty()) {
        if (st.top().first <= i + z_func[i]) {
          st.pop();
        } else {
          break;
        }
      }

      st.push(make_pair((i + z_func[i]), best + 1LL));
    }
    while (!st.empty()) {
      if (st.top().first <= i) {
        st.pop();
      } else {
        break;
      }
    }

    T[i] = st.top().second;

    ans += T[i];
  }
  cout << ans << "\n";
}

void solve() {
  int32_t l, r;
  for (int32_t i = 0; i < q; i++) {
    cin >> l >> r;
    l--;
    r--;

    z_function(l);

    solve_dp(l, r);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> q;
    cin >> a;
    solve();
  }

  return 0;
}

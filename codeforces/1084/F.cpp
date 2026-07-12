#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

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

int32_t n, m;
pair<int32_t, int32_t> a[MAXN], b[MAXN];

void solve() {
  map<int32_t, vector<int32_t>> mm;
  for (int32_t i{0}; i < n; i++) {
    mm[a[i].second].push_back(a[i].first);
  }
  multiset<int32_t> s;
  int64_t ans = 0;
  vector<int64_t> ans_non_incl(n + 2, 0);
  vector<int64_t> ans_incl(n + 2, 0);

  for (int32_t i{n + 1}; i >= 0; i--) {
    for (auto x : mm[i]) {
      s.insert(x);
      ans += x;
    }
    while (s.size() > i) {
      ans -= *s.begin();
      s.erase(s.begin());
    }

    ans_non_incl[i] = std::max(ans_non_incl[i], ans);
  }

  ans = 0;
  s.clear();
  for (int32_t i{n + 1}; i >= 0; i--) {
    for (auto x : mm[i]) {
      s.insert(x);
      ans += x;
    }
    while (s.size() > i - 1) {
      ans -= *s.begin();
      s.erase(s.begin());
    }

    ans_incl[i] = std::max(ans_incl[i], ans);
    // cout << i << " " << ans_incl[i] << "\n";
  }

  for (int32_t i{1}; i <= n + 1; i++) {
    ans_incl[i] = std::max(ans_incl[i], ans_incl[i - 1]);
    ans_non_incl[i] = std::max(ans_non_incl[i], ans_non_incl[i - 1]);
  }

  for (int32_t i{0}; i < m; i++) {
    // cout << ans_incl[b[i].second] << " ";
    cout << std::max(ans_incl[b[i].second] + b[i].first, ans_non_incl[n + 1])
         << " ";
  }

  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> m;
    for (int32_t i{0}; i < n; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].second++;
      a[i].second = min(n + 1, a[i].second);
    }

    for (int32_t i{0}; i < m; i++) {
      cin >> b[i].first >> b[i].second;

      b[i].second++;
      b[i].second = min(n + 1, b[i].second);
    }

    solve();
  }

  return 0;
}

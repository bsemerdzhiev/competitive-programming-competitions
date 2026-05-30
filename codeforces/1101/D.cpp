#include <bits/stdc++.h>

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

int32_t n, a[MAXN];
vector<std::array<int32_t, 3>> ans;

void rec(int32_t k, int32_t from, int32_t to, bool &possible) {
  if (k == -1 || !possible) {
    return;
  }
  int32_t new_from = from;
  // cout << k << " " << from << " " << to << endl;
  if (a[k] == k) {
    // move current
    ans.push_back({k + 1, from, to});
    // return;
  } else {
    int32_t to_remove = k - a[k];
    if (to_remove - 1 < 0 || to_remove - 1 > k) {
      possible = false;
      return;
    }

    rec(to_remove - 1, from, to ^ from, possible);

    // move current
    ans.push_back({k + 1, from, to});

    if (to_remove != k) {
      rec(to_remove - 1, to ^ from, from, possible);
    } else {
      new_from = to ^ from;
    }
  }
  rec(k - 1, new_from, to, possible);
}

void solve() {
  bool possble = true;
  ans.clear();
  rec(n - 1, 1, 3, possble);

  if (possble) {
    cout << "YES\n";
    cout << ans.size() << "\n";
    for (auto x : ans) {
      cout << x[0] << " " << x[1] << " " << x[2] << "\n";
    }
    // cout << "\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (size_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

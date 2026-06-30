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

int32_t n, m;
int32_t a[MAXN];
vector<int32_t> correct_ind[MAXN];
int32_t T[MAXN];

void solve() {
  for (int32_t i{1}; i <= n; i++) {
    correct_ind[i].clear();
    T[i] = 0;
  }

  multiset<int32_t> ms;
  ms.insert(0);

  for (int32_t i{1}; i <= n; i++) {
    int32_t new_ind = m - i + a[i];

    if (new_ind <= n) {
      correct_ind[new_ind].push_back(i);
    }

    for (auto x : correct_ind[i]) {
      ms.erase(ms.find(T[x] - x));
    }

    ms.insert(T[i] - i);

    for (auto x : correct_ind[i]) {
      ms.erase(ms.find(T[x] - x));
      ms.insert(T[x] - x);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> m;

    for (int32_t i{1}; i <= n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

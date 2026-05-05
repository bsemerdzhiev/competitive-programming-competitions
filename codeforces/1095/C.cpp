#include <bits/stdc++.h>
#include <cstdint>
#include <set>
#include <unordered_map>

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

bool check(int32_t middle) {
  unordered_map<int32_t, int32_t> av;
  multiset<int32_t> ss;

  for (int32_t i = 0; i < n; i++) {
    av[a[i]]++;
    ss.insert((a[i] - 1) / 2);
  }
  int32_t wanted = middle - 1;
  while (wanted >= 0) {
    if (av[wanted]) {
      ss.erase(ss.find((wanted - 1) / 2));
      av[wanted]--;
      wanted--;
    } else {
      if (!ss.empty() && *ss.rbegin() >= wanted) {
        wanted--;
        ss.erase(ss.find(*ss.rbegin()));
      } else {
        return false;
      }
    }
  }
  return true;
}

void solve() {
  sort(a, a + n);

  // cout << check(4) << "\n";

  int32_t l = 0, r = n;
  int32_t ans = 0;

  while (l <= r) {
    int32_t middle = (l + r) >> 1;

    if (check(middle)) {
      l = middle + 1;
      ans = middle;
    } else {
      r = middle - 1;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

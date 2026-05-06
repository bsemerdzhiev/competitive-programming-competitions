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

int32_t n;
string a, b;

bool solve() {
  int32_t sm = 0;
  int32_t k = 0;
  for (int32_t i = 0; i < n; i++) {
    if (a[i] == b[i]) {
      sm += a[i] == '(' ? 1 : -1;
    } else {
      k++;
    }
  }
  if (sm != 0 || (k & 1) == 1) {
    return false;
  }

  int32_t pref[2] = {0, 0};

  for (int32_t i = 0; i < n; i++) {
    if (a[i] == b[i]) {
      pref[0] += a[i] == '(' ? 1 : -1;
      pref[1] += a[i] == '(' ? 1 : -1;

      if (pref[0] > pref[1]) {
        swap(pref[0], pref[1]);
      }
      if (pref[0] < 0) {
        return false;
      }
    } else {
      if (pref[0] > pref[1]) {
        swap(pref[0], pref[1]);
      }
      pref[0] += 1;
      pref[1] -= 1;

      if (pref[1] < 0) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    cin >> a;
    cin >> b;

    cout << (solve() ? "YES" : "NO") << "\n";
  }

  return 0;
}

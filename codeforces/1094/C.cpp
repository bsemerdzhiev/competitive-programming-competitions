#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e3 + 5;

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

int32_t T[MAXN];

bool check(int32_t sm, int32_t bg, int32_t eq, int32_t k) {
  int32_t mid = (k / 2) + 1;

  if (mid > sm && mid <= sm + eq) {
    return true;
  }
  return false;
}

void solve() {
  vector<int32_t> vv;
  for (int32_t i = 0; i < n; i++) {
    vv.push_back(a[i]);
  }
  sort(vv.begin(), vv.end());
  int32_t wanted = vv[n / 2];

  if (a[0] == wanted) {
    T[0] = 1;
  } else {
    T[0] = -MAXN;
  }

  for (int32_t i = 1; i < n; i++) {
    int32_t k = 0;
    int32_t sm = 0, bg = 0, eq = 0;

    int32_t best_ans = -MAXN;
    for (int32_t j = i; j >= 0; j--) {
      if (a[j] > wanted) {
        bg++;
      } else if (a[j] < wanted) {
        sm++;
      } else {
        eq++;
      }
      k++;

      if (check(sm, bg, eq, k) && k % 2 == 1) {
        best_ans = max(best_ans, (j == 0 ? 0 : T[j - 1]) + 1);
      }
    }
    T[i] = best_ans;
  }
  cout << T[n - 1] << "\n";
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

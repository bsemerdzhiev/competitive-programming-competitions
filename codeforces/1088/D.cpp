#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 1e9 + 7;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) {
  return ((x + MOD) + (y + MOD) + MOD) % MOD;
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

int32_t n, a[MAXN], fact[MAXN];

int32_t comb(int32_t a, int32_t b) {
  return MO::mul(fact[a], MO::inverse(MO::mul(fact[b], fact[a - b])));
}

void solve() {
  vector<int32_t> digits(32, 0);

  for (int32_t j = n - 1; j >= 0; j--) {
    for (int32_t i = 0; i < 29; i++) {
      if (a[j] & (1 << i)) {
        digits[i] = j + 1;

        for (int32_t z = 0; z <= j; z++) {
          a[z] = MO::add(a[z], -MO::mul(comb(j + 1, z + 1), (1 << i)));
        }
      }
    }
  }

  for (int32_t i = 0; i < n; i++) {
    int32_t numb = 0;
    for (int32_t z = 0; z < 29; z++) {
      if (digits[z]) {
        numb |= (1 << z);
        digits[z]--;
      }
    }
    cout << numb << " ";
  }
  cout << "\n";
}

void precalc() {
  fact[0] = 1;
  for (int32_t i = 1; i < MAXN; i++) {
    fact[i] = MO::mul(fact[i - 1], i);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  precalc();

  while (t--) {
    cin >> n;

    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

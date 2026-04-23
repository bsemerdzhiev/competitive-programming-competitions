#include <any>
#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e4 + 5;

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

const int32_t MAXP = 1e7;
const int32_t CONSIDER_PR = 24;

int32_t n, a[MAXN], b[MAXN];

bool not_prime[MAXP];
vector<int32_t> prime_numbers;
int32_t T[MAXN][CONSIDER_PR];

void solve() {
  for (int32_t i = 0; i <= n; i++) {
    for (int32_t j = 0; j < CONSIDER_PR; j++) {
      T[i][j] = -MAXN;
    }
  }
  T[0][0] = 0;
  vector<bool> skip(n + 1);

  for (int32_t i = 1; i <= n; i++) {
    int64_t desired_left = i == 1 ? 1 : gcd(a[i], a[i - 1]);
    int64_t desired_right = i == n ? 1 : gcd(a[i], a[i + 1]);

    int64_t wanted =
        desired_left * desired_right / gcd(desired_left, desired_right);
    if (wanted < a[i] && wanted <= b[i]) {
      // cout << i << "\n";
      a[i] = wanted;
      skip[i] = 1;
    }
  }

  for (int32_t i = 1; i <= n; i++) {
    for (int32_t prev = 0; prev < CONSIDER_PR; prev++) {
      for (int32_t z = 0; z < CONSIDER_PR; z++) {
        if (z == 0) {
          T[i][z] = max(T[i][z], T[i - 1][prev] + (skip[i] ? 1 : 0));
          continue;
        }
        int64_t new_desired = 1LL * a[i] * prime_numbers[z];

        if (new_desired > b[i]) {
          continue;
        }

        if (i == 1) {
          if (gcd(new_desired, a[i + 1]) == gcd(a[i], a[i + 1]))
            T[i][z] = max(T[i][z], T[i - 1][prev] + (skip[i] ? 1 : z != 0));
        } else if (gcd(new_desired, (1LL * prime_numbers[prev] * a[i - 1])) ==
                       gcd(a[i], a[i - 1]) &&
                   (i == n
                        ? 1
                        : gcd(new_desired, a[i + 1]) == gcd(a[i], a[i + 1]))) {
          T[i][z] = max(T[i][z], T[i - 1][prev] + 1);
        }
      }
    }
  }

  int32_t ans = 0;
  for (int32_t i = 0; i < CONSIDER_PR; i++) {
    ans = max(ans, T[n][i]);
  }
  cout << ans << "\n";
}

void precompute() {
  prime_numbers.push_back(1);

  for (int64_t i = 2; i < MAXP; i++) {
    if (!not_prime[i]) {
      prime_numbers.push_back(i);
      for (int64_t j = i * i; j < MAXP; j += i) {
        not_prime[j] = true;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  precompute();

  while (t--) {
    cin >> n;

    for (int32_t i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int32_t i = 1; i <= n; i++) {
      cin >> b[i];
    }
    solve();
  }

  return 0;
}

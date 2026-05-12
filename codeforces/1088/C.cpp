#include <bits/stdc++.h>
#include <new>
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

int32_t n, k, a[MAXN], b[MAXN];

bool solve() {
  for (int32_t i = 0; i < n - k; i++) {
    if (a[i] != a[i + k]) {
      if (b[i] == -1) {
        b[i] = a[i];
      }
      if (b[i] != a[i]) {
        return false;
      }

      if (b[i + k] == -1) {
        b[i + k] = a[i + k];
      }
      if (b[i + k] != a[i + k]) {
        return false;
      }
    }
  }

  vector<bool> marked(n);
  for (int32_t i = 0; i < n - k; i++) {
    if (!marked[i]) {
      int32_t j = i;

      set<int32_t> ss;

      while (j + k < n && a[j] == a[j + k]) {
        marked[j] = 1;
        marked[j + k] = 1;

        if (b[j + k] != -1) {
          ss.insert(b[j + k]);
        }
        if (b[j] != -1) {
          ss.insert(b[j]);
        }

        j += k;
      }

      if (ss.size() > 1) {
        return false;
      }
      int32_t wanted = (ss.empty() ? b[i] : *ss.begin());

      for (int32_t z = i; z <= j; z += k) {
        b[z] = wanted;
      }
    }
  }

  unordered_map<int32_t, int32_t> cnt[2];

  for (int32_t i = 0; i < k; i++) {
    if (b[i] != -1) {
      cnt[1][b[i]]++;
    }
    cnt[0][a[i]]++;
  }
  for (auto x : cnt[1]) {
    if (cnt[0][x.first] < x.second) {
      return false;
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
    cin >> n >> k;
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }

    for (int32_t i = 0; i < n; i++) {
      cin >> b[i];
    }
    cout << (solve() ? "YES" : "NO") << "\n";
  }

  return 0;
}

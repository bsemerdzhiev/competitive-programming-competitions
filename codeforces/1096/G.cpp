#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;
const int64_t INF = 1e17;

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
int32_t tree[2][MAXN * 2];

void update(int32_t x, int32_t k, int32_t z) {
  for (int32_t j = x; j <= k; j += (j & -j)) {
    tree[z][j]++;
  }
}

int32_t query(int32_t l, int32_t z) {
  if (l <= 0) {
    return 0;
  }
  int32_t ans = 0;
  for (int32_t j{l}; j > 0; j -= (j & -j)) {
    ans += tree[z][j];
  }
  return ans;
}

int32_t query(int32_t l, int32_t r, int32_t z) {
  if (l > r) {
    return 0;
  }
  return query(r, z) - query(l - 1, z);
}

void solve() {
  int64_t sum = 0;

  set<int64_t> ss;
  ss.insert(sum);

  for (int32_t i{0}; i < n; i++) {
    sum = a[i] - sum;

    ss.insert(sum);
    ss.insert(-sum);
  }
  int32_t k = 1;
  map<int64_t, int32_t> mm;
  ss.insert(-INF);

  while (!ss.empty()) {
    int64_t x = *ss.begin();
    ss.erase(x);

    mm[x] = k++;
    // cout << x << " " << mm[x] << "\n";
  }

  int64_t ans = 0;
  sum = 0;
  update(mm[0], k, 1);

  // cout << query(1, 5, 0) << "\n";

  for (int32_t i{0}; i < n; i++) {
    sum = a[i] - sum;
    // cout << mm[sum] << "\n";

    update(mm[sum], k, i & 1);
    // cout << "UPD" << mm[sum] << "\n";

    ans += ((i + 2) / 2) - query(mm[-INF], mm[-sum], !(i & 1));
  }
  for (int32_t i{1}; i <= k; i++) {
    tree[0][i] = tree[1][i] = 0;
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i{0}; i < n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

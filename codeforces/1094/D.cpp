#include <bits/stdc++.h>
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
int64_t pref_sm[MAXN];

int32_t sums[MAXN], indeces[MAXN];

void update(int32_t tree[MAXN], int32_t ind, int32_t val) {
  for (; ind <= n; ind += ind & -ind) {
    tree[ind] += val;
  }
}
int32_t query(int32_t tree[MAXN], int32_t ind) {
  int32_t ans = 0;

  for (; ind > 0; ind -= ind & -ind) {
    // cout << "DSA" << "\n";
    ans += tree[ind];
  }
  return ans;
}

void solve() {
  for (int32_t i = 0; i <= n; i++) {
    sums[i] = indeces[i] = 0;
  }

  int64_t cur_sm = 0;
  set<int64_t> ss;
  unordered_map<int64_t, int32_t> new_ind;

  for (int32_t i = 1; i <= n; i++) {
    pref_sm[i] = cur_sm;
    cur_sm += a[i];

    ss.insert(pref_sm[i]);
  }

  int32_t ind = 1;
  for (set<int64_t>::iterator it = ss.begin(); it != ss.end(); it++) {
    new_ind[*it] = ind++;
  }

  for (int32_t i = 1; i <= n; i++)
    update(sums, new_ind[pref_sm[i]], 1);

  for (int32_t i = 1; i <= n; i++) {
    int32_t kth = (n - (i - 1)) - query(sums, new_ind[pref_sm[i]]) + 1;
    // cout << kth << "\n";
    update(sums, new_ind[pref_sm[i]], -1);

    // find kth element
    int32_t l = 1, r = n;
    int32_t ans = n;

    while (l <= r) {
      int32_t middle = (l + r) >> 1;

      if (middle - query(indeces, middle) >= kth) {
        ans = middle;
        r = middle - 1;
      } else {
        l = middle + 1;
      }
    }
    // int32_t wanted = kth + query(indeces, kth);
    update(indeces, ans, 1);
    cout << ans << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i = 1; i <= n; i++) {
      cin >> a[i];
    }
    solve();
  }

  return 0;
}

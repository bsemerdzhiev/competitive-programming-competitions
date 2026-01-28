#include <iostream>
#include <map>

const int32_t MAXN = 1e2 + 5;

int32_t n;
int32_t a[MAXN];

bool solve() {
  std::map<int32_t, int32_t> cnt;

  for (std::size_t i{0}; i < n; i++) {
    cnt[a[i]]++;
  }
  if (cnt[0] == 0) {
    return false;
  }
  cnt[0]--;
  if (cnt[0] == 0) {
    return true;
  }

  return cnt[0] > 0 && cnt[1] > 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int32_t t;

  std::cin >> t;

  while (t--) {
    std::cin >> n;

    for (std::size_t i{0}; i < n; i++) {
      std::cin >> a[i];
    }

    std::cout << (solve() ? "YES" : "NO") << "\n";
  }
}

#include <iostream>

const int32_t MAXN = 1e2 + 5;

int32_t n;
int32_t a[MAXN];

bool solve() {
  bool first = a[0] % 2;

  for (std::size_t i{0}; i < n; i++) {
    if (a[i] % 2 == a[0] % 2) {
      if (i % 2 != 0) {
        return false;
      }
    } else {
      if (i % 2 != 1) {
        return false;
      }
    }
  }
  return true;
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

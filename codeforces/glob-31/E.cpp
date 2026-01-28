#include <iostream>

int64_t l, r;

int64_t solve() {
  if ((r - l) % 2 == 0) {
    return 0;
  }

  if (r - l == 1) {
    return 1;
  }

  int64_t c_l = l, c_r = r;
  int32_t c_zero = 0, c_one = 0;
  while ((c_l & 1) == 0) {
    c_zero++;
    c_l >>= 1;
  }

  while ((c_r & 1) == 1) {
    c_one++;
    c_r >>= 1;
  }

  return (1LL << std::min(c_zero, c_one)) - 1;
}

int main() {
  int32_t t;
  std::cin >> t;

  while (t--) {
    std::cin >> l >> r;

    std::cout << solve() << "\n";
  }

  return 0;
}

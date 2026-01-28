#include <iostream>
#include <map>
#include <string>
#include <vector>

int32_t n;
std::string a;

void solve() {
  std::map<int32_t, int32_t> cnt;
  for (size_t i{0}; i < n; i++) {
    cnt[a[i] - '0']++;
  }

  int32_t r = n - 1, l = 0;
  std::vector<int32_t> zeroes, ones;

  while (r > l) {
    while (l < n && a[l] == '0') {
      l++;
    }
    while (r >= 0 && a[r] == '1') {
      r--;
    }
    if (l >= r) {
      break;
    }
    zeroes.push_back(l + 1);
    ones.push_back(r + 1);
    l += 1;
    r -= 1;
  }
  if (zeroes.size() + ones.size() == 0) {
    std::cout << "Bob\n";
    return;
  }
  std::cout << "Alice\n" << ones.size() + zeroes.size() << "\n";
  for (auto &x : zeroes) {
    std::cout << x << " ";
  }
  for (int32_t i = ones.size() - 1; i >= 0; i--) {
    std::cout << ones[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int32_t t;

  std::cin >> t;

  while (t--) {
    std::cin >> n;
    std::cin >> a;

    solve();
  }
}

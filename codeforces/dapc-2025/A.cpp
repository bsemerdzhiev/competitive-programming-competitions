#include <cmath>
#include <iostream>
#include <vector>

const int32_t octave = 12;
const int32_t MAXN = (int32_t)1e3 + 5;

int32_t n, l, h;
std::vector<int32_t> notes;

bool can_fit_inside_interval(int32_t lb, int32_t ub) {
  if (lb >= l) {
    int32_t scale = (lb - l) / octave;
    lb -= scale * octave;
    ub -= scale * octave;
  } else {
    int32_t scale = std::ceil(((double)l - (double)lb) / octave);

    lb += scale * octave;
    ub += scale * octave;
  }

  return lb >= l && ub <= h;
}

int32_t memo[MAXN];

int32_t find_best_interval(int32_t index) {
  if (index == n) {
    return n;
  }

  if (memo[index] != 0) {
    return memo[index];
  }

  int32_t lb = notes[index], ub = notes[index];

  int32_t &ans = memo[index];
  ans = 1;

  for (int32_t i = index; i < n; i++) {
    lb = std::min(lb, notes[i]);
    ub = std::max(ub, notes[i]);

    if (can_fit_inside_interval(lb, ub)) {
      ans = std::max(ans, std::min(i - index + 1, find_best_interval(i + 1)));
    } else {
      break;
    }
  }
  return ans;
}

int32_t solve() { return find_best_interval(0); }

int main() {
  std::cin.tie(NULL);
  std::ios_base::sync_with_stdio(false);

  std::cin >> n >> l >> h;
  notes.resize(n);

  for (int32_t i = 0; i < n; i++) {
    std::cin >> notes[i];
  }

  std::cout << solve() << std::endl;

  return 0;
}

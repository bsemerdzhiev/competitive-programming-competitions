#include <ios>
#include <iostream>
#include <queue>
#include <string>

const int32_t MAXN = 2e5 + 5;

int32_t n;
std::string a;
int32_t suff_closing[MAXN];
int32_t suff_matched[MAXN];

void solve() {
  suff_closing[n] = 0;
  suff_matched[n] = 0;

  suff_closing[n - 1] = (a[n - 1] == ')');
  suff_matched[n - 1] = 0;

  for (int32_t i = n - 2; i >= 0; i--) {
    suff_closing[i] = suff_closing[i + 1] + (a[i] == ')');
    if (a[i] == ')') {
      suff_matched[i] = suff_matched[i + 1];
    } else {
      suff_matched[i] =
          ((suff_closing[i] - suff_matched[i + 1]) > 0) + suff_matched[i + 1];
    }
  }

  std::queue<int32_t> qq;
  for (int32_t i{0}; i < n; i++) {
    if (a[i] == '(') {
      qq.push(i);
    }
  }

  int32_t next_start = qq.front();
  qq.pop();

  int32_t cur_sum = 0;
  int32_t answer = -1;

  for (int32_t i{0}; i < n; i++) {
    while (i >= next_start) {
      if (qq.empty()) {
        break;
      }
      next_start = qq.front();
      qq.pop();
    }
    if (a[i] == '(') {
      if (a[i] == '(') {
        cur_sum += 1;
      } else {
        cur_sum -= 1;
      }
      continue;
    }
    if (i >= next_start) {
      break;
    }

    if (suff_closing[next_start + 1] >= cur_sum + 1) {
      int32_t take_more = std::min(suff_closing[next_start + 1] - (cur_sum + 1),
                                   suff_matched[next_start + 1]);
      int32_t final_answer = (i + (cur_sum + 2)) + (take_more * 2);

      if (final_answer >= n) {
        if (a[i] == '(') {
          cur_sum += 1;
        } else {
          cur_sum -= 1;
        }
        continue;
      }
      answer = std::max(answer, final_answer);
    }
    if (a[i] == '(') {
      cur_sum += 1;
    } else {
      cur_sum -= 1;
    }
  }

  std::cout << answer << "\n";
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

  return 0;
}

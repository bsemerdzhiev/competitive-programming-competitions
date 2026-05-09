#include <cstdio>
#include <random>

using namespace std;

mt19937 randomGenerator(2708199);

struct Treap {
  long long key;
  int priority;
  Treap *left, *right;
  int tSize;

  Treap(long long pKey = 0) {
    key = pKey;
    priority = randomGenerator();
    tSize = 1;
    left = nullptr;
    right = nullptr;
  }

  void recalc() {
    int l = (left == nullptr ? 0 : left->tSize);
    int r = (right == nullptr ? 0 : right->tSize);
    tSize = l + r + 1;
  }

  long long find_kth(int k) {
    int l = (left == nullptr ? 0 : left->tSize);
    if (l == k) {
      return key;
    } else if (l > k) {
      return left->find_kth(k);
    } else {
      return right->find_kth(k - l - 1);
    }
  }
};

Treap *root = nullptr;

Treap *merge(Treap *sm, Treap *bg) {
  if (sm == nullptr) {
    return bg;
  } else if (bg == nullptr) {
    return sm;
  }
  if (sm->priority > bg->priority) {
    sm->right = merge(sm->right, bg);
    sm->recalc();
    return sm;
  } else {
    bg->left = merge(sm, bg->left);
    bg->recalc();
    return bg;
  }
}

pair<Treap *, Treap *> split(Treap *t, long long key) {
  if (t == nullptr) {
    return {nullptr, nullptr};
  }
  if (t->key < key) {
    auto splitResults = split(t->right, key);
    t->right = splitResults.first;
    t->recalc();
    return {t, splitResults.second};
  } else {
    auto splitResults = split(t->left, key);
    t->left = splitResults.second;
    t->recalc();
    return {splitResults.first, t};
  }
}

void add_number(long long x) {
  if (root == nullptr) {
    root = new Treap(x);
    return;
  }
  Treap *t = new Treap(x);
  auto splitResults = split(root, x);
  splitResults.first = merge(splitResults.first, t);
  root = merge(splitResults.first, splitResults.second);
}

void remove_number(long long x) {
  auto splitResults1 = split(root, x);
  auto splitResults2 = split(splitResults1.second, x + 1);
  root = merge(splitResults1.first, splitResults2.second);
}

long long kth_number(int k) { return root->find_kth(k - 1); }

int main() {
  for (int32_t i = 0; i < 4000000; i++) {
    add_number(randomGenerator());
    // printf("%lld\n", kth_number(1));
  }
  return 0;
}

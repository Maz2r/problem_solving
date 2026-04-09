#include <iostream>

using namespace std;

int perm[10];
int N, M;

void func(int k);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  func(0);

  return 0;
}

void func(int k) {
  if (k == M) {
    for (int i = 1; i <= M; i++) {
      cout << perm[i] << ' ';
    }
    cout << '\n';

    return;
  }

  for (int i = 1; i <= N; i++) {
    perm[k + 1] = i;
    func(k + 1);
  }

  return;
}

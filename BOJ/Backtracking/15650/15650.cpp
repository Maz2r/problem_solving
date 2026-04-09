#include <iostream>

using namespace std;

void func(int k);

int perm[12];
bool is_issued[12];
int N, M;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i <= N; i++) {
    is_issued[i] = false;
  }
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
    if (i <= perm[k]) continue;

    perm[k + 1] = i;
    is_issued[i] = true;
    func(k + 1);
    is_issued[i] = false;
  }

  return;
}

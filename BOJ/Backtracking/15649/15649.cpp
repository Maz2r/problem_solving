#include <iostream>

using namespace std;

int perm[10];
bool issued[10] = {false};
int N, M;

void func(int nx);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  func(0);

  return 0;
}

void func(int nx) {
  if (nx == M) {
    for (int i = 0; i < M; i++) {
      cout << perm[i] << ' ';
    }
    cout << '\n';

    return;
  }

  for (int i = 0; i < N; i++) {
    if (issued[i]) continue;
    perm[nx] = i + 1;
    issued[i] = true;
    func(nx + 1);
    issued[i] = false;
  }

  return;
}

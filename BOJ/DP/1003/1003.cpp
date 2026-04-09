#include <iostream>

using namespace std;

int T;

int DP_t_0[45];
int DP_t_1[45];
int N;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> T;
  for (int i = 0; i < T; i++) {
    cin >> N;
    if (N == 0) {
      cout << 1 << ' ' << 0 << '\n';
      continue;
    }
    if (N == 1) {
      cout << 0 << ' ' << 1 << '\n';
      continue;
    }

    // initialization
    DP_t_0[0] = 1;
    DP_t_0[1] = 0;
    DP_t_1[0] = 0;
    DP_t_1[1] = 1;

    for (int j = 2; j <= N; j++) {
      DP_t_0[j] = DP_t_0[j - 1] + DP_t_0[j - 2];
      DP_t_1[j] = DP_t_1[j - 1] + DP_t_1[j - 2];
    }

    cout << DP_t_0[N] << ' ' << DP_t_1[N] << '\n';
  }

  return 0;
}

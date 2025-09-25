#include <algorithm>
#include <iostream>

using namespace std;

int DP[302][3];

int score[302];
int N;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> score[i];
  }

  if (N == 1) {
    cout << score[0];

    return 0;
  }
  if (N == 2) {
    cout << score[0] + score[1];

    return 0;
  }

  // Initialization
  DP[0][0] = score[0];
  DP[0][1] = score[0];
  DP[1][0] = score[1];
  DP[1][1] = score[0] + score[1];

  for (int i = 2; i < N; i++) {
    DP[i][0] = max(DP[i - 2][0] + score[i], DP[i - 2][1] + score[i]);
    DP[i][1] = DP[i - 1][0] + score[i];
  }

  cout << max(DP[N - 1][0], DP[N - 1][1]);

  return 0;
}

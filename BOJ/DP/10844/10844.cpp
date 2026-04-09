#include <iostream>

using namespace std;

int DP_t[103][12];
int N;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N;
  if (N == 1) {
    cout << 9;

    return 0;
  }
  if (N == 2) {
    cout << 17;

    return 0;
  }

  // initialization
  for (int i = 1; i <= 2; i++) {
    for (int j = 0; j <= 9; j++) {
      if (i == 1 && j == 0) {
        DP_t[i][j] = 0;
        continue;
      }
      if (i == 1) {
        DP_t[i][j] = 1;
        continue;
      }
      if (j == 0 || j == 1 || j == 9) {
        DP_t[i][j] = 1;
        continue;
      }

      DP_t[i][j] = 2;
    }
  }

  // recurrence
  for (int i = 3; i <= N; i++) {
    for (int j = 0; j <= 9; j++) {
      if (j == 0) {
        DP_t[i][j] = DP_t[i - 1][1];
        continue;
      }
      if (j == 9) {
        DP_t[i][j] = DP_t[i - 1][8];
        continue;
      }

      DP_t[i][j] = (DP_t[i - 1][j - 1] + DP_t[i - 1][j + 1]) % 1000000000;
    }
  }

  int answer = 0;
  for (int i = 0; i <= 9; i++) {
    answer = (answer + DP_t[N][i]) % 1000000000;
  }

  cout << answer;

  return 0;
}

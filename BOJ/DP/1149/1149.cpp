#include <algorithm>
#include <iostream>

using namespace std;

int DP[1002][5];

int cost[1002][5];
int N;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> cost[i][j];
    }
  }

  // Initialization
  DP[0][0] = cost[0][0];
  DP[0][1] = cost[0][1];
  DP[0][2] = cost[0][2];

  for (int i = 1; i < N; i++) {
    DP[i][0] = cost[i][0] + min(DP[i - 1][1], DP[i - 1][2]);
    DP[i][1] = cost[i][1] + min(DP[i - 1][0], DP[i - 1][2]);
    DP[i][2] = cost[i][2] + min(DP[i - 1][0], DP[i - 1][1]);
  }

  cout << min(min(DP[N - 1][0], DP[N - 1][1]), DP[N - 1][2]);

  return 0;
}

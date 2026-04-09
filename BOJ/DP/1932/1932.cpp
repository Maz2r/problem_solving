#include <algorithm>
#include <iostream>

using namespace std;

int int_tri[500][500];
int DP_t[500][500];
int n;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      cin >> int_tri[i][j];
    }
  }

  // initialization
  DP_t[0][0] = int_tri[0][0];

  // recurrence
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0) {
        DP_t[i][j] = DP_t[i - 1][j] + int_tri[i][j];
        continue;
      }
      if (j == i) {
        DP_t[i][j] = DP_t[i - 1][j - 1] + int_tri[i][j];
        continue;
      }

      DP_t[i][j] = max(DP_t[i - 1][j - 1] + int_tri[i][j],
                       DP_t[i - 1][j] + int_tri[i][j]);
    }
  }

  int answer = -1;
  for (int i = 0; i < n; i++) {
    if (DP_t[n - 1][i] <= answer) continue;

    answer = DP_t[n - 1][i];
  }

  cout << answer;

  return 0;
}

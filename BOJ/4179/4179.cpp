#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

char board[1002][1002];
int R, C;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> R >> C;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> board[i][j];
    }
  }

    return 0;
}

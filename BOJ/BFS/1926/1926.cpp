#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

int n, m;
int board[502][502];
bool vis[502][502];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> board[i][j];
    }
  }

  int paint_num = 0;
  int paint_size = 0;
  int largest_paint_size = 0;

  queue<pair<int, int>> Q;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] != 1 || vis[i][j]) continue;

      paint_size = 1;

      Q.push({i, j});
      vis[i][j] = true;
      while (!Q.empty()) {
        pair<int, int> cur = Q.front();
        Q.pop();
        for (int dir = 0; dir < 4; dir++) {
          int x = cur.X + dx[dir];
          int y = cur.Y + dy[dir];
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          if (board[x][y] != 1 || vis[x][y]) continue;

          Q.push({x, y});
          vis[x][y] = true;
          paint_size++;
        }
      }
      if (paint_size > largest_paint_size) {
        largest_paint_size = paint_size;
      }
      paint_num++;
    }
  }

  cout << paint_num << "\n";
  cout << largest_paint_size << "\n";

  return 0;
}

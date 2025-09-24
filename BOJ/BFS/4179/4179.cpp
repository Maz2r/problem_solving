#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

char board[1002][1002];
int dist[1002][1002];
int dist_J[1002][1002];
int R, C;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  queue<pair<int, int>> Q;
  pair<int, int> J_pos;

  cin >> R >> C;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> board[i][j];
      if (board[i][j] == 'J') {
        J_pos = {i, j};
        dist[j][j] = -1;
        dist_J[i][j] = 0;
      } else if (board[i][j] == 'F') {
        Q.push({i, j});
        dist[i][j] = 0;
        dist_J[i][j] = -1;
      } else {
        dist[i][j] = -1;
        dist_J[i][j] = -1;
      }
    }
  }

  while (!Q.empty()) {
    pair<int, int> cur = Q.front();
    Q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.X + dx[i];
      int ny = cur.Y + dy[i];

      if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
      if (board[nx][ny] == '#' || dist[nx][ny] >= 0) continue;

      Q.push({nx, ny});
      dist[nx][ny] = dist[cur.X][cur.Y] + 1;
    }
  }

  Q.push(J_pos);
  while (!Q.empty()) {
    pair<int, int> cur = Q.front();
    Q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.X + dx[i];
      int ny = cur.Y + dy[i];

      if (nx < 0 || nx >= R || ny < 0 || ny >= C) {
        cout << dist_J[cur.X][cur.Y] + 1 << '\n';

        return 0;
      }
      if (board[nx][ny] == '#' || dist_J[nx][ny] >= 0) continue;
      if (dist[nx][ny] != -1 && dist_J[cur.X][cur.Y] + 1 >= dist[nx][ny])
        continue;

      Q.push({nx, ny});
      dist_J[nx][ny] = dist_J[cur.X][cur.Y] + 1;
    }
  }

  cout << "IMPOSSIBLE" << '\n';

  return 0;
}

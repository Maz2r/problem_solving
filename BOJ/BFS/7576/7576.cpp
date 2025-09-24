#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

int board[1002][1002];
int dist[1002][1002];
int N, M;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  queue<pair<int, int>> Q;
  int already_riped = 1;

  cin >> M >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
      already_riped *= board[i][j];
      if (board[i][j] == 1) {
        Q.push({i, j});
        dist[i][j] = 0;
      } else {
        dist[i][j] = -1;
      }
    }
  }
  if (already_riped != 0) {
    cout << 0 << '\n';

    return 0;
  }

  while (!Q.empty()) {
    pair<int, int> cur = Q.front();
    Q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.X + dx[i];
      int ny = cur.Y + dy[i];

      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (board[nx][ny] != 0 || dist[nx][ny] > 0) continue;

      Q.push({nx, ny});
      dist[nx][ny] = dist[cur.X][cur.Y] + 1;
    }
  }

  int answer = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] != -1 && dist[i][j] == -1) {
        cout << -1 << '\n';

        return 0;
      }
      if (dist[i][j] > answer) {
        answer = dist[i][j];
      }
    }
  }

  cout << answer << '\n';

  return 0;
}

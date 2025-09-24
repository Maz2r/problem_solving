#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

string board[102];
int dist[102][102];
int N, M;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> board[i];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      dist[i][j] = -1;
    }
  }

  queue<pair<int, int>> Q;

  Q.push({0, 0});
  dist[0][0] = 1;
  while (!Q.empty()) {
    pair<int, int> cur = Q.front();
    Q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = cur.X + dx[i];
      int ny = cur.Y + dy[i];

      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (board[nx][ny] == '0' || dist[nx][ny] != -1) continue;

      Q.push({nx, ny});
      dist[nx][ny] = dist[cur.X][cur.Y] + 1;
    }
  }

  cout << dist[N - 1][M - 1] << '\n';

  return 0;
}

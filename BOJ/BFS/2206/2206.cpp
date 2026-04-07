#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

#define X first
#define Y second

int map[1003][1003];
int dist[2][1003][1003];
int N, M;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  string s;
  for (int i = 0; i < N; i++) {
    cin >> s;
    for (int j = 0; j < M; j++) {
      map[i][j] = s[j] - '0';
      dist[0][i][j] = 0;
      dist[1][i][j] = 0;
    }
  }

  queue<pair<int, pair<int, int>>> Q;

  dist[0][0][0] = 1;
  Q.push({0, {0, 0}});
  while (!Q.empty()) {
    pair<bool, pair<int, int>> cur = Q.front();
    Q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int nx = cur.Y.X + dx[dir];
      int ny = cur.Y.Y + dy[dir];

      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

      if (cur.X) {
        if ((map[nx][ny] == 1) ||
            (dist[cur.X][nx][ny] != 0 &&
             dist[cur.X][nx][ny] <= dist[cur.X][cur.Y.X][cur.Y.Y] + 1))
          continue;

        dist[cur.X][nx][ny] = dist[cur.X][cur.Y.X][cur.Y.Y] + 1;
        Q.push({cur.X, {nx, ny}});
      } else {
        if (map[nx][ny] == 0) {
          if (dist[cur.X][nx][ny] != 0 &&
              dist[cur.X][nx][ny] <= dist[cur.X][cur.Y.X][cur.Y.Y] + 1)
            continue;

          dist[cur.X][nx][ny] = dist[cur.X][cur.Y.X][cur.Y.Y] + 1;
          Q.push({cur.X, {nx, ny}});
        } else {
          if (dist[1][nx][ny] != 0 &&
              dist[1][nx][ny] <= dist[cur.X][cur.Y.X][cur.Y.Y] + 1)
            continue;

          dist[1][nx][ny] = dist[cur.X][cur.Y.X][cur.Y.Y] + 1;
          Q.push({1, {nx, ny}});
        }
      }
    }
  }

  if ((dist[0][N - 1][M - 1] == 0) && (dist[1][N - 1][M - 1] == 0)) {
    cout << -1;
  } else if ((dist[0][N - 1][M - 1] != 0) && (dist[1][N - 1][M - 1] == 0)) {
    cout << dist[0][N - 1][M - 1];
  } else if ((dist[0][N - 1][M - 1] == 0) && (dist[1][N - 1][M - 1] != 0)) {
    cout << dist[1][N - 1][M - 1];
  } else {
    cout << (dist[0][N - 1][M - 1] < dist[1][N - 1][M - 1]
                 ? dist[0][N - 1][M - 1]
                 : dist[1][N - 1][M - 1]);
  }

  return 0;
}

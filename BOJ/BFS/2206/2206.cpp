#include <iostream>
#include <utility>
#include <queue>

using namespace std;

#define X first
#define Y second

int map[1003][1003];
int dist[1003][1003];
int N, M;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> map[i][j];
      dist[i][j] = 0;
    }
  }

  queue<pair<bool, pair<int, int>>> Q;

  dist[0][0] = 1;
  Q.push({false, {0, 0}});
  while(!Q.empty()) {
    pair<bool, pair<int, int>> cur = Q.front();
    Q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int nx = cur.Y.X + dx[dir];
      int ny = cur.Y.Y + dy[dir];

      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      
      if (cur.X) {
        if ((map[nx][ny] == 1) || (dist[nx][ny] != 0 && )) continue;
      }
      else {

      }
    }
  }

  return 0;
}

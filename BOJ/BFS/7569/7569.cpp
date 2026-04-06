#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

int box[100][100][100];
bool vis[100][100][100];
int H, N, M;

int dz[6] = {-1, +1, 0, 0, 0, 0};
int dx[6] = {0, 0, -1, +1, 0, 0};
int dy[6] = {0, 0, 0, 0, -1, +1};

bool is_all_riped = true;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> M >> N >> H;

  for (int h = H - 1; h >= 0; h--) {
    for (int n = 0; n < N; n++) {
      for (int m = 0; m < M; m++) {
        cin >> box[h][n][m];
        vis[h][n][m] = false;
      }
    }
  }

  for (int h = 0; h < H; h++) {
    for (int n = 0; n < N; n++) {
      for (int m = 0; m < M; m++) {
        if (box[h][n][m] == 0) {
          is_all_riped = false;
          break;
        }
      }
      if (!is_all_riped) break;
    }
    if (!is_all_riped) break;
  }

  if (is_all_riped) {
    cout << 0;

    return 0;
  }

  queue<pair<int, pair<int, int>>> Q;

  for (int h = 0; h < H; h++) {
    for (int n = 0; n < N; n++) {
      for (int m = 0; m < M; m++) {
        if (box[h][n][m] != 1) continue;

        Q.push({h, {n, m}});
        vis[h][n][m] = true;
        while (!Q.empty()) {
          pair<int, pair<int, int>> cur = Q.front();
          Q.pop();

          for (int dir = 0; dir < 6; dir++) {
            int nz = cur.X + dz[dir];
            int nx = cur.Y.X + dx[dir];
            int ny = cur.Y.Y + dy[dir];

            if (nz < 0 || nz >= H || nx < 0 || nx >= N || ny < 0 || ny >= M)
              continue;
            if (box[nz][nx][ny] == -1 || vis[nz][nx][ny] || (box[nz][nx][ny] != 0 && box[nz][nx][ny] <= box[cur.X][cur.Y.X][cur.Y.Y] + 1)) continue;

            box[nz][nx][ny] = box[cur.X][cur.Y.X][cur.Y.Y] + 1;

            Q.push({nz, {nx, ny}});
            vis[nz][nx][ny] = true;
          }
        }

        for (int h = 0; h < H; h++) {
          for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
              vis[h][n][m] = false;
            }
          }
        }
      }
    }
  }

  int answer = -1;

  for (int h = 0; h < H; h++) {
    for (int n = 0; n < N; n++) {
      for (int m = 0; m < M; m++) {
        if (box[h][n][m] == -1) continue;
        if (box[h][n][m] == 0) {
          cout << -1;

          return 0;
        }

        if (answer < box[h][n][m] - 1) {
          answer = box[h][n][m] - 1;
        }
      }
    }
  }

  cout << answer;

  return 0;
}

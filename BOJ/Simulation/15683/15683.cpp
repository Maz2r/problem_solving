#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#define X first
#define Y second

int board[10][10];
int simulation[10][10];
int N, M;

vector<pair<int, int>> CCTV;
int K;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void cover_toward_dir(int x, int y, int dir);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int answer = 0;

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
      if (board[i][j] != 0 && board[i][j] != 6) CCTV.push_back({i, j});
      if (board[i][j] == 0) answer++;
    }
  }

  for (int setting = 0; setting < (1 << (2 * CCTV.size())); setting++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        simulation[i][j] = board[i][j];
      }
    }

    int setting_ = setting;
    for (int i = 0; i < (int)CCTV.size(); i++) {
      int dir = setting_ % 4;
      setting_ /= 4;
      int x = CCTV[i].first;
      int y = CCTV[i].second;
      if (board[x][y] == 1) {
        cover_toward_dir(x, y, dir);
      } else if (board[x][y] == 2) {
        cover_toward_dir(x, y, dir);
        cover_toward_dir(x, y, (dir + 2) % 4);
      } else if (board[x][y] == 3) {
        cover_toward_dir(x, y, dir);
        cover_toward_dir(x, y, (dir + 1) % 4);
      } else if (board[x][y] == 4) {
        cover_toward_dir(x, y, dir);
        cover_toward_dir(x, y, (dir + 1) % 4);
        cover_toward_dir(x, y, (dir + 2) % 4);
      } else {
        cover_toward_dir(x, y, dir);
        cover_toward_dir(x, y, (dir + 1) % 4);
        cover_toward_dir(x, y, (dir + 2) % 4);
        cover_toward_dir(x, y, (dir + 3) % 4);
      }
    }

    int uncovered_num = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (simulation[i][j] == 0) uncovered_num++;
      }
    }

    if (uncovered_num < answer) answer = uncovered_num;
  }

  cout << answer << '\n';

  return 0;
}

void cover_toward_dir(int x, int y, int dir) {
  while (true) {
    x += dx[dir];
    y += dy[dir];
    if (x < 0 || x >= N || y < 0 || y >= M) break;
    if (simulation[x][y] == 6) break;
    if (simulation[x][y] != 0) continue;
    simulation[x][y] = 7;
  }

  return;
}

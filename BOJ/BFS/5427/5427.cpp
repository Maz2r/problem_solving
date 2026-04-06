#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

int case_num;

int building[1002][1002];
int fire_time[1002][1002];
int s_time[1002][1002];
int H, W;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> case_num;
  for (int i = 0; i < case_num; i++) {
    pair<int, int> s_init_pos;
    queue<pair<int, int>> Q_fire;

    cin >> W >> H;
    char c;
    for (int j = 0; j < H; j++) {
      for (int k = 0; k < W; k++) {
        cin >> c;
        building[j][k] = c;
        if (building[j][k] == '.') {
          fire_time[j][k] = -1;
          s_time[j][k] = -1;
        } else if (building[j][k] == '#') {
          fire_time[j][k] = -2;
          s_time[j][k] = -2;
        } else if (building[j][k] == '*') {
          fire_time[j][k] = 0;
          s_time[j][k] = -2;
          Q_fire.push({j, k});
        } else {
          fire_time[j][k] = -1;
          s_time[j][k] = 0;
          s_init_pos = {j, k};
        }
      }
    }

    while (!Q_fire.empty()) {
      pair<int, int> cur_fire = Q_fire.front();
      Q_fire.pop();

      for (int dir = 0; dir < 4; dir++) {
        int nx = cur_fire.X + dx[dir];
        int ny = cur_fire.Y + dy[dir];

        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (fire_time[nx][ny] != -1) continue;

        fire_time[nx][ny] = fire_time[cur_fire.X][cur_fire.Y] + 1;
        Q_fire.push({nx, ny});
      }
    }

    queue<pair<int, pair<int, int>>> Q;

    Q.push({0, s_init_pos});
    while (!Q.empty()) {
      pair<int, pair<int, int>> cur = Q.front();
      Q.pop();

      for (int dir = 0; dir < 4; dir++) {
        int nx = cur.Y.X + dx[dir];
        int ny = cur.Y.Y + dy[dir];

        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (s_time[nx][ny] != -1 ||
            (fire_time[nx][ny] >= 0 &&
             fire_time[nx][ny] <=
                 cur.X + 1))  // Review Point: 불이 못번지는 구역이 존재 가능
          continue;

        s_time[nx][ny] = cur.X + 1;
        Q.push({s_time[nx][ny], {nx, ny}});
      }
    }

    int answer = 20000000;

    for (int j = 0; j < W; j++) {
      if (s_time[0][j] >= 0 && s_time[0][j] < answer) {
        answer = s_time[0][j] + 1;
      }
    }

    for (int j = 1; j < H; j++) {
      if (s_time[j][0] >= 0 && s_time[j][0] < answer) {
        answer = s_time[j][0] + 1;
      }
      if (s_time[j][W - 1] >= 0 && s_time[j][W - 1] < answer) {
        answer = s_time[j][W - 1] + 1;
      }
    }

    for (int j = 0; j < W; j++) {
      if (s_time[H - 1][j] >= 0 && s_time[H - 1][j] < answer) {
        answer = s_time[H - 1][j] + 1;
      }
    }

    if (answer == 20000000) {
      cout << "IMPOSSIBLE" << '\n';
    } else {
      cout << answer << '\n';
    }
  }

  return 0;
}

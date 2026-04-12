#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

char seat_map[7][7];
bool is_chosen[7][7];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

pair<int, int> seven_sisters[10];

int answer;

void func(int k);
bool is_connected(void);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> seat_map[i][j];
      is_chosen[i][j] = false;
    }
  }

  answer = 0;
  func(0);
  cout << answer;

  return 0;
}

void func(int k) {
  if (k == 7) {
    int feasible_S = 0;
    for (int i = 0; i < 7; i++) {
      if (seat_map[seven_sisters[i].X][seven_sisters[i].Y] == 'Y') continue;
      feasible_S++;
    }
    if (feasible_S < 4) return;
    if (!is_connected()) return;

    answer++;

    return;
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (k != 0) {
        if (i * 5 + j <= seven_sisters[k - 1].X * 5 + seven_sisters[k - 1].Y)
          continue;
      }

      seven_sisters[k] = {i, j};
      is_chosen[i][j] = true;
      func(k + 1);
      is_chosen[i][j] = false;
    }
  }

  return;
}

bool is_connected(void) {
  queue<pair<int, int>> Q;
  bool ss_visited[7][7];

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ss_visited[i][j] = false;
    }
  }

  ss_visited[seven_sisters[0].X][seven_sisters[0].Y] = true;
  Q.push(seven_sisters[0]);
  while (!Q.empty()) {
    pair<int, int> cur_ss = Q.front();
    Q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int nx = cur_ss.X + dx[dir];
      int ny = cur_ss.Y + dy[dir];

      if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
      if (!is_chosen[nx][ny]) continue;
      if (ss_visited[nx][ny]) continue;

      ss_visited[nx][ny] = true;
      Q.push({nx, ny});
    }
  }

  bool answer = true;
  for (int i = 0; i < 7; i++) {
    if (ss_visited[seven_sisters[i].X][seven_sisters[i].Y]) continue;

    answer = false;
    break;
  }

  return answer;
}

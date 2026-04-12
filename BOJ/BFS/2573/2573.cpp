#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define X first
#define Y second

int ocean[302][302];
bool visited[302][302];
vector<pair<int, int>> icebergs;
int N, M;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int year;

bool are_connected(void);  // Check icebergs are connected

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> ocean[i][j];
      if (ocean[i][j] > 0) icebergs.push_back({i, j});
    }
  }

  // Edge cases: (1) no iceberg, (2) icebergs are already not connected
  if (icebergs.empty() || !are_connected()) {
    cout << 0;

    return 0;
  }

  year = 0;
  // Year passes until: (1) icebergs are not connected, (2) all icebergs melt
  while (true) {
    year++;
    // Step 1: Icebergs melt
    vector<int> height_losses;

    vector<pair<int, int>>::iterator iter;
    for (iter = icebergs.begin(); iter != icebergs.end(); iter++) {
      pair<int, int> cur_iceberg = (*iter);
      int height_loss = 0;

      for (int dir = 0; dir < 4; dir++) {
        int nx = cur_iceberg.X + dx[dir];
        int ny = cur_iceberg.Y + dy[dir];

        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (ocean[nx][ny] != 0) continue;

        height_loss++;
      }

      height_losses.push_back(height_loss);
    }

    int icebergs_num = icebergs.size();
    for (int i = 0; i < icebergs_num; i++) {
      ocean[icebergs[i].X][icebergs[i].Y] -= height_losses[i];
      if (ocean[icebergs[i].X][icebergs[i].Y] < 0)
        ocean[icebergs[i].X][icebergs[i].Y] = 0;
    }

    for (iter = icebergs.begin(); iter != icebergs.end();) {
      if (ocean[(*iter).X][(*iter).Y] == 0)
        iter = icebergs.erase(iter);
      else
        iter++;
    }

    // Step 2: Check if icebergs exist
    if (icebergs.empty()) {
      year = 0;
      break;
    }

    // Step 2: Check if icebergs are connected
    if (!are_connected()) break;
  }

  cout << year;

  return 0;
}

bool are_connected(void) {
  queue<pair<int, int>> Q;
  int visited_icebergs_num = 0;

  Q.push(icebergs[0]);
  visited[icebergs[0].X][icebergs[0].Y] = true;
  visited_icebergs_num++;
  while (!Q.empty()) {
    pair<int, int> cur_iceberg = Q.front();
    Q.pop();

    for (int dir = 0; dir < 4; dir++) {
      int nx = cur_iceberg.X + dx[dir];
      int ny = cur_iceberg.Y + dy[dir];

      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (ocean[nx][ny] == 0 || visited[nx][ny]) continue;

      Q.push({nx, ny});
      visited[nx][ny] = true;
      visited_icebergs_num++;
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!visited[i][j]) continue;
      visited[i][j] = false;
    }
  }

  if (visited_icebergs_num != int(icebergs.size())) return false;

  return true;
}

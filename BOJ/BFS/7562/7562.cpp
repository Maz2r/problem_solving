#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define X first
#define Y second

int case_num;

int board[302][302];
int dist[302][302];
int l;

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int main(void) {
  cin >> case_num;
  for (int i = 0; i < case_num; i++) {
    cin >> l;
    for (int j = 0; j < l; j++) {
      for (int k = 0; k < l; k++) {
        dist[j][k] = -1;
      }
    }

    pair<int, int> knight_pos;
    pair<int, int> goal_pos;

    cin >> knight_pos.X >> knight_pos.Y;
    cin >> goal_pos.X >> goal_pos.Y;

    queue<pair<int, int>> Q;

    dist[knight_pos.X][knight_pos.Y] = 0;
    Q.push(knight_pos);
    while (!Q.empty()) {
      pair<int, int> cur = Q.front();
      Q.pop();

      for (int dir = 0; dir < 8; dir++) {
        int nx = cur.X + dx[dir];
        int ny = cur.Y + dy[dir];

        if (nx < 0 || nx >= l || ny < 0 || ny >= l) continue;
        if (dist[nx][ny] >= 0) continue;

        dist[nx][ny] = dist[cur.X][cur.Y] + 1;
        Q.push({nx, ny});
      }
    }

    cout << dist[goal_pos.X][goal_pos.Y] << '\n';
  }

  return 0;
}

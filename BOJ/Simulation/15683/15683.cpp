#include <iostream>

using namespace std;

void visit_toward_direction(int x, int y, int dir);

int board[10][10];
bool visited[10][10] = {false};
int N, M;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
    }
  }

  // Iterate the board
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 0 || board[i][j] == 6) continue;

      // Encountered a CCTV
      // Calculate the covered grid for each direction
      int covered_grid[4];
      for (int dir = 0; dir < 4; dir++) {
        covered_grid[dir] = 0;
        int nx = i + dx[dir];
        int ny = j + dy[dir];
        while (true) {
          if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
          if (board[nx][ny] == 6) break;
          if (board[nx][ny] != 0 || visited[nx][ny]) {
            nx += dx[dir];
            ny += dy[dir];
            continue;
          }
          covered_grid[dir]++;
          nx += dx[dir];
          ny += dy[dir];
        }
      }

      // Decide the direction of the CCTV
      // and visit the grids towards the decided direction
      if (board[i][j] == 1) {
        int best_dir = 0;
        for (int k = 1; k < 4; k++) {
          if (covered_grid[k] <= covered_grid[best_dir]) continue;
          best_dir = k;
        }
        visit_toward_direction(i, j, best_dir);
      } else if (board[i][j] == 2) {
        int covered_grid_vertical = covered_grid[0] + covered_grid[2];
        int covered_grid_horizontal = covered_grid[1] + covered_grid[3];

        if (covered_grid_vertical >= covered_grid_horizontal) {
          visit_toward_direction(i, j, 0);
          visit_toward_direction(i, j, 2);
        } else {
          visit_toward_direction(i, j, 1);
          visit_toward_direction(i, j, 3);
        }
      } else if (board[i][j] == 3) {
        int best_dir = 0;
        for (int k = 1; k < 4; k++) {
          if ((covered_grid[k] + covered_grid[(k + 1) % 4]) <=
              (covered_grid[best_dir] + covered_grid[(best_dir + 1) % 4]))
            continue;
          best_dir = k;
        }
        visit_toward_direction(i, j, best_dir);
        visit_toward_direction(i, j, (best_dir + 1) % 4);
      } else if (board[i][j] == 4) {
        int worst_dir = 0;
        for (int k = 1; k < 4; k++) {
          if (covered_grid[k] >= covered_grid[worst_dir]) continue;
          worst_dir = k;
        }
        for (int k = 0; k < 4; k++) {
          if (k == worst_dir) continue;
          visit_toward_direction(i, j, k);
        }
      } else {
        for (int k = 0; k < 4; k++) {
          visit_toward_direction(i, j, k);
        }
      }
    }
  }

  // Iterate the board
  // by calculating number of uncovered grid
  int answer = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == 0 && !visited[i][j]) answer++;
    }
  }

  cout << answer << '\n';

  return 0;
}

void visit_toward_direction(int x, int y, int dir) {
  int nx = x + dx[dir];
  int ny = y + dy[dir];
  while (true) {
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
    if (board[nx][ny] == 6) break;
    if (board[nx][ny] != 0 || visited[nx][ny]) {
      nx += dx[dir];
      ny += dy[dir];
      continue;
    }
    visited[nx][ny] = true;
    nx += dx[dir];
    ny += dy[dir];
  }

  return;
}

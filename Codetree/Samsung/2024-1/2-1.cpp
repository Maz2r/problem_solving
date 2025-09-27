#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define PADDING 3

// Golem Info
#define INIT_ROW_IDX 1
#define INIT_COLUMN_IDX first
#define EXIT second

#define CENTER 1
#define LEAF 2
#define EXIT_LEAF 3

#define X first
#define Y second

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int board[75][75];
bool fairy_visited[75][75];
int R, C;

pair<int, int> golem_info[1002];
int K;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int answer = 0;

// Golem
pair<int, int> move_golem_to_southest(int golem_idx);
pair<int, int> move_golem_once(int golem_idx, pair<int, int> golem_pos);
bool south_movable(pair<int, int> golem_pos);
bool west_south_movable(pair<int, int> golem_pos);
bool east_south_movable(pair<int, int> golem_pos);
void erase_golem(pair<int, int> golem_pos);
// Fairy
int move_fairy_to_southest(pair<int, int> fairy_pos);
void clear_fairy_visited(void);
// Utils
void clear_board(void);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Input
  cin >> R >> C >> K;
  for (int i = 0; i < K; i++) {
    cin >> golem_info[i].INIT_COLUMN_IDX >> golem_info[i].EXIT;
    golem_info[i].INIT_COLUMN_IDX--;
  }
  // Initialization
  for (int i = 0; i < PADDING + R; i++) {
    for (int j = 0; j < C; j++) {
      board[i][j] = 0;
      if (i < PADDING) {
        fairy_visited[i][j] = true;
      } else {
        fairy_visited[i][j] = false;
      }
    }
  }

  // Game (for each K golems & fairies)
  for (int golem_idx = 0; golem_idx < K; golem_idx++) {
    pair<int, int> golem_pos;
    int fairy_row;
    // Move golem to northest
    golem_pos = move_golem_to_southest(golem_idx);
    // // Check
    // cout << "GOLEM IDX: " << golem_idx << '\n';
    // for (int i = 0; i < PADDING + R; i++) {
    //   for (int j = 0; j < C; j++) {
    //     cout << board[i][j] << ' ';
    //   }
    //   cout << '\n';
    // }
    // cout << '\n';
    // Move fairy to northest
    fairy_row = move_fairy_to_southest(golem_pos);
    if (fairy_row == -1) {
      clear_board();
      continue;
    }
    // Increment the answer
    answer += (fairy_row - PADDING) + 1;
  }

  // Output
  cout << answer;

  return 0;
}

// Golem
pair<int, int> move_golem_to_southest(int golem_idx) {
  // Get initial position of given golem
  pair<int, int> cur_golem_pos = {INIT_ROW_IDX,
                                  golem_info[golem_idx].INIT_COLUMN_IDX};
  pair<int, int> moved_golem_pos = move_golem_once(golem_idx, cur_golem_pos);
  // Move golem until it can be moved
  while (moved_golem_pos.X != cur_golem_pos.X ||
         moved_golem_pos.Y != cur_golem_pos.Y) {
    cur_golem_pos = moved_golem_pos;
    moved_golem_pos = move_golem_once(golem_idx, cur_golem_pos);
  }

  return cur_golem_pos;
}

pair<int, int> move_golem_once(int golem_idx, pair<int, int> golem_pos) {
  pair<int, int> moved_golem_pos = golem_pos;

  // If already southest, then it can't be moved
  if (golem_pos.X == (PADDING + R - 1) - 1) return moved_golem_pos;

  // Check SOUTH and move if possible
  if (south_movable(golem_pos)) {
    // Erase golem
    erase_golem(golem_pos);

    // Draw CENTER
    moved_golem_pos.X++;
    board[moved_golem_pos.X][moved_golem_pos.Y] = CENTER;

    // Draw LEAF and EXIT_LEAF
    for (int i = 0; i < 4; i++) {
      int nx = moved_golem_pos.X + dx[i];
      int ny = moved_golem_pos.Y + dy[i];

      if (i == golem_info[golem_idx].EXIT) {
        board[nx][ny] = EXIT_LEAF;
        continue;
      }
      board[nx][ny] = LEAF;
    }

    return moved_golem_pos;
  }
  // Check WEST-SOUTH and rotate and move if possible
  if (west_south_movable(golem_pos)) {
    // Rotate golem(C.C.W.)
    if (golem_info[golem_idx].EXIT == 0) {
      golem_info[golem_idx].EXIT = 3;
    } else {
      golem_info[golem_idx].EXIT--;
    }

    // Erase golem
    erase_golem(golem_pos);

    // Draw CENTER
    moved_golem_pos.X++;
    moved_golem_pos.Y--;
    board[moved_golem_pos.X][moved_golem_pos.Y] = CENTER;

    // Draw LEAF and EXIT_LEAF
    for (int i = 0; i < 4; i++) {
      int nx = moved_golem_pos.X + dx[i];
      int ny = moved_golem_pos.Y + dy[i];

      if (i == golem_info[golem_idx].EXIT) {
        board[nx][ny] = EXIT_LEAF;
        continue;
      }
      board[nx][ny] = LEAF;
    }

    return moved_golem_pos;
  }
  // Check EAST-SOUTH and rotate and move if possible
  if (east_south_movable(golem_pos)) {
    // Rotate golem(C.W.)
    golem_info[golem_idx].EXIT = ((golem_info[golem_idx].EXIT + 1) % 4);

    // Erase golem
    erase_golem(golem_pos);

    // Draw CENTER
    moved_golem_pos.X++;
    moved_golem_pos.Y++;
    board[moved_golem_pos.X][moved_golem_pos.Y] = CENTER;

    // Draw LEAF and EXIT_LEAF
    for (int i = 0; i < 4; i++) {
      int nx = moved_golem_pos.X + dx[i];
      int ny = moved_golem_pos.Y + dy[i];

      if (i == golem_info[golem_idx].EXIT) {
        board[nx][ny] = EXIT_LEAF;
        continue;
      }
      board[nx][ny] = LEAF;
    }

    return moved_golem_pos;
  }

  return moved_golem_pos;
}

bool south_movable(pair<int, int> golem_pos) {
  return (board[golem_pos.X + 1][golem_pos.Y - 1] == 0 &&
          board[golem_pos.X + 2][golem_pos.Y] == 0 &&
          board[golem_pos.X + 1][golem_pos.Y + 1] == 0);
}

bool west_south_movable(pair<int, int> golem_pos) {
  // OOB?
  if ((golem_pos.X > (PADDING + R - 1) - 2) || (golem_pos.Y < 2)) return false;
  // Not all-zero?
  if (board[golem_pos.X - 1][golem_pos.Y - 1] != 0 ||
      board[golem_pos.X][golem_pos.Y - 2] != 0 ||
      board[golem_pos.X + 1][golem_pos.Y - 1] != 0 ||
      board[golem_pos.X + 1][golem_pos.Y - 2] != 0 ||
      board[golem_pos.X + 2][golem_pos.Y - 1] != 0)
    return false;

  return true;
}

bool east_south_movable(pair<int, int> golem_pos) {
  // OOB?
  if ((golem_pos.X > (PADDING + R - 1) - 2) || (golem_pos.Y > (C - 3)))
    return false;
  // Not all-zero?
  if (board[golem_pos.X - 1][golem_pos.Y + 1] != 0 ||
      board[golem_pos.X][golem_pos.Y + 2] != 0 ||
      board[golem_pos.X + 1][golem_pos.Y + 1] != 0 ||
      board[golem_pos.X + 1][golem_pos.Y + 2] != 0 ||
      board[golem_pos.X + 2][golem_pos.Y + 1] != 0)
    return false;

  return true;
}

void erase_golem(pair<int, int> golem_pos) {
  board[golem_pos.X][golem_pos.Y] = 0;
  for (int i = 0; i < 4; i++) {
    int nx = golem_pos.X + dx[i];
    int ny = golem_pos.Y + dy[i];

    board[nx][ny] = 0;
  }

  return;
}

// Fairy
int move_fairy_to_southest(pair<int, int> fairy_pos) {
  int fairy_row = -1;

  // If the golem is not fully contained in valid area,
  // then we don't move the fairy
  if (fairy_pos.X <= PADDING) return fairy_row;

  // BFS for fairy
  queue<pair<int, int>> Q;

  Q.push(fairy_pos);
  fairy_visited[fairy_pos.X][fairy_pos.Y] = true;
  while (!Q.empty()) {
    pair<int, int> cur = Q.front();
    Q.pop();

    // Case 1: CENTER
    if (board[cur.X][cur.Y] == CENTER) {
      for (int i = 0; i < 4; i++) {
        int nx = cur.X + dx[i];
        int ny = cur.Y + dy[i];

        if (nx < PADDING || nx >= PADDING + R || ny < 0 || ny >= C) continue;
        if (board[nx][ny] == 0 || fairy_visited[nx][ny]) continue;

        Q.push({nx, ny});
        fairy_visited[nx][ny] = true;
      }
    }
    // Case 2: LEAF
    else if (board[cur.X][cur.Y] == LEAF) {
      for (int i = 0; i < 4; i++) {
        int nx = cur.X + dx[i];
        int ny = cur.Y + dy[i];

        if (nx < PADDING || nx >= PADDING + R || ny < 0 || ny >= C) continue;
        if (board[nx][ny] == 0 || fairy_visited[nx][ny]) continue;

        if (board[nx][ny] == CENTER) {
          Q.push({nx, ny});
          fairy_visited[nx][ny] = true;
        }
      }
    }
    // Case 3: EXIT_LEAF
    else {
      for (int i = 0; i < 4; i++) {
        int nx = cur.X + dx[i];
        int ny = cur.Y + dy[i];

        if (nx < PADDING || nx >= PADDING + R || ny < 0 || ny >= C) continue;
        if (board[nx][ny] == 0 || fairy_visited[nx][ny]) continue;

        Q.push({nx, ny});
        fairy_visited[nx][ny] = true;
      }
    }
  }

  // Check southest row
  for (int i = (PADDING + R) - 1; i >= PADDING; i--) {
    for (int j = 0; j < C; j++) {
      if (fairy_visited[i][j]) {
        fairy_row = i;
        clear_fairy_visited();
        return fairy_row;
      }
    }
  }

  return fairy_row;
}

void clear_fairy_visited(void) {
  for (int i = PADDING; i < PADDING + R; i++) {
    for (int j = 0; j < C; j++) {
      fairy_visited[i][j] = false;
    }
  }

  return;
}

// Utils
void clear_board(void) {
  for (int i = 0; i < PADDING + R; i++) {
    for (int j = 0; j < C; j++) {
      board[i][j] = 0;
    }
  }

  return;
}

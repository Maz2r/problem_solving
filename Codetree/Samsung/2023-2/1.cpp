#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define X first
#define Y second

// Santa
#define DEAD -4
#define ALIVE -3

// Rudolf
#define R 31

int board[52][52];
int N;

int M;

// Santa
pair<int, int> pos_S[32];
int status[32];               // -4: DEAD, -3: ALIVE, t>=0: STUNNED at t-th turn
int score[32];                // Score(Answer)
int P;                        // Number
int D;                        // Power
int dx_S[4] = {-1, 0, 1, 0};  // Directions
int dy_S[4] = {0, 1, 0, -1};

// Rudolf
pair<int, int> pos_R;
int C;                                      // Power
int dx_R[8] = {1, 1, 1, 0, 0, -1, -1, -1};  // Directions
int dy_R[8] = {1, 0, -1, 1, -1, 1, 0, -1};

// Functions
// Santa
void move_Santas(int turn);
void S2S(pair<int, int> pos, pair<int, int> dir);
void S2R(pair<int, int> pos, pair<int, int> dir, int turn);
// Rudolf
int find_idx_nearest_Santa(void);
void move_Rudolf(pair<int, int> pos_nearest_Santa, int turn);
void R2S(pair<int, int> pos, pair<int, int> dir, int turn);

// Utils
int distance(pair<int, int> pos1, pair<int, int> pos2);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Get basic params
  cin >> N >> M >> P >> C >> D;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = 0;
    }
  }

  // Get Rudolf
  cin >> pos_R.X >> pos_R.Y;
  pos_R.X--;
  pos_R.Y--;
  board[pos_R.X][pos_R.Y] = R;

  // Get Santas
  for (int i = 0; i < P; i++) {
    int index;
    cin >> index;
    cin >> pos_S[index - 1].X >> pos_S[index - 1].Y;
    pos_S[index - 1].X--;
    pos_S[index - 1].Y--;
    board[pos_S[index - 1].X][pos_S[index - 1].Y] = index;
    status[i] = ALIVE;
    score[i] = 0;
  }

  // Game
  for (int turn = 0; turn < M; turn++) {
    // Wake up Santas
    for (int i = 0; i < P; i++) {
      if ((status[i] == DEAD) || (status[i] == ALIVE) ||
          (status[i] == turn - 1))
        continue;
      status[i] = ALIVE;
    }

    // Rudolf phase
    // Find nearest Santa
    int idx_nearest_Santa = find_idx_nearest_Santa();
    if (idx_nearest_Santa == 0) break;  // No Santa on the board
    pair<int, int> pos_nearest_Santa = pos_S[idx_nearest_Santa - 1];

    // Move Rudolf
    move_Rudolf(pos_nearest_Santa, turn);

    // Santa phase
    // Move Santas
    move_Santas(turn);

    // Additional score for survivors
    for (int i = 0; i < P; i++) {
      if (!(status[i] == DEAD)) score[i]++;
    }
  }

  for (int i = 0; i < P; i++) {
    cout << score[i] << ' ';
  }

  return 0;
}

// Santa
void move_Santas(int turn) {
  for (int i = 0; i < P; i++) {
    if ((status[i] == DEAD) || (status[i] >= 0)) continue;

    int dir_min = -1;
    int dist_min = 10000;
    int dist = distance(pos_S[i], pos_R);
    // Decide direction
    for (int dir = 0; dir < 4; dir++) {
      int nx = pos_S[i].X + dx_S[dir];
      int ny = pos_S[i].Y + dy_S[dir];

      if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
      if ((board[nx][ny] != 0) && (board[nx][ny] != R)) continue;
      int ndist = distance({nx, ny}, pos_R);
      if (ndist >= dist) continue;

      if (ndist >= dist_min) continue;

      dir_min = dir;
      dist_min = ndist;
    }
    if (dir_min == -1) continue;

    // Move
    int nx = pos_S[i].X + dx_S[dir_min];
    int ny = pos_S[i].Y + dy_S[dir_min];

    if (board[nx][ny] == R)
      S2R(pos_S[i], {dx_S[dir_min], dy_S[dir_min]}, turn);
    else {
      board[nx][ny] = board[pos_S[i].X][pos_S[i].Y];
      board[pos_S[i].X][pos_S[i].Y] = 0;
      pos_S[i] = {nx, ny};
    }
  }

  return;
}

void S2S(pair<int, int> pos, pair<int, int> dir) {
  int idx_S = board[pos.X][pos.Y] - 1;

  // Hit Santa
  int nx = pos.X + dir.X;
  int ny = pos.Y + dir.Y;

  if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
    board[pos.X][pos.Y] = 0;
    pos_S[idx_S] = {-1, -1};
    status[idx_S] = DEAD;

    return;
  }
  if (board[nx][ny] != 0) S2S({nx, ny}, dir);

  board[nx][ny] = board[pos.X][pos.Y];
  board[pos.X][pos.Y] = 0;
  pos_S[idx_S] = {nx, ny};

  return;
}

void S2R(pair<int, int> pos, pair<int, int> dir, int turn) {
  int idx_S = board[pos.X][pos.Y] - 1;
  board[pos.X][pos.Y] = 0;

  // Increase score for the Santa
  score[idx_S] += D;

  // Hit Santa
  int nx = pos_R.X + ((-1) * dir.X * D);
  int ny = pos_R.Y + ((-1) * dir.Y * D);

  if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
    pos_S[idx_S] = {-1, -1};
    status[idx_S] = DEAD;

    return;
  }
  if (board[nx][ny] != 0) S2S({nx, ny}, {(-1) * dir.X, (-1) * dir.Y});

  board[nx][ny] = idx_S + 1;
  pos_S[idx_S] = {nx, ny};
  status[idx_S] = turn;

  return;
}

// Rudolf
int find_idx_nearest_Santa(void) {
  int idx_nearest_Santa = 0;
  int dist_nearest_Santa = 10000;

  for (int i = 0; i < P; i++) {
    if (status[i] == DEAD) continue;
    int dist = distance(pos_R, pos_S[i]);
    if (dist > dist_nearest_Santa) continue;

    if (dist < dist_nearest_Santa) {
      idx_nearest_Santa = i + 1;
      dist_nearest_Santa = dist;
    } else {
      if (pos_S[i].X > pos_S[idx_nearest_Santa - 1].X) {
        idx_nearest_Santa = i + 1;
        dist_nearest_Santa = dist;
      } else if (pos_S[i].X == pos_S[idx_nearest_Santa - 1].X) {
        if (pos_S[i].Y > pos_S[idx_nearest_Santa - 1].Y) {
          idx_nearest_Santa = i + 1;
          dist_nearest_Santa = dist;
        }
      }
    }
  }

  return idx_nearest_Santa;
}

void move_Rudolf(pair<int, int> pos_nearest_Santa, int turn) {
  // Decide direction
  int dx, dy;
  // X?
  if (pos_nearest_Santa.X > pos_R.X)
    dx = 1;
  else if (pos_nearest_Santa.X == pos_R.X)
    dx = 0;
  else
    dx = -1;
  // Y?
  if (pos_nearest_Santa.Y > pos_R.Y)
    dy = 1;
  else if (pos_nearest_Santa.Y == pos_R.Y)
    dy = 0;
  else
    dy = -1;

  // Move
  int nx = pos_R.X + dx;
  int ny = pos_R.Y + dy;

  if (board[nx][ny] != 0) R2S({nx, ny}, {dx, dy}, turn);

  board[nx][ny] = R;
  board[pos_R.X][pos_R.Y] = 0;
  pos_R = {nx, ny};

  return;
}

void R2S(pair<int, int> pos, pair<int, int> dir, int turn) {
  int idx_S = board[pos.X][pos.Y] - 1;

  // Increase score for the Santa
  score[idx_S] += C;

  // Hit Santa
  int nx = pos.X + (dir.X * C);
  int ny = pos.Y + (dir.Y * C);

  if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
    board[pos.X][pos.Y] = 0;
    pos_S[idx_S] = {-1, -1};
    status[idx_S] = DEAD;

    return;
  }
  if (board[nx][ny] != 0) S2S({nx, ny}, dir);

  board[nx][ny] = board[pos.X][pos.Y];
  board[pos.X][pos.Y] = 0;
  pos_S[idx_S] = {nx, ny};
  status[idx_S] = turn;

  return;
}

// Utils
int distance(pair<int, int> pos1, pair<int, int> pos2) {
  return (pos1.X - pos2.X) * (pos1.X - pos2.X) +
         (pos1.Y - pos2.Y) * (pos1.Y - pos2.Y);
}

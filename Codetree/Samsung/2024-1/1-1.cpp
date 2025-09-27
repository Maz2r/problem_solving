#include <iostream>
#include <utility>

using namespace std;

#define BOARD_SIZE 5

#define X first
#define Y second

int board[7][7];
bool visited[7][7];
bool visited_for_deletion[7][7];
int rotate_degree[3] = {90, 180, 270};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int wall_number[302];
int M;
int wall_number_idx = 0;

int K;
int score_of_the_turn = 0;

// Search
bool search_and_rotate(void);
int calculate_score(void);
int calculate_block_score(pair<int, int> pos, int treasure_num);
// Acquire
bool acquire(void);
void delete_the_block(pair<int, int> pos, int treasure_num);
void fill_the_board(void);

// Utils
void rotate_the_board(pair<int, int> pos_center, int degree);
void unrotate_the_board(pair<int, int> pos_center, int degree);
void clear_the_visited(void);
void clear_the_visited_for_deletion(void);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Input & Initialization
  cin >> K >> M;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      cin >> board[i][j];
      visited[i][j] = false;
      visited_for_deletion[i][j] = false;
    }
  }
  for (int i = 0; i < M; i++) {
    cin >> wall_number[i];
  }

  // Game (K turns)
  for (int turn = 0; turn < K; turn++) {
    score_of_the_turn = 0;
    // Search and rotate(by the best center and degree)
    if (!search_and_rotate()) break;
    // Acquire
    while (acquire()) {
      // Fill the board(with the wall numbers)
      fill_the_board();
    }
    // Output(score for each turn)
    cout << score_of_the_turn << ' ';
  }

  return 0;
}

// Search
// Search the best center and degree w.r.t. the acquired score
// and rotate by the best center and degree
bool search_and_rotate(void) {
  // Simulate each center and degree
  // to get the best center and degree w.r.t. the aquired score
  pair<int, int> pos_best_center = {-1, -1};
  int best_degree = -1;
  int best_score = -1;

  for (int k = 0; k < 3; k++) {
    for (int j = 1; j < BOARD_SIZE - 1; j++) {
      for (int i = 1; i < BOARD_SIZE - 1; i++) {
        pair<int, int> pos_center = {i, j};
        rotate_the_board(pos_center, rotate_degree[k]);
        int score = calculate_score();
        if (score == 0 || (score <= best_score)) {
          unrotate_the_board(pos_center, rotate_degree[k]);
          continue;
        }
        pos_best_center = pos_center;
        best_degree = rotate_degree[k];
        best_score = score;
        unrotate_the_board(pos_center, rotate_degree[k]);
      }
    }
  }
  if (pos_best_center.X == -1 && pos_best_center.Y == -1) return false;

  // Rotate by the best center and degree
  rotate_the_board(pos_best_center, best_degree);

  return true;
}

int calculate_score(void) {
  int score = 0;

  // Calculate block score for each block
  // and if block score is >= 3, then increment the score
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (visited[i][j]) continue;
      int block_score = calculate_block_score({i, j}, board[i][j]);
      if (block_score < 3) continue;
      score += block_score;
    }
  }
  clear_the_visited();

  return score;
}

int calculate_block_score(pair<int, int> pos, int treasure_num) {
  int block_score = 1;

  visited[pos.X][pos.Y] = true;
  for (int i = 0; i < 4; i++) {
    int nx = pos.X + dx[i];
    int ny = pos.Y + dy[i];

    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) continue;
    if ((board[nx][ny] != treasure_num) || visited[nx][ny]) continue;

    block_score += calculate_block_score({nx, ny}, treasure_num);
  }

  return block_score;
}

// Acquire
// Acquire and increment the score(if acquired)
bool acquire(void) {
  int score = 0;

  // Calculate block score for each block
  // and if block score is >= 3, then delete the block add the score
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (visited[i][j]) continue;
      int block_score = calculate_block_score({i, j}, board[i][j]);
      if (block_score < 3) continue;
      delete_the_block({i, j}, board[i][j]);
      score += block_score;
    }
  }
  clear_the_visited();
  clear_the_visited_for_deletion();

  if (score == 0) return false;

  score_of_the_turn += score;

  return true;
}

// Delete the block starting from the given position
void delete_the_block(pair<int, int> pos, int treasure_num) {
  board[pos.X][pos.Y] = 0;
  visited_for_deletion[pos.X][pos.Y] = true;
  for (int i = 0; i < 4; i++) {
    int nx = pos.X + dx[i];
    int ny = pos.Y + dy[i];

    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) continue;
    if ((board[nx][ny] != treasure_num) || visited_for_deletion[nx][ny])
      continue;

    delete_the_block({nx, ny}, treasure_num);
  }

  return;
}

// Fill the board with the wall numbers
// and reset the index of wall numbers
void fill_the_board(void) {
  for (int j = 0; j < BOARD_SIZE; j++) {
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
      if (board[i][j] != 0) continue;
      board[i][j] = wall_number[wall_number_idx];
      wall_number_idx++;
    }
  }

  return;
}

// Utils
void rotate_the_board(pair<int, int> pos_center, int degree) {
  int x = pos_center.X;
  int y = pos_center.Y;

  int corner[4] = {board[x - 1][y - 1], board[x - 1][y + 1],
                   board[x + 1][y + 1], board[x + 1][y - 1]};
  int bridge[4] = {board[x - 1][y], board[x][y + 1], board[x + 1][y],
                   board[x][y - 1]};

  if (degree == 90) {
    // Corners
    board[x - 1][y - 1] = corner[3];
    board[x - 1][y + 1] = corner[0];
    board[x + 1][y + 1] = corner[1];
    board[x + 1][y - 1] = corner[2];
    // Bridges
    board[x - 1][y] = bridge[3];
    board[x][y + 1] = bridge[0];
    board[x + 1][y] = bridge[1];
    board[x][y - 1] = bridge[2];
  } else if (degree == 180) {
    // Corners
    board[x - 1][y - 1] = corner[2];
    board[x - 1][y + 1] = corner[3];
    board[x + 1][y + 1] = corner[0];
    board[x + 1][y - 1] = corner[1];
    // Bridges
    board[x - 1][y] = bridge[2];
    board[x][y + 1] = bridge[3];
    board[x + 1][y] = bridge[0];
    board[x][y - 1] = bridge[1];
  } else {
    // Corners
    board[x - 1][y - 1] = corner[1];
    board[x - 1][y + 1] = corner[2];
    board[x + 1][y + 1] = corner[3];
    board[x + 1][y - 1] = corner[0];
    // Bridges
    board[x - 1][y] = bridge[1];
    board[x][y + 1] = bridge[2];
    board[x + 1][y] = bridge[3];
    board[x][y - 1] = bridge[0];
  }

  return;
}

void unrotate_the_board(pair<int, int> pos_center, int degree) {
  int x = pos_center.X;
  int y = pos_center.Y;

  int corner[4] = {board[x - 1][y - 1], board[x - 1][y + 1],
                   board[x + 1][y + 1], board[x + 1][y - 1]};
  int bridge[4] = {board[x - 1][y], board[x][y + 1], board[x + 1][y],
                   board[x][y - 1]};

  if (degree == 90) {
    // Corners
    board[x - 1][y - 1] = corner[1];
    board[x - 1][y + 1] = corner[2];
    board[x + 1][y + 1] = corner[3];
    board[x + 1][y - 1] = corner[0];
    // Bridges
    board[x - 1][y] = bridge[1];
    board[x][y + 1] = bridge[2];
    board[x + 1][y] = bridge[3];
    board[x][y - 1] = bridge[0];
  } else if (degree == 180) {
    // Corners
    board[x - 1][y - 1] = corner[2];
    board[x - 1][y + 1] = corner[3];
    board[x + 1][y + 1] = corner[0];
    board[x + 1][y - 1] = corner[1];
    // Bridges
    board[x - 1][y] = bridge[2];
    board[x][y + 1] = bridge[3];
    board[x + 1][y] = bridge[0];
    board[x][y - 1] = bridge[1];
  } else {
    // Corners
    board[x - 1][y - 1] = corner[3];
    board[x - 1][y + 1] = corner[0];
    board[x + 1][y + 1] = corner[1];
    board[x + 1][y - 1] = corner[2];
    // Bridges
    board[x - 1][y] = bridge[3];
    board[x][y + 1] = bridge[0];
    board[x + 1][y] = bridge[1];
    board[x][y - 1] = bridge[2];
  }

  return;
}

void clear_the_visited(void) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      visited[i][j] = false;
    }
  }

  return;
}

void clear_the_visited_for_deletion(void) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      visited_for_deletion[i][j] = false;
    }
  }

  return;
}

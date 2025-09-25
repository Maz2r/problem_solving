#include <iostream>

using namespace std;

int board[20][20];
int N;

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int func(int nx);
void visit(int x, int y);
void devisit(int x, int y);

int main(void) {
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = 0;
    }
  }

  cout << func(0) << '\n';

  return 0;
}

int func(int nx) {
  int answer = 0;

  // Base case
  if (nx == N - 1) {
    for (int i = 0; i < N; i++) {
      if (board[nx][i] > 0) continue;
      answer++;
    }

    return answer;
  }

  for (int i = 0; i < N; i++) {
    if (board[nx][i] > 0) continue;
    visit(nx, i);
    answer += func(nx + 1);
    devisit(nx, i);
  }

  return answer;
}

void visit(int x, int y) {
  board[x][y]++;
  for (int dir = 0; dir < 8; dir++) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
      board[nx][ny]++;
      nx += dx[dir];
      ny += dy[dir];
    }
  }

  return;
}

void devisit(int x, int y) {
  board[x][y]--;
  for (int dir = 0; dir < 8; dir++) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
      board[nx][ny]--;
      nx += dx[dir];
      ny += dy[dir];
    }
  }

  return;
}

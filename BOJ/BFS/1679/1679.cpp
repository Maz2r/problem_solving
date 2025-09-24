#include <iostream>
#include <queue>

using namespace std;

bool vis[100002] = {false};
int dist[100002];
int N, K;

int dx[3] = {-1, 1, 2};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> K;
  if (N >= K) {
    cout << N - K;

    return 0;
  }

  queue<int> Q;

  Q.push(N);
  vis[N] = true;
  while (!Q.empty()) {
    int cur = Q.front();
    Q.pop();

    for (int i = 0; i < 3; i++) {
      int nx = cur;

      if (i == 2) {
        nx = cur * dx[i];
      } else {
        nx = cur + dx[i];
      }

      if (nx < 0 || nx >= 100002) continue;
      if (vis[nx]) continue;

      if (nx == K) {
        cout << dist[cur] + 1;

        return 0;
      }
      Q.push(nx);
      vis[nx] = true;
      dist[nx] = dist[cur] + 1;
    }
  }

  return 0;
}

#include <iostream>
#include <queue>

using namespace std;

int T;

int vote[100003];
int ns_s[100003];
bool visited[100003];

int n;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> T;
  for (int i = 0; i < T; i++) {
    int answer = 0;

    cin >> n;
    // Review Note: Index랑 번호 잘 통일하기. 흔히 나오는 트릭(?).
    for (int j = 1; j <= n; j++) {
      cin >> vote[j];
      ns_s[j] = 0;
      visited[j] = false;
    }

    for (int j = 1; j <= n; j++) {
      if (ns_s[j] == -1 || ns_s[j] == 1) continue;

      queue<int> Q;
      bool done = false;

      visited[j] = true;
      Q.push(j);
      while (!Q.empty() && !done) {
        int cur = Q.front();
        Q.pop();

        int nex = vote[cur];

        if (ns_s[nex] == -1 || ns_s[nex] == 1) {
          int cur_ns = j;
          while (true) {
            answer++;
            ns_s[cur_ns] = -1;
            if (cur_ns == cur) break;
            cur_ns = vote[cur_ns];
          }
          done = true;
          continue;
        }
        if (visited[nex]) {
          if (j != nex) {
            int cur_ns = j;
            while (true) {
              answer++;
              ns_s[cur_ns] = -1;
              if (vote[cur_ns] == nex) break;
              cur_ns = vote[cur_ns];
            }
          }

          int cur_s = nex;
          while (true) {
            ns_s[cur_s] = 1;
            if (cur_s == cur) break;
            cur_s = vote[cur_s];
          }
          done = true;
          continue;
        }

        visited[nex] = true;
        Q.push(nex);
      }
    }

    cout << answer << '\n';
  }

  return 0;
}

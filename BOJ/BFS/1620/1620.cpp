#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> ency_1;
string ency_2[100003];

int N, M;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    cin >> ency_2[i];
    ency_1[ency_2[i]] = i;
  }
  for (int i = 0; i < M; i++) {
    string query;

    cin >> query;
    if (isdigit(query[0])) {
      cout << ency_2[stoi(query)] << '\n';
    } else {
      cout << ency_1[query] << '\n';
    }
  }

  return 0;
}

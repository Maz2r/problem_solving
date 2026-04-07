#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> note;
int N, M;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> M;
  string site;
  string pwd;
  for (int i = 0; i < N; i++) {
    cin >> site;
    cin >> pwd;
    note[site] = pwd;
  }
  string query;
  for (int i = 0; i < M; i++) {
    cin >> query;
    cout << note[query] << '\n';
  }

  return 0;
}

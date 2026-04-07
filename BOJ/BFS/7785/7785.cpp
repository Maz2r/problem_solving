#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<string> current_workers;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;

  cin >> n;
  for (int i = 0; i < n; i++) {
    string name, log;

    cin >> name >> log;

    if (log == "enter") {
      current_workers.insert(name);
    } else {
      current_workers.erase(name);
    }
  }

  vector<string> answer(current_workers.begin(), current_workers.end());

  sort(answer.begin(), answer.end(), greater<string>());
  for (vector<string>::iterator iter = answer.begin(); iter != answer.end();
       iter++) {
    cout << (*iter) << '\n';
  }

  return 0;
}

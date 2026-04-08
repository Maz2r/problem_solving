#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int test_case;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    unordered_map<string, int> closet;
    int n;

    cin >> n;
    string clothing;
    string cate;
    for (int j = 0; j < n; j++) {
      cin >> clothing >> cate;
      closet[cate]++;
    }
    int answer = 1;
    unordered_map<string, int>::iterator iter;
    for (iter = closet.begin(); iter != closet.end(); iter++) {
      answer *= (*iter).second + 1;
    }

    cout << answer - 1 << '\n';
  }

  return 0;
}

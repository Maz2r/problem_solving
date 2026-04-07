#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

unordered_map<string, int> Q;
int K, L;

bool cmp(pair<string, int>& a, pair<string, int>& b);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> K >> L;
  for (int i = 0; i < L; i++) {
    string student;

    cin >> student;
    Q[student] = i;
  }

  vector<pair<string, int>> final_Q(Q.begin(), Q.end());
  sort(final_Q.begin(), final_Q.end(), cmp);

  int enrolled_num = 0;
  for (vector<pair<string, int>>::iterator iter = final_Q.begin();
       iter != final_Q.end(); iter++) {
    cout << (*iter).first << '\n';
    enrolled_num++;
    if (enrolled_num >= K) break;
  }

  return 0;
}

bool cmp(pair<string, int>& a, pair<string, int>& b) {
  return a.second <= b.second;
}

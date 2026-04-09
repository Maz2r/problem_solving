#include <iostream>

using namespace std;

int lottery[15];
int S[15];
bool is_issued[15];
int k;

void func(int selected);

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  while (true) {
    cin >> k;
    if (k == 0) break;

    for (int i = 0; i < k; i++) {
      cin >> S[i];
      is_issued[i] = false;
    }

    func(0);
    cout << '\n';
  }

  return 0;
}

void func(int selected) {
  if (selected == 6) {
    for (int i = 0; i < 6; i++) {
      cout << lottery[i] << ' ';
    }
    cout << '\n';

    return;
  }

  for (int i = 0; i < k; i++) {
    if (selected != 0 && S[i] <= lottery[selected - 1]) continue;
    if (k - i < 6 - selected) break;

    lottery[selected] = S[i];
    is_issued[i] = true;
    func(selected + 1);
    is_issued[i] = false;
  }

  return;
}

#include <iostream>

#include <vector>

using namespace std;

void console_output(vector < vector < int >> world) {
  for (int i = 1; i < (int) world.size() - 1; i++) {
    for (int j = 1; j < (int) world.at(0).size() - 1; j++)
      cout << (world.at(i).at(j) == 1 ? "o" : ".") << " ";
    cout << '\n';
  }
  cout << '\n';
}

vector < vector < int >> init_world(int height, int width) {
  vector < vector < int >> world(height + 2, vector < int > (width + 2, 0));
  while (true) {
    int a, b;
    cout << "pairs of natural numbers to determine height and width of living cells / integer <= 0 to start simulation \n";
    console_output(world);
    if (!(cin >> a)) {
      cin.clear();
      cin.ignore();
      cout << "only digits as input allowed";
      continue;
    }
    if (a < 1) break;
    if (a > height) {
      cout << "enter height less or equal to " << height << '\n';
      continue;
    }
    if (!(cin >> b)) {
      cin.clear();
      cin.ignore();
      cout << "only digits as input allowed";
      continue;
    }
    if (b < 1) break;
    if (b > width) {
      cout << "enter width less or equal to " << width << '\n';
      continue;
    }
    world.at(a).at(b) == 0 ? world.at(a).at(b) = 1 : world.at(a).at(b) = 0;
  }
  return world;
}

vector < vector < int >> simulate(vector < vector < int >> world) {
  vector < vector < int >> nextgen_world(world.size(), vector < int > (world.at(0).size(), 0));
  for (int i = 1; i < (int) world.size() - 1; i++) {
    for (int j = 1; j < (int) world.at(0).size() - 1; j++) {
      int neighbours {
        0
      };
      if (world.at(i - 1).at(j - 1) == 1) neighbours++;
      if (world.at(i - 1).at(j) == 1) neighbours++;
      if (world.at(i - 1).at(j + 1) == 1) neighbours++;
      if (world.at(i).at(j - 1) == 1) neighbours++;
      if (world.at(i).at(j + 1) == 1) neighbours++;
      if (world.at(i + 1).at(j - 1) == 1) neighbours++;
      if (world.at(i + 1).at(j) == 1) neighbours++;
      if (world.at(i + 1).at(j + 1) == 1) neighbours++;

      if (world.at(i).at(j) == 0) {
        if (neighbours == 3) {
          nextgen_world.at(i).at(j) = 1;
          continue;
        }
        nextgen_world.at(i).at(j) = 0;
        continue;
      }
      if (world.at(i).at(j) == 1) {
        if (neighbours == 2 || neighbours == 3) {
          nextgen_world.at(i).at(j) = 1;
          continue;
        }
        nextgen_world.at(i).at(j) = 0;
        continue;
      }
    }
  }
  console_output(nextgen_world);
  if (world != nextgen_world) {
    while (true) {
      char c {
        ' '
      };
      cout << "continue simulation ? y / n\n";
      cin >> c;
      if (c == 'y') return simulate(nextgen_world);
      if (c == 'n') return nextgen_world;
    }
  }
  return nextgen_world;
}

int main() {
  while (true) {
    int n, m;
    cout << "world height as natural number / integer <= 0 to close app \n";
    if (!(cin >> n)) {
      cin.clear();
      cin.ignore();
      continue;
    }
    if (n < 1) break;
    cout << "world width as natural number / integer <= 0 to close app  \n";
    if (!(cin >> m)) {
      cin.clear();
      cin.ignore();
      continue;
    }
    if (m < 1) break;
    simulate(init_world(n, m));
  }
  return 0;
}

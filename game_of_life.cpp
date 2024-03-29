#include <iostream>

#include <vector>

using namespace std;

void console_output(vector < vector < int >> world) {
  for (int i = 1; i < (int) world.size() - 1; i++) {
    for (int j = 1; j < (int) world.at(0).size() - 1; j++)
      cout << (world.at(i).at(j) == 1 ? "o" : ".") << " ";
    cout << '\n';
  }
}

vector < vector < int >> alter_world(vector < vector < int >> world) {
  vector < vector < int >> altered_world = world;
  while (true) {
    int a, b;
    cout << "pairs of natural numbers to determine height and width of living cells / integer <= 0 to start simulation \n";
    console_output(altered_world);
    if (!(cin >> a)) {
      cin.clear();
      cin.ignore();
      cout << "only integers as input allowed";
      continue;
    }
    if (a < 1) break;
    if (a > (int) world.size() - 2) {
      cout << "enter height less or equal to " << world.size() - 2 << '\n';
      continue;
    }
    if (!(cin >> b)) {
      cin.clear();
      cin.ignore();
      cout << "only integers as input allowed";
      continue;
    }
    if (b < 1) break;
    if (b > (int) world.at(0).size() - 2) {
      cout << "enter width less or equal to " << world.at(0).size() - 2 << '\n';
      continue;
    }
    altered_world.at(a).at(b) == 0 ? altered_world.at(a).at(b) = 1 : altered_world.at(a).at(b) = 0;
  }
  return altered_world;
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
      cout << "enter 'y' to continue simulation / enter 'a' to alter world / enter 'n' to stop\n";
      cin >> c;
      if (c == 'y') return simulate(nextgen_world);
      if (c == 'n') return nextgen_world;
      if (c == 'a') return simulate(alter_world(nextgen_world));
    }
  }
  return nextgen_world;
}

int main() {
  vector < vector < int >> world;
  while (true) {
    int n, m;
    cout << "world height as natural number / -1 to load previous world / 0 to close app \n";
    if (!(cin >> n)) {
      cin.clear();
      cin.ignore();
      continue;
    }
    if (n == 0) break;
    if (n == -1) {
      if (!world.empty()) {
        world = alter_world(world);
        simulate(world);
      }
      continue;
    }
    if (n < -1) continue;
    cout << "world width as natural number / -1 to load previous world / 0 to close app  \n";
    if (!(cin >> m)) {
      cin.clear();
      cin.ignore();
      continue;
    }
    if (m == 0) break;
    if (m == -1) {
      if (!world.empty()) {
        world = alter_world(world);
        simulate(world);
      }
      continue;
    }
    if (m < -1) continue;
    vector < vector < int >> new_world(n + 2, vector < int > (m + 2, 0));
    world = alter_world(new_world);
    simulate(world);
  }
  return 0;
}

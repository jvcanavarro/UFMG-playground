#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

int shortest_path(int a, int b) {
    if (a == b) {
        return 0;
    }

    queue<int> queue;
    unordered_set<int> visited;
    int distance = 0;

    queue.push(a);
    visited.insert(a);

    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            int node = queue.front();
            queue.pop();

            int neighbor1 = node + 1;
            string temp = to_string(node);
            reverse(temp.begin(), temp.end());
            int neighbor2 = stoi(temp);

            if (neighbor1 == b || neighbor2 == b) {
                return distance + 1;
            }

            if (visited.find(neighbor1) == visited.end() && neighbor1 < 10000) {
                visited.insert(neighbor1);
                queue.push(neighbor1);
            }

            if (visited.find(neighbor2) == visited.end() && neighbor2 < 10000) {
                visited.insert(neighbor2);
                queue.push(neighbor2);
            }
        }

        distance++;
    }

    return -1;
}

int main() {
    int n_tests;
    cin >> n_tests;
    cin.ignore(); // Ignore the remaining newline character after reading n_tests

    for (int i = 0; i < n_tests; ++i) {
        int a, b;
        cin >> a >> b;
        cout << shortest_path(a, b) << endl;
    }

    return 0;
}
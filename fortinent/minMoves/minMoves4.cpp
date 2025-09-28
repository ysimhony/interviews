#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>

using namespace std;


    long long encode(int row, int col) {
        return ((long long)row << 32) | col;
    }
int minMoves(int n, int startRow, int startCol, int endRow, int endCol) {
    // All possible knight moves
    vector<pair<int, int>> directions = {
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
        {1, 2}, {2, 1}, {2, -1}, {1, -2}
    };


    unordered_set<long> visited;
    /*
	We use queue, which is STL FIFO enforced by the CPP lib.
	In the underlying, it uses deque, which is double-ended queue,
	which allows to push/pop both front and back.

	Note that we store the number of steps in the queue,
	and not the whole path
    */
    queue<pair<pair<int, int>, int>> q; // ((row, col), steps)

    q.push({{startRow, startCol}, 0});

    visited.insert(encode(startRow, startCol));
    while (!q.empty()) {
        auto [pos, steps] = q.front();
        q.pop();

        int row = pos.first;
        int col = pos.second;

        if (row == endRow && col == endCol) {
            return steps;
        }

        for (auto [dr, dc] : directions) {
            int newRow = row + dr;
            int newCol = col + dc;

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n) {
                pair<int, int> next = {newRow, newCol};
                if (visited.find(encode(newRow, newCol)) == visited.end()) {
                    visited.insert(encode(newRow, newCol));
                    q.push({next, steps + 1});
                }
            }
        }
    }

    return -1; // Not reachable
}
int main() {
    int res = minMoves(7, 6, 6, 0, 1);

    cout << "result = " << res << endl;
}


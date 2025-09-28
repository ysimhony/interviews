using namespace std;

#include <iostream>
#include <set>
#include <vector>


/*
Comments are:
1. No need to track the whole path. it is enough to track the number of 
steps so far.
2.
vector<vector<int>> newPath = path;
This line is too expensive
3. 
set<vector<int>> visited;
  a. unordered_set would be better.
  b. pair is faster than vector
*/
int minMoves(int n, int startRow, int startCol, int endRow, int endCol) {
        set<vector<int>> visited;
        vector<vector<vector<int>>> queue;
        vector<vector<int>> directions = 
        { {-1, -2}, 
          {-2, -1}, {-2, 1}, {-1, 2}, 
            {1, 2}, {2, 1}, {2, -1}, {1, -2} };


        queue.push_back({ { startRow, startCol } });

        while (!queue.empty()) {

            vector<vector<int>> path = queue.front();
            queue.erase(queue.begin());
            vector<int> last = path.back();

            if (last[0] == endRow && last[1] == endCol) {
                return path.size() - 1;
            }
            

            visited.insert(last);

            for (auto direction : directions) {

                vector<int> newPoint = { last[0] + direction[0], last[1] + direction[1] };

                if (visited.find(newPoint) != visited.end()) {
                    continue;
                }
                if (newPoint[0] < 0 || newPoint[0] >= n) {
                    continue;
                }
                if (newPoint[1] < 0 || newPoint[1] >= n) {
                    continue;
                }

                vector<vector<int>> newPath = path;
                newPath.push_back(newPoint);

                queue.push_back(newPath);

            }
        }

        return -1;

}


int main() {
    int res = minMoves(7, 6, 6, 0, 1);

    cout << "result = " << res << endl;
}


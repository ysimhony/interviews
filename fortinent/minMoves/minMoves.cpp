using namespace std;

#include <iostream>
#include <list>
#include <tuple>
#include <set>
#include <deque>
int minMoves(int n, int startRow, int startCol, int endRow, int endCol) {

    list<tuple<int, int>> directions = { make_tuple(-1, -2), make_tuple(-2, -1), make_tuple(-2, 1), make_tuple(-1, 2), make_tuple(1, 2), make_tuple(2, 1), make_tuple(2, -1), make_tuple(1, -2) };
    set<tuple<int, int>> visited;
        
    deque<list<tuple<int, int>>> queue;

    queue.push_back ({ make_tuple(startRow, startCol) });

    while (!queue.empty()) {

        list<tuple<int, int>> path = queue.front();
        queue.pop_front();
        tuple<int, int> position = *path.rbegin();

        if (get<0>(position) == endRow && get<1>(position) == endCol) {
            return path.size() - 1;
        }

        if (visited.find(position) == visited.end()) {
            visited.insert(position);

            for (tuple<int, int> direction : directions) {

                tuple<int, int> new_pos = make_tuple(get<0>(position) + get<0>(direction), get<1>(position) + get<1>(direction));

                if (get<0>(new_pos) < 0 || get<0>(new_pos) >= n) {
                    continue;
                }

                if (get<1>(new_pos) < 0 || get<1>(new_pos) >= n) {
                    continue;
                }

                list<tuple<int, int>> new_path = path;
                new_path.push_back(new_pos);
                queue.push_back(new_path);


            }
        }

    }


    return -1;
}


int main() {
    int res = minMoves(7, 6, 6, 0, 1);

    cout << "result = " << res << endl;
}


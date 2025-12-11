#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    void CountingStars(vector<vector<int>>& stars_indexes_arr) {

/*
priority_queue<
    tuple<int,int,int>,
    vector<tuple<int,int,int>>,
    greater<tuple<int,int,int>>
> pq;
*/
        priority_queue<     tuple<int,int,int>, 
                            vector<tuple<int,int,int>>, 
                            greater<tuple<int,int,int>>
                    > pq;

        int m = stars_indexes_arr.size();
        int n = stars_indexes_arr[0].size();

        for (int i = 0; i < m; i++) {
            pq.push({ stars_indexes_arr[i][0], i, 0 });
        }

        int count = 0;
        int prev = INT_MAX;
        int val;

        while (!pq.empty()) {
            tuple<int, int, int> elem = pq.top();
            pq.pop();

            val = get<0>(elem);
            int row = get<1>(elem);
            int col = get<2>(elem);

            if (col + 1 < n) {
                pq.push({ stars_indexes_arr[row][col + 1], row, col + 1 });
            }

            if (prev != val) {
                if (count % 2 == 1 && prev != INT_MAX) {
                    cout << prev << endl;
                }
                count = 1;
            }
            else {
                count += 1;
            }

            prev = val;
        }

        if (count % 2 == 1) {
            cout << val << endl;
        }

        return;
    }
};


int main() {
    
    Solution sol;

    vector<vector<int>> stars_indexes_arr ={{2, 5, 6}, {0, 2, 3}, {6, 10, 11}};
    sol.CountingStars(stars_indexes_arr);


    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:

    deque<tuple<int, int, int>>::iterator findMin(deque<tuple<int, int, int>>& q) {

        deque<tuple<int, int, int>>::iterator result = q.end();
        int minVal = INT_MAX;
        for (deque<tuple<int, int, int>>::iterator it = q.begin(); 
                it != q.end(); 
                it++) {
            if (get<0>(*it) < minVal) {
                minVal = get<0>(*it);                
                result = it;
            }

        }
        return result;
    }
    void CountingStars(vector<vector<int>>& stars_indexes_arr) {


        int m = stars_indexes_arr.size();
        int n = stars_indexes_arr[0].size();

        deque<tuple<int, int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({ stars_indexes_arr[i][0], i, 0 });
        }

        int count = 0;
        int prev = INT_MAX;
        int val;

        while (q.size() > 0) {
  //          cout << "size: " << q.size() << endl;
            deque<tuple<int, int, int>>::iterator ret = findMin(q);
            tuple<int, int, int> elem = (*ret);
            val = get<0>(elem);
            int row = get<1>(elem);
            int col = get<2>(elem);
    //        cout << "val: " << val << " row: " << row << " col: " << col  << endl;
            
            q.erase(ret);
      //      cout << "size: " << q.size()  << endl;
            if (col + 1 < n) {
                q.push_back({ stars_indexes_arr[row][col + 1], row, col + 1 });
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

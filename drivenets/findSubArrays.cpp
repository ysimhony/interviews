
/*
You can compile the code with either c++11 or c++17

yacovs@MOE-KT-6565923:~/interviews/drivenets$ g++ -std=c++11 -ggdb -o findSubArrays findSubArrays.cpp
yacovs@MOE-KT-6565923:~/interviews/drivenets$ g++ -std=c++17 -ggdb -o findSubArrays findSubArrays.cpp


*/
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


vector<pair<int, int>> findSubArrays(vector<int> arr) {

    vector<pair<int, int>> result;
    unordered_map<int, vector<int>> num2indices;
    num2indices[0] = {-1};
    int sum = 0;

    for (int i=0; i<arr.size(); i++) {
        
        sum += arr[i];

        if (num2indices.find(sum) != num2indices.end()) {
            
            for (auto index: num2indices[sum]) {
                /*
                chatGpt suggest to use emplace_back instead of 
push_back(), since this function has better performance as it does the 
operations in-place.
                result.push_back(make_pair(index+1, i));            
                */
                result.emplace_back(index+1, i);
            }
        }

        num2indices[sum].push_back(i);
    }

    return result;
}




int main() {

    std::cout << "__cplusplus = " << __cplusplus << std::endl;
    vector<int> arr = {6, 3, -1, -3, 4, -2, 2, 4, 6, -12, -7};
    vector<pair<int, int>> res = findSubArrays(arr);

#if __cplusplus >= 201703L 
    for (const auto &[start, end] : res) {
        cout << "start: " << start << " end: " << end << endl;
    }
#elif __cplusplus >= 201103L

/*
    This is the warning you get if you compile this code with c++17:

    findSubArrays.cpp: In function ‘int main()’:
findSubArrays.cpp:43:22: warning: structured bindings only available with ‘-std=c++17’ or ‘-std=gnu++17’ [-Wc++17-extensions]
   43 |     for (const auto &[start, end] : res) {
      |        
*/

    for (auto p : res) {
        cout << "start: " << p.first << " end: " << p.second << endl;

    }        
#endif
}

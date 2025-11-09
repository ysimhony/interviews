#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    // ---------------- VECTOR ----------------
    vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.emplace_back(5);
    cout << "Vector: ";
    for (int x : v) cout << x << " ";
    /*
    Vector: 1 2 3 4 5
    */
    cout << "\nFront: " << v.front() << ", Back: " << v.back() << "\n";
    /*
    Front: 1, Back: 5
    */
    v.pop_back();
    sort(v.begin(), v.end());
    cout << "After sort: ";
    for (int x : v) cout << x << " ";
    cout << "\n\n";
    /*
    After sort: 1 2 3 4
    */

    // ---------------- LIST ----------------
    list<int> lst = {10, 20, 30};
    lst.push_front(5);
    lst.push_back(40);
    lst.remove(20);
    cout << "List: ";
    for (int x : lst) cout << x << " ";
    cout << "\n\n";
    /*
    List: 5 10 30 40
    */
    // ---------------- DEQUE ----------------
    deque<int> dq = {1, 2, 3};
    dq.push_front(0);
    dq.push_back(4);
    cout << "Deque: ";
    for (int x : dq) cout << x << " ";
    cout << "\n\n";
    /*
    Deque: 0 1 2 3 4
    */
    // ---------------- SET ----------------
    set<int> s = {3, 1, 2};
    s.insert(2); // duplicates ignored
    s.erase(1);
    cout << "Set: ";
    for (int x : s) cout << x << " ";
    cout << "\nContains 2? " << (s.count(2) ? "Yes" : "No") << "\n\n";
    /*
    Set: 2 3
    Contains 2? Yes
    */
    // ---------------- UNORDERED_SET ----------------
    unordered_set<string> us = {"apple", "banana"};
    us.insert("orange");
    cout << "Unordered Set: ";
    for (auto &x : us) cout << x << " ";
    cout << "\n\n";
    /*
    Unordered Set: orange banana apple
    */
    // ---------------- MAP ----------------
    map<string, int> m;
    m["apple"] = 3;
    m.insert({"banana", 5});
    m.emplace("pear", 7);
    cout << "Map:\n";
    for (auto &[k, v] : m)
        cout << "  " << k << " -> " << v << "\n";
    cout << "Find banana: " << m["banana"] << "\n\n";
    /*
    Map:
      apple -> 3
      banana -> 5
      pear -> 7
    Find banana: 5
    */

    // ---------------- UNORDERED_MAP ----------------
    unordered_map<string, int> um = {{"x", 10}, {"y", 20}};
    um["z"] = 30;
    cout << "Unordered Map:\n";
    for (auto &[k, v] : um)
        cout << "  " << k << " -> " << v << "\n";
    cout << "\n";
    /*
    Unordered Map:
      z -> 30
      y -> 20
      x -> 10

    */
    // ---------------- STACK ----------------
    stack<int> st;
    st.push(10);
    st.push(20);
    cout << "Stack top: " << st.top() << "\n";
    st.pop();
    cout << "After pop, top: " << st.top() << "\n\n";
    /*
    Stack top: 20
    After pop, top: 10    
    */

    // ---------------- QUEUE ----------------
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Queue front: " << q.front() << ", back: " << q.back() << "\n";
    q.pop();
    cout << "After pop, front: " << q.front() << "\n\n";
    /*
    Queue front: 1, back: 3
    After pop, front: 2
    */

    // ---------------- PRIORITY_QUEUE ----------------
    priority_queue<int> pq;
    pq.push(5);
    pq.push(1);
    pq.push(3);
    cout << "Priority Queue (max-heap): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n\n";
    /*
    Priority Queue (max-heap): 5 3 1
    */

    // ---------------- ALGORITHMS ----------------
    vector<int> a = {4, 2, 5, 1, 3};
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    cout << "Algorithms (sort + reverse): ";
    for (int x : a) cout << x << " ";
    cout << "\nMin: " << *min_element(a.begin(), a.end())
         << ", Max: " << *max_element(a.begin(), a.end()) << "\n";
    /*
    Algorithms (sort + reverse): 5 4 3 2 1
    Min: 1, Max: 5
    */

    cout << "\nAll done!\n";
    return 0;
}


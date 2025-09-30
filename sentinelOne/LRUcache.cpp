
using namespace std;

#include <iostream>
#include <list>
#include <unordered_map>
class LRUCache {
public:

    unordered_map<int, pair<int, list<int>::iterator>> cache;
    int m_capacity;
    list<int> lru;

    LRUCache(int capacity) {
        m_capacity = capacity;
    }

    int get(int key) {

        if (cache.find(key) == cache.end()) {
            return -1;
        }

        int val = cache[key].first;
        
        list<int>::iterator it = cache[key].second;
        lru.erase(it);
        lru.push_front(key);
        return val;

    }

    void put(int key, int value) {

        if (cache.find(key) != cache.end()) {

            list<int>::iterator it = cache[key].second;
            lru.erase(it);
            lru.push_front(key);
            cache[key] = make_pair(value, lru.begin());
            
        }
        else {
            lru.push_front(key);
            cache[key] = make_pair(value, lru.begin());

            if (lru.size() > m_capacity) {
                list<int>::iterator last = prev(lru.end());

                cache.erase(*last);
                lru.erase(last);

            }
        }
    }
};


int main() {
    
    LRUCache lru_cache(2);
    lru_cache.put(1, 10);
    cout << lru_cache.get(1) << endl;
    lru_cache.put(2, 20);
    lru_cache.put(3, 30);
    cout << lru_cache.get(2) << endl;
    cout << lru_cache.get(1) << endl;

    return 0;
}

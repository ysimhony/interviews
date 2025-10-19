
class LRUCache {
public:

    LRUCache(int capacity) {
    }

    int get(int key) {

    }

    void put(int key, int value) {

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

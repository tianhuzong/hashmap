#include <iostream>
#include <vector>
#include <functional>

template<typename K, typename V>
class Pair {
public:
    K key;
    V val;

    Pair(const K& k, const V& v) : key(k), val(v) {}
};

template<typename K, typename V>
class HashMap {
private:
    int size;
    int capacity = 4;
    const double loadThres = 2.0 / 3.0;
    const int extendRatio = 2;
    std::vector<Pair<K, V>*> buckets;
    Pair<K, V>* TOMBSTONE;

public:
    HashMap();
    ~HashMap();
    int hashFunc(const K& key);
    double loadFactor();
    int findBucket(const K& key);
    V get(const K& key);
    void put(const K& key, const V& val);
    void remove(const K& key);
    void extend();
    void print();
};

template<typename K, typename V>
HashMap<K, V>::HashMap() : size(0), buckets(capacity, nullptr) {
    TOMBSTONE = new Pair<K, V>(K(), V());
}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    for (auto pair : buckets) {
        if (pair != nullptr && pair != TOMBSTONE) {
            delete pair;
        }
    }
    delete TOMBSTONE;
}

template<typename K, typename V>
int HashMap<K, V>::hashFunc(const K& key) {
    std::hash<K> hasher;
    return hasher(key) % capacity;
}

template<typename K, typename V>
double HashMap<K, V>::loadFactor() {
    return static_cast<double>(size) / capacity;
}

template<typename K, typename V>
int HashMap<K, V>::findBucket(const K& key) {
    int index = hashFunc(key);
    int firstTombstone = -1;
    while (buckets[index] != nullptr) {
        if (buckets[index] != TOMBSTONE && buckets[index]->key == key) {
            if (firstTombstone != -1) {
                buckets[firstTombstone] = buckets[index];
                buckets[index] = TOMBSTONE;
                return firstTombstone;
            }
            return index;
        }
        if (firstTombstone == -1 && buckets[index] == TOMBSTONE) {
            firstTombstone = index;
        }
        index = (index + 1) % capacity;
    }
    return firstTombstone == -1 ? index : firstTombstone;
}

template<typename K, typename V>
V HashMap<K, V>::get(const K& key) {
    int index = findBucket(key);
    if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
        return buckets[index]->val;
    }
    return V();
}

template<typename K, typename V>
void HashMap<K, V>::put(const K& key, const V& val) {
    if (loadFactor() > loadThres) {
        extend();
    }
    int index = findBucket(key);
    if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
        buckets[index]->val = val;
        return;
    }
    buckets[index] = new Pair<K, V>(key, val);
    size++;
}

template<typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
    int index = findBucket(key);
    if (buckets[index] != nullptr && buckets[index] != TOMBSTONE) {
        delete buckets[index];
        buckets[index] = TOMBSTONE;
        size--;
    }
}

template<typename K, typename V>
void HashMap<K, V>::extend() {
    std::vector<Pair<K, V>*> bucketsTmp = buckets;
    capacity *= extendRatio;
    buckets = std::vector<Pair<K, V>*>(capacity, nullptr);
    size = 0;
    for (auto pair : bucketsTmp) {
        if (pair != nullptr && pair != TOMBSTONE) {
            put(pair->key, pair->val);
            delete pair;
        }
    }
}

template<typename K, typename V>
void HashMap<K, V>::print() {
    for (auto pair : buckets) {
        if (pair == nullptr) {
            std::cout << "nullptr" << std::endl;
        } else if (pair == TOMBSTONE) {
            std::cout << "TOMBSTONE" << std::endl;
        } else {
            std::cout << pair->key << " -> " << pair->val << std::endl;
        }
    }
}

// Explicit template instantiation for types used in Cython
//template class HashMap<int, std::string>;

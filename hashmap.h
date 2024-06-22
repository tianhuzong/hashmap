#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <vector>
#include <functional>

//键值对
template<typename K, typename V>
class Pair {
public:
    K key;
    V val;

    Pair(const K& k, const V& v) : key(k), val(v) {}
};
//哈希表
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

#endif

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include "Food.h"

using namespace std;

template<typename K, typename V>
class unordered_map
{
private:
    vector<list<pair<K, V>>> hashTable;
    int size;
    int capacity;

public:
    unordered_map(int cap = 100000) : capacity(cap), size(0), hashTable(cap) {}

    int hash(K key)
    {
        return std::hash<K>{}(key) % capacity;
    }

    void insert(K key, V value)
    {
        for (auto& x : hashTable[hash(key)])
        {
            if (x.first == key)
            {
                x.second = value;
                return;
            }
        }
        hashTable[hash(key)].push_back(make_pair(key, value));
        size++;
    }

    bool search(K key, V& value)
    {
        for (auto& x : hashTable[hash(key)]) {
            if (x.first == key)
            {
                value = x.second;
                return true;
            }
        }
        return false;
    }

    bool remove(K key)
    {
        for (auto it = hashTable[hash(key)].begin(); it != hashTable[hash(key)].end(); ++it)
        {
            if (it->first == key) {
                hashTable[hash(key)].erase(it);
                size--;
                return true;
            }
        }
        return false;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

int main()
{
    unordered_map<string, Food> foodMap;

    foodMap.insert("Apple", Food("1", "Apple", 25.0, 0.3, 0.2, 19.0, 1.0));
    foodMap.insert("Banana", Food("2", "Banana", 23.0, 1.1, 0.3, 12.0, 1.0));

    Food searchResult;
    if (foodMap.search("Apple", searchResult))
    {
        cout << "Found Apple, Nutritional Information:" << endl;
        cout << "Carbohydrates: " << searchResult.carbohydrates << "g" << endl;
        cout << "Proteins: " << searchResult.proteins << "g" << endl;
        cout << "Fat: " << searchResult.fat << "g" << endl;
        cout << "Sugars: " << searchResult.sugars << "g" << endl;
        cout << "Sodium: " << searchResult.sodium << "mg" << endl;
    }
    else
        cout << "Apple not found" << endl;
    
    return 0;
}

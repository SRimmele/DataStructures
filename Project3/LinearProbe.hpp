#ifndef LINEAR_PROBE_HPP
#define LINEAR_PROBE_HPP

#include <string>

struct Pair {
    std::string key; 
    int value; 
}; 

class HashTable { 
    private: 
    int maxSize; 
    int currentSize; 
    Pair* array; 

    public: 
    HashTable(int size);    //constructor
    ~HashTable();   //Destructor
    int hashFunction(std::string key); 
    void insert(std::string key, int value);
    void remove(std::string key); 
    int search(std::string key);
    void print();
};

HashTable generateHashMap(int size, int maxSize); 
void runLinearProbing(); 

#endif
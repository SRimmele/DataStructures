#ifndef LINEAR_PROBE_HPP
#define LINEAR_PROBE_HPP

struct Node{
    int element; 
    struct Node* next; 
};

class HashTable {
    private: 
    
    public: 
    HashTable();    //constructor
    void insert(int element);
    void remove(); 
    int search(int element);

}




#endif 
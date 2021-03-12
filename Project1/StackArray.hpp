#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP
#define STACK_BUFFER 1024

template<typename T, int size>
class StackArray{
    private:
        int *stack; // O(n)
        int top; // O(1)

        // O(n) + O(1) = O(n)

    public: 
        StackArray();       //default
        StackArray(T* array, int length); 
        ~StackArray(); 

        bool isEmpty(); 
        void push(T element); 
        void pop(); 
        int search(T element);
};

StackArray<int, STACK_BUFFER> generateStack(int size); 

void runnerArray(); 

#endif //Stack Array HPP
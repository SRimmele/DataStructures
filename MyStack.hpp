#ifndef MY_STACK_HPP
#define MY_STACK_HPP

struct Node
{
    int element; 
    struct Node* next; 
};

//Simple stack using a Linked List.
class MyStack {
private: 
    Node* top;
public:
    MyStack(const int array[], int size);
    MyStack();
    void push(int element);
    void pop();
    int search(int element);
};

MyStack generateMyStack(int size);

void runner();


#endif // MY_STACK_HPP
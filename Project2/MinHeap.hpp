#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream> // For printing out to console.
#include <algorithm> // for std::swap in _siftdown.

template <typename T>
class MinHeap
{
private:
    T* _heap;               // Pointer to heap array
    int _maxSize;           // Maximum size of the heap
    int _currSize;          // Number of elements currently in the heap
    void _siftdown(int);    // Put element into place

public:
    // Constructors
    MinHeap();
    MinHeap(int max);
    MinHeap(T* curr, int num, int max);
    ~MinHeap();

    // Service Methods
    void buildHeap();           // Heapifies Internal Array
    int size() const;           // Standard Size Getter (current heap size)
    void resize();              // Double Max Size of Internal Array.
    friend std::ostream& operator<<(std::ostream& input, MinHeap const& rhs)  // for ~debugging~
    {
        if(!rhs.size())  // Empty
            return input << "EMPTY HEAP";

        for(int i = 0; i < rhs.size(); ++i)
            input << rhs._heap[i] << " | ";

        return input;
    }

    // Relational Methods
    bool isLeaf(int ) const;
    int leftChild(int ) const;
    int rightChild(int ) const;
    int parent(int ) const;

    // Modifying (Insert/Erase) Methods
    bool insert(const T&);
    bool remove(int);

    bool removeMax();
    bool removeMin();

    // Nonmodifying-ish (Get/Search) Methods
    T getMaxVal() const;        // we're not gonna let the user modify the underlying values
    int getMaxIndex() const;    // because we don't really have a way of forcing them to maintain
    T getMinVal() const;        // the MinHeap structure.
    int getMinIndex() const;

    T getValAt(int) const;
    int getIndex(const T&);    // Get index of arbitrary element. Might be used in internal methods.
};

// Code Implementation, for readability.

// Notable Notes to Know If You're Implementing This And I Did Something Wrong:
// For a Complete Binary Tree, [_currSize/2] yields the index of the earliest leaf
// Assume that elements of type T have an operator< overload (objects are comparable)

template <typename T>
MinHeap<T>::MinHeap()
{
    _maxSize = 16;
    _currSize = 0;
    _heap = new T[_maxSize];
}

template <typename T>
MinHeap<T>::MinHeap(int max)
{
    _heap = new T*;
    _maxSize = max;
    _currSize = 0;
}

template <typename T>
MinHeap<T>::MinHeap(T* curr, int num, int max)
{
    _heap = curr;
    _maxSize = max;
    _currSize = num;

    buildHeap();
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    //delete _heap;
}

// _siftdown -- swaps elements until Heap Property restored
// Use it for Pre-Existing Arrays
template <typename T>
void MinHeap<T>::_siftdown(int currPos)
{
    //std::cout << "Siftdown called on: " << _heap[currPos] << " at index: " << currPos << std::endl;
    if(isLeaf(currPos)) // We've reached the end,
        return;         //  base condition.

    // ok no
    // int smallestChild = ( (rightChild(currPos) < _currSize) && _heap[leftChild(currPos)] < _heap[rightChild(currPos)] ) ? ;

    // Get Smallest Child to compare against Current Subroot.
    int smallestChild;
    if( (rightChild(currPos) < _currSize) && (_heap[ rightChild(currPos) ] < _heap[ leftChild(currPos) ]) )
    {
        smallestChild = rightChild(currPos);
    }
    else
    {
        smallestChild = leftChild(currPos);
    }

    //std::cout << "\t" << _heap[currPos] << " vs. " << _heap[smallestChild] << "\n";

    if( _heap[currPos] < _heap[smallestChild] ) // We're already the smallest. Second Base Case.
        return;

    // Swap the values.
    std::swap(_heap[currPos], _heap[smallestChild]);

    _siftdown(smallestChild);                           // Siftdown from the (new) smallestChild.
}

// Heapify contents of the heap
template <typename T>
void MinHeap<T>::buildHeap()
{
    for(int currPos = (_currSize/2)-1; currPos >= 0; --currPos) // Start at the last internal node,
    {                                                           // Then _siftdown upwards.
        //std::cout << "Before: " << *this << std::endl;
        _siftdown(currPos); // Verify the Heap property
        //std::cout << "After: " << *this << std::endl;
    }
}

// Service Methods
// current heap size
template <typename T>
int MinHeap<T>::size() const
{
    return _currSize;
}

template <typename T>
void MinHeap<T>::resize()
{
    T* newHeap = new T[_maxSize * 2];

    for(int i = 0; i < _maxSize; ++i)
    {
        newHeap[i] = _heap[i];
    }

    newHeap = _heap;
}

/*
template <typename T>
std::ostream& operator<<(std::ostream& input, MinHeap<T> const &rhs)
{
    if(!rhs.size())  // Empty
        return input << "EMPTY HEAP\n";

    for(int i = 0; i < rhs.size(); ++i)
        input << rhs._heap[i] << " | ";

    return input;
}
*/

// Relational Methods
/*
 *
 *                0
 *              /   \
 *             1     2      <-- Left Child of 1 is (1*2) + 1 = 3
 *           /  \   /  \
 *          3   4  5    6   <-- Parent of 5 is floor((5-1)/2) = floor(4/2) = 2
 *         /  \
 *        7    8            <-- First Leaf = floor(9/2) = 4. 4 Has no Children.
 */

template <typename T>
bool MinHeap<T>::isLeaf(int currPos) const
{   // Between First Leaf and 'Last Index'
    return ( (currPos >= (_currSize/2)) && (currPos < _currSize) );
}

template <typename T>
int MinHeap<T>::leftChild(int currPos) const
{
    return ( (2 * currPos) + 1 );
}

template <typename T>
int MinHeap<T>::rightChild(int currPos) const
{
    return ( (2 * currPos) + 2 );
}

template <typename T>
int MinHeap<T>::parent(int currPos) const
{
    return ( (currPos - 1) / 2 );
}

// Modifying Methods:
// Insert:
template <typename T>
bool MinHeap<T>::insert(const T &nodeIn)
{
    if(_currSize == _maxSize)
        resize();   // kept for now. return false;

    // Append to end of the array & increment running total:
    _heap[_currSize++] = nodeIn;

    // On the one hand, we /could/ just `buildHeap` and call it a day
    // but that's quite inefficient, as we'll end up traversing everything
    // again. Instead, we can take some form of advantage of the situation:
    // Let's siftup (instead of siftdown):
    int currNode = _currSize - 1;   // Index of Inserted Node.

    while( _heap[currNode] < _heap[ parent(currNode) ])
    {   // For every parent node greater than our inserted node...
        std::swap(_heap[currNode], _heap[ parent(currNode) ]);  // Swap,
        currNode = parent(currNode);                            // 'iterate'
    }

    return true;
}

// Remove:
template <typename T>
bool MinHeap<T>::remove(int index)
{
    if(index < 0 || index >= _currSize)    // Boundary check.
        return false;

    // While we can fill the resulting empty space with one of its children,
    //  the children might themselves have children, so we risk
    //  wasting time managing the subtrees.
    // Instead, we can swap out the current node with any leaf node
    //  to make sure that we don't screw anything else up elsewhere
    // The last leaf node ought to be the simplest (and easiest), since
    //  it's, by our implementation, the last element in `_heap`:
    _heap[index] = _heap[_currSize - 1];    // Replace,
    _heap[_currSize - 1] = NULL;            // "Delete."
    _currSize--;                            // Update Size.

    // Now, we need to restore the Heap Property.
    // Since we only updated a single value, we'll only need to _siftdown
    //  at that index.
    _siftdown(index);

    return true;
}

// Remove Max:
template <typename T>
bool MinHeap<T>::removeMax()
{
    if(!_currSize)
        return false;

    // First, find the Max,
    // Then remove it the good 'ol way
    remove( getMaxIndex() );
    return true;
}

template <typename T>
T MinHeap<T>::getMaxVal() const
{
    if(!_currSize)
        return NULL;

    return _heap[ getMaxIndex() ];
}

template <typename T>
int MinHeap<T>::getMaxIndex() const
{
    // Since we're hella unordered, we've got no way of gracefully
    //  finding it. Sequential Search it is:
    int maxIndex = 0;
    for(int i = 0; i < _currSize; ++i)
    {
        if(_heap[maxIndex] < _heap[i])
            maxIndex = 1;
    }

    return maxIndex;
}

template <typename T>
T MinHeap<T>::getMinVal() const
{
    if(!_currSize)
        return NULL;

    return _heap[0];
}

template <typename T>
int MinHeap<T>::getMinIndex() const
{
    return 0;   // it's... just... don't worry about it.
}

template <typename T>
T MinHeap<T>::getValAt(int index) const
{
    if(index < 0 || index >= _currSize)
        return NULL;

    return _heap[index];
}

template <typename T>
int MinHeap<T>::getIndex(const T &nodeIn)
{
    int index = 0;

    while(index < _currSize)
    {
        if(_heap[index] == nodeIn)
            break;

        ++index;
    }

    return index;
}

void runMinHeap(); 


#endif // MINHEAP_HPP

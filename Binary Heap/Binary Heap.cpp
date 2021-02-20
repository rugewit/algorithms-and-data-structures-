#include <iostream>
#include <climits> 
// src https://www.geeksforgeeks.org/binary-heap/

// Prototype of a utility function to swap two integers 
void swap(int* x, int* y);

// A class for Min Heap 
class MinHeap
{
    int* heapArray; // pointer to array of elements in heap 
    int capacity; // maximum possible size of min heap 
    int heapSize; // Current number of elements in min heap 
public:
    // Constructor 
    MinHeap(int capacity);

    // to heapify a subtree with the root at given index 
    void MinHeapify(int);

    int parent(int i) { 
        return (i - 1) / 2; 
    }

    // to get index of left child of node at index i 
    int left(int i) { 
        return (2 * i + 1); 
    }

    // to get index of right child of node at index i 
    int right(int i) { 
        return (2 * i + 2); 
    }

    // to extract the root which is the minimum element 
    int extractMin();

    // Decreases key value of key at index i to new_val 
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap 
    int getMin()
    { 
        return heapArray[0];
    }

    // Deletes a key stored at index i 
    void deleteKey(int i);

    // Inserts a new key 'k' 
    void insertKey(int k);

    // Print elements of heapArray
    void PrintSelf();
};

// Constructor: Builds a heap from a given array a[] of given size 
MinHeap::MinHeap(int cap)
{
    heapSize = 0;
    capacity = cap;
    heapArray = new int[cap];
}

// Inserts a new key 'k' 
void MinHeap::insertKey(int k)
{
    if (heapSize == capacity)
    {
        std::cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end 
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = k;

    // Fix the min heap property if it is violated 
    while (i != 0 && heapArray[parent(i)] > heapArray[i])
    {
        swap(&heapArray[i], &heapArray[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that 
// new_val is smaller than heapArray[i]. 
void MinHeap::decreaseKey(int i, int new_val)
{
    heapArray[i] = new_val;
    while (i != 0 && heapArray[parent(i)] > heapArray[i])
    {
        swap(&heapArray[i], &heapArray[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap 
int MinHeap::extractMin()
{
    if (heapSize <= 0)
        return INT_MAX;
    if (heapSize == 1)
    {
        heapSize--;
        return heapArray[0];
    }

    // Store the minimum value, and remove it from heap 
    int root = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    MinHeapify(0);

    return root;
}


// This function deletes key at index i. It first reduced value to minus 
// infinite, then calls extractMin() 
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && heapArray[l] < heapArray[i])
        smallest = l;
    if (r < heapSize && heapArray[r] < heapArray[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&heapArray[i], &heapArray[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::PrintSelf() {
    for (size_t i = 0; i < heapSize; i++) {
        std::cout << heapArray[i] << " ";
    }
    std::cout << std::endl;
}

// A utility function to swap two elements 
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    
    MinHeap minHeap(6);
    minHeap.insertKey(1);
    minHeap.insertKey(3);
    minHeap.insertKey(6);
    minHeap.insertKey(5);
    minHeap.insertKey(9);
    minHeap.insertKey(8);
    minHeap.PrintSelf();
}


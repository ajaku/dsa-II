// Initial Test of Heap
// Make sure fundamental data structure works
// Then worry about combining with hash

#include <iostream>
//#include <vector>
#include <string>
#include "heap.h"

using namespace std;

heap::heap(int capacity) {
    array.resize(capacity+1);
    array[0] = 0; // Disregarded element
    cur_size = 0;
}

void heap::insert(int key) {
    // Resize condition
    if (cur_size == array.size() - 1) {
        array.resize(array.size() * 2);
    }
    // Will also likely rehash to increase size here

    // Inserting will always be a percolateUp operation 
    cur_size++;
    // You create a hole at the next index and percolate from there
    percolateUp(key, cur_size);
}

void heap::percolateUp(int key, int hole) {
    // while value at hole > value at parent, keep doing
    
    while ((hole > 1) && (key < array[hole/2])) {
        array[hole] = array[hole/2];
        hole /= 2;
    }
    array[hole] = key;
}

void heap::deleteMin() {
    if (!cur_size) {
        cout << "Is empty\n";
    }

    // Replace top with very bottom value and percolate down
    array[1] = array[cur_size--];
    percolateDown(1);
}

void heap::percolateDown(int hole) {
    int child;
    int temp = array[hole];

    while (hole*2 <= cur_size) {
        child = hole*2;
        if (child != cur_size && array[child + 1] < array[child]) {
            child++;
        }
        if (array[child] < temp) {
            array[hole] = array[child];
        } else {
            break;
        }
        hole = child;
    }
    /*for (; hole*2 <= cur_size; hole = child) {
        child = hole*2;
        if (child != cur_size && array[child + 1] < array[child]) {
            child++;
        }
        if (array[child] < temp) {
            array[hole] = array[child];
        } else {
            break;
        }
    }*/
    array[hole] = temp;
    // Set value in hole to 0
    array[cur_size + 1] = 0;
}

void heap::buildHeap() {
    for (int i = cur_size/2; i > 0; i--) {
        percolateDown(i);
    }
}
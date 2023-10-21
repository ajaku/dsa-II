#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure Inspired by: Weiss's DSA in C++ Chp. 6.3
class heap
{

 public:

    heap(int capacity = 100);

    void insert(int key);
    //void setKey(int key); Will rely on hash
    void deleteMin();
    //void remove(string id);
    void makeEmpty();

 private:
    class node {
     public:
        string id;
        int key;
        void *pData;
    };

    int cur_size;
    vector<int> array; // would actually be of <node>
    //hashTable mapping;

    void buildHeap();
    void percolateDown(int hole);
    void percolateUp(int key, int hole);

    int get_pos(int key);
};

#endif //_HEAP_H
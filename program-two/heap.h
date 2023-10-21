#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <string>
#include "hash.h"

using namespace std;

// Structure Inspired by: Weiss's DSA in C++ Chp. 6.3
class heap
{

 public:

    heap(int capacity);

    void insert(const string &id, int key, void *pv = nullptr);
    int setKey(const string &id, int key);
    void deleteMin(string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);
    void remove(const string &id, int *pKey = nullptr, void *ppData = nullptr);

 private:
    class node {
     public:
        string id;
        int key;
        void *pData;
    };

    int cur_size;
    int heap_cap;
    vector<node> array; // would actually be of <node>
    hashTable mapping;

    void percolateDown(int hole);
    void percolateUp(int pos_cur);

    int get_pos(node *pn);
};

#endif //_HEAP_H
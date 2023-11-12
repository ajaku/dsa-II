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

   // 0 - Success, 1 - Heap Full, 2 - Already Exists
   int insert(const string &id, int key, void *pv = nullptr);
   // 0 - Success, 1 - ID Does not exist
   int setKey(const string &id, int key);
   // 0 - Success, 1 - Heap Empty
   int deleteMin(string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);
   // 0 - Success, 1 - ID Does not Exist 
   int remove(const string &id, int *pKey = nullptr, void *ppData = nullptr);

 private:
   class node {
    public:
      string id;
      int key;
      void *pData;
   };

   int cur_size;
   int heap_cap;
   vector<node> array;
   hashTable mapping;

   void percolateDown(int pos_cur);
   void percolateUp(int pos_cur);

   // Returns location of node on heap
   int get_pos(node *pn);
};

#endif //_HEAP_H
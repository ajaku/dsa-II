// Initial Test of Heap
// Make sure fundamental data structure works
// Then worry about combining with hash

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "heap.h"

using namespace std;

heap::heap(int capacity)
 : mapping(capacity) {
    heap_cap = capacity;
    if (capacity == 0) {
        heap_cap = 100;
    }
    array.resize(heap_cap+1);
    // Disregarded element
    array[0].id    = "";
    array[0].key   = 0;
    array[0].pData = nullptr;
    cur_size = 0;
}

int heap::insert(const string &id, int key, void *pv) {
    // Resize condition
    if (cur_size == array.size() - 1) {
       cout << "Heap is already full\n"; 
       return 1;
    }
    // Will also likely rehash to increase size here

    // Inserting will always be a percolateUp operation 
    // You create a hole at the next index and percolate from there
    if (mapping.contains(id)) {
        cout << "Entry already exists\n";
        return 2;
    }

    cur_size++;
    array[cur_size].id    = id;
    array[cur_size].key   = key;
    array[cur_size].pData = pv;
    mapping.insert(id, &array[cur_size]);
    percolateUp(cur_size);
    return 0;
}

int heap::setKey(const string &id, int key) {
    bool b;
    node* pn = static_cast<node *> (mapping.getPointer(id, &b));
    if (!b) { return 1; }

    // Get existing key value, store it (to determine perc up or down)
    // then map that value to the new key
    int idx = get_pos(pn);
    int existing_key = array[idx].key;
    array[idx].key = key;
    // If new key is smaller will likely have to percolate up
    if (existing_key > key) { 
        percolateUp(idx);
    } else {
        percolateDown(idx);
    }
    return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
    if (!cur_size) {
        cout << "The heap is empty\n";
        return 1;
    }

    // Replace top with very bottom value and percolate down
    mapping.remove(array[1].id);
    cur_size;
    // Place last item into the top
    array[1] = array[cur_size];
    // Set elements of last item to 0
    array[cur_size].id     = "";
    array[cur_size].key    = 0;
    array[cur_size].pData  = nullptr;
    cur_size--;
    percolateDown(1);
    return 0;
} 

int heap::remove(const string &id, int *pKey, void *ppData) {
    bool b;
    node* pn = static_cast<node *> (mapping.getPointer(id, &b));
    if (!b) {
        cout << "Entry does not exist\n";
        return 1;
    }

    array[pn->key] = array[cur_size--];
    percolateDown(pn->key);
    return 0;
}


void heap::percolateUp(int pos_cur) {
    int local_pos = pos_cur;
    while (local_pos > 1) {
        int bottom_pos = local_pos;
        node bottom_node = array[local_pos];
        local_pos /= 2;
        node top_node = array[local_pos];

        if (bottom_node.key < top_node.key) {
            // Save one copy
            array[bottom_pos] = top_node;
            array[local_pos] = bottom_node;
        } else { break; }
    }
    mapping.setPointer(array[local_pos].id, &array[local_pos]);
}

void heap::percolateDown(int pos_cur) {
    // Inspired by : https://courses.cs.washington.edu/courses/cse373/17su/lectures/Lecture%2012%20-%20Binary%20Heaps.pdf
    while (2*pos_cur <= cur_size) {
        int left_pos    = 2*pos_cur;
        int right_pos   = left_pos + 1;

        node left_node  = array[left_pos];
        node right_node = array[right_pos];
        int target;

        if (right_pos > cur_size || (left_node.key < right_node.key)) {
            target = left_pos;
        } else { target = right_pos; }

        if (array[target].key < array[pos_cur].key) {
            array[target] = array[pos_cur];

            if (target == left_pos) {
                array[pos_cur] = left_node;
            } else { array[pos_cur] = right_node; }

            pos_cur = target;
        } else { break; }
    }
}

int heap::get_pos(node *pn) {
    return (pn - &array[0]);
}
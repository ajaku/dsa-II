// Initial Test of Heap
// Make sure fundamental data structure works
// Then worry about combining with hash

#include <iostream>
#include <vector>
#include <string>
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

void heap::insert(const string &id, int key, void *pv) {
    // Resize condition
    if (cur_size == array.size() - 1) {
        array.resize(array.size() * 2);
    }
    // Will also likely rehash to increase size here

    // Inserting will always be a percolateUp operation 
    // You create a hole at the next index and percolate from there
    cur_size++;
    array[cur_size].id    = id;
    array[cur_size].key   = key;
    array[cur_size].pData = pv;
    mapping.insert(id, &array[cur_size]);
    percolateUp(cur_size);
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

void heap::deleteMin(string *pId, int *pKey, void *ppData) {
    if (!cur_size) {
        cout << "Is empty\n";
    }

    // Replace top with very bottom value and percolate down
    array[1] = array[cur_size--];
    array[cur_size + 1].id     = "";
    array[cur_size + 1].key    = 0;
    array[cur_size + 1].pData  = nullptr;
    mapping.remove(array[cur_size + 1].id);
    percolateDown(1);
} 

void heap::remove(const string &id, int *pKey, void *ppData) {
    bool b;
    node* pn = static_cast<node *> (mapping.getPointer(id, &b));
    if (b) {
        array[pn->key] = array[cur_size--];
        percolateDown(pn->key);
    } else {
        cout << "Does not exist\n";
    }
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
    int child;
    node temp = array[pos_cur];

    while (pos_cur*2 <= pos_cur) {
        child = pos_cur*2;
        if (child != cur_size && array[child + 1].key < array[child].key) {
            child++;
        }
        if (array[child].key < temp.key) {
            array[pos_cur] = array[child];
        } else {
            break;
        }
        pos_cur = child;
    }
}

int heap::get_pos(node *pn) {
    return (pn - &array[0]);
}
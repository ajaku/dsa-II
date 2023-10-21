#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <unistd.h>
#include "hash.h"

#define MAX_IDX 8

using namespace std;

// The constructor initializes the hash table.
hashTable::hashTable(int size) {
  capacity = primes[7]; // largest number
  for (int i = 0; i < 8; i++) {
   if (size < primes[i]) {
    capacity = primes[i];
    prime_idx = i;
    break;
   }
  }
  data.resize(capacity);
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const string &key, void *pv) {
  if ((double)filled/(double)capacity >= 0.5) {
    rehash();
  }
  int loc = hash(key);
  if (data[loc].isOccupied) {
    if (data[loc].key != key) {
      // collission
      int i = loc;
      while (data[i].isOccupied) {
        if (i >= capacity - 1) {
          i = -1;
        }
        i++;
      }
      data[i].key = key;
      data[i].isOccupied = true;
      filled++;
      return 0;
    }
    return 1;
  }
  data[loc].key = key;
  data[loc].isOccupied = true;
  data[loc].pv = pv;
  filled++;
  return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const string &key) {
  // see if value is stored at hash location
  // see if key matches desired key (collission)
  // if collission, iterate through entire table to see if value exists
  //    Note: A value must exist if a collision is true!
  int loc = hash(key); // Location of key
  if (!data[loc].isOccupied)  { return false; } // value doesn't exist

  if (data[loc].key == key)   { return true; } // Value found

  int i = loc;
  while (data[i].isOccupied) {
    if (data[i].key == key) {
      return true;
    }
    i++;
    // Corrected per professor Sable's request
    if (i >= capacity) {
      i = 0;
    }
  }
  return false;
}

int hashTable::getCapacity() {
  return capacity;
}

int hashTable::getFilled() {
  return filled;
}

string hashTable::atLocation(int loc) {
  return data[loc].key;
}

// The hash function.
int hashTable::hash(const string &key) {
  int hashVal = 0;
  for(int i = 0; i < key.length(); i++) {
    hashVal = 37 * hashVal + key[i];
  }
  hashVal %= capacity; // ensures values are limited to 0-capacity

  if (hashVal < 0) {
    hashVal += capacity;
  }
  return hashVal;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const string &key) {
  if (contains(key)) {
    return hash(key);
  }
  else {
    return -1;
  }
}

// The rehash function; makes the hash table bigger.
bool hashTable::rehash() {
  prime_idx += 1;
  filled = 0;
  if(this->prime_idx >= MAX_IDX) {
    exit(1);
  }
  vector<hashItem> old_vec(capacity); // old capacity
  old_vec.swap(data);
  data.clear();
  capacity = primes[prime_idx];
  data.resize(capacity);
  int prev = prime_idx - 1;
  for (int i = 0; i < primes[prev]; i++) {
    insert(old_vec[i].key, old_vec[i].pv);
  }
  old_vec.clear();
  return true;
}

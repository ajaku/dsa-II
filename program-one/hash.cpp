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
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable() {
  capacity = 0;
}

hashTable::hashTable(int size) {
  capacity = primes[prime_idx];
  list = (hashItem*)calloc(capacity, sizeof(hashItem));
  for (int i = 0; i < capacity; i ++) {
    data.push_back(list[i]);
  }
}

hashTable::~hashTable() {
  free(list);
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const string &key, void *pv = nullptr) {
  //cout << "Filled: " << filled << "\tCapacity: " << capacity << "\n";
  if ((double)filled/(double)capacity >= 0.5) {
    //cout << "Filled: " << filled << "\t Capacity: " << capacity << "\n";
    rehash();
  }
  int loc = hash(key);
  if (data[loc].isOccupied) {
    if (data[loc].key != key) {
      // collission
      int i = loc;
      while (data[i].isOccupied) {
        //cout << "Key: " << key << "\tInsert: Looking for free data\n"; 
        if (i >= capacity) {
          i = -1;
        }
        i++;
      }
      data[i].key = key;
      data[i].isOccupied = true;
      filled++;
      //cout << "Location: " << i << "\n";
      return 0;
    }
    // Duplicate value
    //cout << "Duplicate value\n";
    return 1;
  }
  data[loc].key = key;
  data[loc].isOccupied = true;
  data[loc].pv = pv;
  filled++;
  //cout << "Location: " << loc << "\n";
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

string hashTable::findLoc(int loc) {
  return data[loc].key;
}

int hashTable::rehash_insert(const string &key, void *pv = nullptr, vector<hashItem>* new_vec = nullptr) {
  int loc = hash(key);
  if ((*new_vec)[loc].isOccupied) {
    if ((*new_vec)[loc].key != key) {
      // collission
      int i = loc;
      while ((*new_vec)[i].isOccupied) {
        //cout << "Key: " << key << "\tInsert: Looking for free data\n"; 
        if (i >= capacity) {
          i = -1;
        }
        i++;
      }
      (*new_vec)[i].key = key;
      (*new_vec)[i].isOccupied = true;
      filled++;
      //cout << "Location: " << i << "\n";
      return 0;
    }
    // Duplicate value
    //cout << "Duplicate value\n";
    return 1;
  }
  (*new_vec)[loc].key = key;
  (*new_vec)[loc].isOccupied = true;
  (*new_vec)[loc].pv = pv;
  filled++;
  //cout << "Location: " << loc << "\n";
  return 0;
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

/*
// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int findPos(const string &key);
*/

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash() {
  prime_idx += 1;
  filled = 0;
  if(this->prime_idx >= MAX_IDX) { 
    //cout << "Exceeding expected size\n";
    exit(1);
  }
  capacity = primes[prime_idx];
  hashItem* ptr = (hashItem*)calloc(capacity, sizeof(hashItem));
  vector<hashItem> new_vec;
  for (int i = 0; i < capacity; i ++) {
    new_vec.push_back(ptr[i]);
  }
  int prev = prime_idx - 1;
  for (int i = 0; i < primes[prev]; i++) {
    rehash_insert(data[i].key, data[i].pv, &new_vec);
    // need to make sure that this makes sense
  }
  data.clear(); 
  data.swap(new_vec);
  free(list);
  list = ptr;
  return true;
}

/*int main() {
  hashTable table(25000);
  cout << "Capacity: " << table.getCapacity() << "\n";
  printf("Filled: %d\n", table.getFilled());
  string doc, dict, output;
  read_input(&dict, &doc, &output);
  cout << "\nDict: " << dict << "\n";
  parse_input(dict, table);
  cout << "Does list contain abroad:  " << table.contains("abroad") << "\n";
  cout << "Does list contain aboard:  " << table.contains("aboard") << "\n";
  cout << "Does list contain abroad:  " << table.contains("abroadz") << "\n";
  cout << "Does list contain Zurich:  " << table.contains("Zurich") << "\n";
  return 0;
}*/
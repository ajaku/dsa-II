#ifndef _HASH_H
#define _HASH_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class hashTable {

 public:

  // The constructor initializes the hash table.
  // Uses getPrime to choose a prime number at least as large as
  // the specified size for the initial size of the hash table.
  hashTable(int size = 0);

  // Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns 0 on success,
  // 1 if key already exists in hash table,
  // 2 if rehash fails.
  int insert(const string &key, void *pv = nullptr); 

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool contains(const string &key);

  int getCapacity(); 

  int getFilled();

  string findLoc(int loc);
  /*

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  void *getPointer(const std::string &key, bool *b = nullptr);

  // Set the pointer associated with the specified key.
  // Returns 0 on success,
  // 1 if the key does not exist in the hash table.
  int setPointer(const std::string &key, void *pv);

  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
  bool remove(const std::string &key);

  */

 private:

  // Each item in the hash table contains:
  // key - a string used as a key.
  // isOccupied - if false, this entry is empty,
  //              and the other fields are meaningless.
  // isDeleted - if true, this item has been lazily deleted.
  // pv - a pointer related to the key;
  //      nullptr if no pointer was provided to insert.
  class hashItem {
  public:
    string key {""};
    bool isOccupied {false};
    bool isDeleted {false};
    void *pv {nullptr};

    hashItem() = default;
  };

  int capacity = 0; // The current capacity of the hash table.
  int filled = 0; // Number of occupied items in the table.
  int primes[8] = {25933, 50021, 100003, 200003, 400009, 800011, 1600033, 3200003};
  int prime_idx = 0;

  vector<hashItem> data; // The actual entries are here.

  // removed pre-defined values here
  int rehash_insert(const string &key, void *pv, vector<hashItem>* new_vec);

  // The hash function.
  int hash(const string &key);

  // Search for an item with the specified key.
  // Return the position if found, -1 otherwise.
  int findPos(const string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash();
};

#endif //_HASH_H
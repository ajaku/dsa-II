#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <unistd.h>
#define MAX_IDX 8

using namespace std;

class hashTable {

 public:

  // The constructor initializes the hash table.
  // Uses getPrime to choose a prime number at least as large as
  // the specified size for the initial size of the hash table.
  hashTable() {
    capacity = 0;
  }

  hashTable(int size) {
    capacity = primes[prime_idx];
    list = (hashItem*)calloc(capacity, sizeof(hashItem));
    for (int i = 0; i < capacity; i ++) {
      data.push_back(list[i]);
    }
  }

  ~hashTable() {
    free(list);
  }

  // Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns 0 on success,
  // 1 if key already exists in hash table,
  // 2 if rehash fails.
  int insert(const string &key, void *pv = nullptr) {
    cout << "Filled: " << filled << "\tCapacity: " << capacity << "\n";
    if ((double)filled/(double)capacity >= 0.5) {
      cout << "Filled: " << filled << "\t Capacity: " << capacity << "\n";
       rehash();
    }
    int loc = hash(key);
    if (data[loc].isOccupied) {
      if (data[loc].key != key) {
        // collission
        int i = loc;
        while (data[i].isOccupied) {
          cout << "Key: " << key << "\tInsert: Looking for free data\n"; 
          if (i >= capacity) {
            i = -1;
          }
          i++;
        }
        data[i].key = key;
        data[i].isOccupied = true;
        filled++;
        cout << "Location: " << i << "\n";
        return 0;
      }
      // Duplicate value
      cout << "Duplicate value\n";
      return 1;
    }
    data[loc].key = key;
    data[loc].isOccupied = true;
    data[loc].pv = pv;
    filled++;
    cout << "Location: " << loc << "\n";
    return 0;
  }

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool contains(const string &key) {
    // see if value is stored at hash location 
    // see if key matches desired key (collission)
    // if collission, iterate through entire table to see if value exists
    //    Note: A value must exist if a collision is true!
    int loc = hash(key); // Location of key
    if (!data[loc].isOccupied)  { return false; } // value doesn't exist

    if (data[loc].key == key)   { return true; } // Value found
    
    int i = loc;
    while (data[i].key != key) {
      i++;
      if (i >= capacity) {
        i = 0;
      }
    }
    return true;
  }

  int getCapacity() {
    return capacity;
  }

  int getFilled() {
    return filled;
  }

  string findLoc(int loc) {
    return data[loc].key;
  }

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
  
  hashItem* list;
  int capacity = 0; // The current capacity of the hash table.
  int filled = 0; // Number of occupied items in the table.
  int primes[8] = {25933, 50021, 100003, 200003, 400009, 800011, 1600033, 3200003};
  int prime_idx = 0;
  vector<hashItem> data; // The actual entries are here.


  int rehash_insert(const string &key, void *pv = nullptr, vector<hashItem>* new_vec = nullptr) {
    int loc = hash(key);
    if ((*new_vec)[loc].isOccupied) {
      if ((*new_vec)[loc].key != key) {
        // collission
        int i = loc;
        while ((*new_vec)[i].isOccupied) {
          cout << "Key: " << key << "\tInsert: Looking for free data\n"; 
          if (i >= capacity) {
            i = -1;
          }
          i++;
        }
        (*new_vec)[i].key = key;
        (*new_vec)[i].isOccupied = true;
        filled++;
        cout << "Location: " << i << "\n";
        return 0;
      }
      // Duplicate value
      cout << "Duplicate value\n";
      return 1;
    }
    (*new_vec)[loc].key = key;
    (*new_vec)[loc].isOccupied = true;
    (*new_vec)[loc].pv = pv;
    filled++;
    cout << "Location: " << loc << "\n";
    return 0;
  }

  // The hash function.
  int hash(const string &key) {
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
  int findPos(const string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash() {
    prime_idx += 1;
    if(this->prime_idx >= MAX_IDX) { 
      cout << "Exceeding expected size\n";
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

};

int parse_input(string file, hashTable& table) {
  fstream new_file;
  new_file.open(file, ios::in);
  if (new_file.is_open()) {
    string line;
    while (getline(new_file, line)) {
      string& temp = line;
      cout << line << "\n";
      table.insert(temp);
    }
  } else { return 1; }

  new_file.close();
  return 0;
}

int main() {
    hashTable table(25000);
    string file = "wordlist_small";
    cout << "Capacity: " << table.getCapacity() << "\n";
    printf("Filled: %d\n", table.getFilled());
    parse_input(file, table);
    cout << "Does list contain abroad:  " << table.contains("abroad") << "\n";
    cout << "Does list contain aboard:  " << table.contains("aboard") << "\n";
    cout << "Does list contain abroad:  " << table.contains("abroadz") << "\n";
    cout << "Does list contain Zurich:  " << table.contains("Zurich") << "\n";
    return 0;
}
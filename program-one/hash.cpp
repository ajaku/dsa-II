#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>

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
    capacity = getPrime(size);
  }

  // Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns 0 on success,
  // 1 if key already exists in hash table,
  // 2 if rehash fails.
  int insert(const string &key, void *pv = nullptr) {
    return hash(key);
  }

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool contains(const string &key) {
    return true;
  }

  int getSize() {
    return capacity;
  }
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

  int capacity; // The current capacity of the hash table.
  int filled; // Number of occupied items in the table.

  vector<hashItem> data; // The actual entries are here.

  // The hash function.
  int hash(const string &key) {
    int hash_scale = 3;
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        int cur = key[i];
        hash = (hash_scale*hash) + cur;
        /*if (hash > capacity) {
           while (hash > capacity) {
             hash /= 2;
           }
        }*/
    }
    hash < 0 ? (hash *= -1) : hash;
    cout << "Hash: " << hash << "\n";
    return hash;
  }

  // Search for an item with the specified key.
  // Return the position if found, -1 otherwise.
  int findPos(const string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash();

  // Return a prime number at least as large as size.
  // Uses a precomputed sequence of selected prime numbers.
  static unsigned int getPrime(int size) {
    if (size >= 1000000) { return 1000003; }
    if (size >= 500000)  { return 500009; }
    if (size >= 250000)  { return 250007; }
    if (size >= 100000)  { return 100003; }
    if (size >= 50000)   { return 50021; }
    return 10007;
  }
};

int main() {
    /*hashTable table(50000);
    cout << "Capacity: " << table.getSize() << "\n";
    string temp = "supercali";
    string& temp_ref = temp;
    table.insert(temp_ref);*/

    fstream new_file;
    new_file.open("wordlist_small", ios::in);
    hashTable table(25000);
    int hash[25144];
    int i = 0;
    if (new_file.is_open()) {
        string line;
        while (getline(new_file, line)) {
            cout << line << "\n";
            string& temp = line;
            int val = table.insert(temp);
            cout << "Val: " << val << "\n";
            hash[i] = val;
            cout << "i: " << i << "\t" << "Hash: " << hash[i] <<  "\n";
            i++;
        }
    }
    /*for (int i = 0; i < 25144; i++) {
        cout << hash[i] << "\n";
    }*/

    int dupes;
    for (int i = 0; i < sizeof(hash)/sizeof(int); i++) {
        for (int j = i+1; j < sizeof(hash)/sizeof(int); j++) {
            if (hash[i] == hash[j]) {
                //cout << "Prev: " << hash[i] << "\n";
                //cout << "Cur: " << hash[j] << "\n";
                //cout << "i: " << i << "\t" << "j: " << j << "\n";
                dupes++;
            }
        }
    }
    cout << "Dupes: " << dupes << "\n";
    new_file.close();
    return 0;
}
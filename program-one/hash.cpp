#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

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
    hashItem* ptr = (hashItem*)calloc(capacity, sizeof(hashItem));
    for (int i = 0; i < capacity; i ++) {
      data.push_back(ptr[i]);
    }
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
    cout << "Contains Loc: " << loc << "\n";
    if (!data[loc].isOccupied)  { return false; } // value doesn't exist

    if (data[loc].key == key)   { cout << "Value contained at: " << loc << "\n"; return true; } // Value found
    
    int i = loc;
    /*for (int i = 0; i < capacity; i++) {
      if(data[i].key == "aboard") {
        cout << "Loc: " << loc << "\ti: " << i << "\n";
        exit(1);
      }
    }
    */
    while (data[i].key != key) {
      cout << "Empty Key: " << data[i].key << "\ti: " << i << "\tCapacity: " << capacity << "\n";
      i++;
      if (i >= capacity) {
        i = 0;
      }
    }
    cout << "Value contained at: " << i << "\n";
    return true;
  }

  void do_rehash() {
    rehash();
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

  int capacity = 0; // The current capacity of the hash table.
  int filled = 0; // Number of occupied items in the table.

  vector<hashItem> data; // The actual entries are here.

  // The hash function.
  int hash(const string &key) {
    static int initial_cap = capacity;
    int hashVal = 0;
    for(int i = 0; i < key.length(); i++) {
      hashVal = 37 * hashVal + key[i];
    }
    hashVal %= initial_cap; // ensures values are limited to 0-capacity

    if (hashVal < 0) {
      hashVal += initial_cap;
    } 
    return hashVal;
  }

  // Search for an item with the specified key.
  // Return the position if found, -1 otherwise.
  int findPos(const string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash() {
    cout << "Over 50p filled\n";
    //exit(1);
    int prev_cap = capacity;
    capacity = getPrime(capacity*2);
    cout << "New cap: " << capacity << "\n";
    hashItem* ptr = (hashItem*)calloc(capacity, sizeof(hashItem));
    //hashItem* ptr = (hashItem*)malloc(capacity*sizeof(hashItem));
    vector<hashItem> new_vec;
    for (int i = 0; i < capacity; i ++) {
      new_vec.push_back(ptr[i]);
    }
    for (int i = 0; i < prev_cap; i++) {
      new_vec[i] = data[i];
    }
    printf("Calloc worked\n");
    data.swap(new_vec);
    return true;
  }

  // Return a prime number at least as large as size.
  // Uses a precomputed sequence of selected prime numbers.
  static unsigned int getPrime(int size) {
    if (size < 25000   ) { return 25933;   }
    if (size <= 50000  )  { return 50021;   }
    if (size <= 100000 )  { return 100003;  }
    if (size <= 250000 )  { return 250007;  }
    if (size <= 500000 )  { return 500009;  }
    if (size <= 1000000)  { return 1000003; }
    if (size <= 1500000)  { return 1500007; }
    return 2000001;
  }

};

int dupes(int arr[], int n) {
  int res = 1;
    // Pick all elements one by one
    for (int i = 1; i < n; i++) {
        int j = 0;
        for (j = 0; j < i; j++)
            if (arr[i] == arr[j])
                break;
 
        // If not printed earlier, then print it
        if (i == j)
            res++;
    }
    return res;
}

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
    cout << "Loc of abroad: " << table.contains("abroad") << "\n";
    cout << "Loc of aboard: " << table.contains("aboard") << "\n";
    // Values still exist, just contains can't, find them
    cout << table.findLoc(9458) << "\n"; 
    cout << table.findLoc(29891) << "\n"; 
    cout << table.findLoc(29891) << "\n"; 
    return 0;
}
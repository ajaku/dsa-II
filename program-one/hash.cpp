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

	if ((double)filled/(double)capacity >= 0.5) { rehash(); }

	if (contains(key)) { return 1; }

	int loc = hash(key);
	int og_loc = loc;

	// A value already exists there (result of linear probe for another item)
	while (data[loc].isOccupied) {
		loc++;
		// Make sure we only loop once
		if (loc == og_loc) 	 { return -1; }
		// Add wraparound for loop
		if (loc >= capacity) { loc = 0; }
	}

	data[loc].isOccupied = true;
	data[loc].isDeleted  = false;
	data[loc].key 		 = key;
	data[loc].pv  		 = pv;
	filled++;
	return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const string &key) {

	if (findPos(key) >= 0) { return true; }	

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

void *hashTable::getPointer(const string &key, bool *b) {

	int pos;
	if ((pos = findPos(key)) == -1) {
		*b = false;
		return nullptr;
	}

	*b = true;
	return data[pos].pv;
}

int hashTable::setPointer(const string &key, void *pv) {

	int pos;
	if ((pos = findPos(key)) == -1) {
		return 1;
	}

	data[pos].pv = pv;
	return 0;
}

bool hashTable::remove(const string &key) {

	int pos;
	if ((pos = findPos(key)) == -1) {
		return 1;
	}

	data[pos].isDeleted = 1;

	return 0;
}

// Private Methods

// The hash function.
int hashTable::hash(const string &key) {

	int hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		hashVal = 37 * hashVal + key[i];
	}
	hashVal %= capacity; // ensures values are limited to 0-capacity

	if (hashVal < 0) { hashVal += capacity; }

	return hashVal;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.

/* Just have a single loop as long as the current place is occupied.
 * If you get to an unoccupied cell, return -1. While the current cell is occupied,
 * if the key matches and it is not deleted, return the current location (otherwise keep looping)
 */

// CORRECTED - ASK PROF
int hashTable::findPos(const string &key) {

	int loc = hash(key);

	if (!data[loc].isOccupied) { return -1; }

	int og_loc = loc;
	while (data[loc].isOccupied) {
		
		// Entry exists and hasn't been deleted
		if ((data[loc].key == key) && !data[loc].isDeleted) { return loc; }
	
		loc++;

		// Make sure we only loop once
		if (loc == og_loc) 	 { return -1; }
		// Add wraparound for loop
		if (loc >= capacity) { loc = 0; }

	}
	return -1;
}

// The rehash function; makes the hash table bigger.
bool hashTable::rehash() {

	prime_idx += 1;
	filled = 0;

	if (this->prime_idx >= MAX_IDX) { exit(1); }

	vector<hashItem> old_vec(capacity); // old capacity
	old_vec.swap(data);
	data.clear();
	capacity = primes[prime_idx];
	data.resize(capacity);

	int prev = prime_idx - 1;
	for (int i = 0; i < primes[prev]; i++) {
		if (old_vec[i].isOccupied && !old_vec[i].isDeleted) {
			insert(old_vec[i].key, old_vec[i].pv);
		}
	}

	old_vec.clear();
	return true;
}

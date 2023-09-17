#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include "hash.h"

using namespace std;

bool deleteable_char(char c) {
    if (c >= '0' && c <= '9') { return false; }
    if (c >= 'A' && c <= 'Z') { return false; }
    if (c >= 'a' && c <= 'z') { return false; }
    if (c == '-' || c == 0x27) { return false; }
    
    return true;
}

// Get each word from each line in doc (sep by spaces)
void parse_doc(hashTable *table) {
    string input, output;
    cout << "Enter name of input file: ";
    cin >> input;
    cout << "Enter name of output file: ";
    cin >> output;
    fstream outfile;
    outfile.open(output, ios_base::out);

    if (!outfile.is_open()){
      cout << "Unable to open file";
      exit(0);
    }

    ifstream file(input);
    if (file.is_open()) {
        clock_t start = clock();
        string line;
        int line_idx = 0;
        bool first = true;
        while (getline(file, line)) {
            line_idx++;
            bool skip = false;
            for (int i = 0; i < line.size(); i++) {
                if (deleteable_char(line[i])) { line.replace(i, 1, " "); }
                if (line[i] >= '0' && line[i] <= '9') { skip = true; }
                if (line[i] >= 'A' && line[i] <= 'Z') { line[i] = tolower(line[i]); }
            }
            istringstream iss(line);
            string word; 
            while(iss >> word) {
              if (!skip) 
              {
                if (word.size() <= 20) 
                {
                    if (!table->contains(word)) 
                    {
                      if (!first) { outfile << "\n"; }
                      first = false;
                      outfile << "Unknown word at line " << line_idx << ": " << word;
                    }
                } 
                else 
                {
                    if (!first) { outfile << "\n"; }
                    first = false;
                    outfile << "Long word at line " << line_idx << ", starts: " << word.substr(0, 20);
                }
              } 
            }
        }
        file.close();
        clock_t end = clock();
        double time_elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "Total time (in seconds) to check document: " << time_elapsed << "\n";
    }
    outfile.close();
}

int parse_dictionary(hashTable *table) {
  string file;
  cout << "Dictionary file: ";
  cin >> file;
  fstream new_file;
  new_file.open(file, ios::in);
  if (new_file.is_open()) {
    clock_t start = clock();
    string line;
    while (getline(new_file, line)) {
      bool skip = false;
      for (int i = 0; i < line.size(); i++) {
                if (deleteable_char(line[i]) || line.size() > 20) { skip = true; }
                if (line[i] >= 'A' && line[i] <= 'Z') { line[i] = tolower(line[i]); }
      }
      string& temp = line;
      if (!skip) {
        table->insert(temp, nullptr);
      }
    }
    clock_t end = clock();
    double time_elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << time_elapsed << "\n";
  } else { return 1; }
  new_file.close();
  return 0;
}

int main() {
    hashTable table(25000);
    parse_dictionary(&table);
    parse_doc(&table);
    return 0;
}
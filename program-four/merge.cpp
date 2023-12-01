#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <stack>
#include <vector>

#define MAX_A 1000
#define MAX_B 1000
#define MAX_C 2000

using namespace std;

bool matrix[MAX_A + 1][MAX_B + 1]; // Make room for extra top node

// s1 is first inp, s2 is 3rd inp, s3 is test
string isInterleaved(string s1, string s2, string s3) {
	int s1_len = s1.length();
	int s2_len = s2.length();
	int s3_len = s3.length();

	if (s3_len != (s1_len + s2_len)) { return "*** NOT A MERGE ***\n"; }

	// Will be using the same matrix for multiple computations
	// thus, need to zero all elements after each run
	for (int r = 0; r < MAX_A + 1; r++) {
		for (int c = 0; c < MAX_B + 1; c++) {
			matrix[r][c] = false;
		}
	}

	matrix[0][0] = true;

	// Fill out the first row
	for (int j = 1; j <= s1_len; j++) {
		if ((s1[j-1] == s3[j-1]) && matrix[0][j-1]) {
			matrix[0][j] = true;		
		}
	}
	// Fill out the first col
	for (int i = 1; i <= s2_len; i++) {
		if ((s2[i-1] == s3[i-1]) && matrix[i-1][0]) {
			matrix[i][0] = true;		
		}
	}

	// Fill out matrix
	for (int i = 1; i <= s2_len; i++) {
		for (int j = 1; j <= s1_len; j++) {
			// Match in s1 means check left item
			if (s1[j-1] == s3[j+i-1]) {
				if (matrix[i][j-1]) {
					matrix[i][j] = true;
				}
			}
			// Match in s2 means check above item
			if (s2[i-1] == s3[j+i-1]) {
				if (matrix[i-1][j]) {
					matrix[i][j] = true;
				}
			}
		}
	}
	
	// Print out dynamic programming table for easier debugging
	/*
	cout << "\n    ";

	for (int i = 0; i < s1_len; i++) {
		cout << s1[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i <= s2_len; i++) {
		if (i == 0) {
			cout << "  ";
		} else {
			cout << s2[i-1] << " ";
		}
		for (int j = 0; j <= s1_len; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	*/

	// Return true if match, return false if not
	// Match condition is: matrix[s1_len][s2_len]
	
	/* Come up with a way to determine which string led us where */
	string fs = "";

	if (matrix[s2_len][s1_len]) {
//		stack<char> final_str;
		int i = s2_len;
		int j = s1_len;
		// check top
		while ((i+j) >= 0) {
			if (matrix[i-1][j]) {
//				final_str.push(s2[i-1]);
				fs = s2[i-1] + fs;
				i--;
			} else {
				//cout << char(toupper(s1[j-1])) << " ";
//				final_str.push(char(toupper(s1[j-1])));
				fs = (char)(toupper(s1[j-1])) + fs;
				j--;
			}
		}
		// Put items into a new string 
//		while (!final_str.empty()) {
//			fs += (char)(final_str.top());
//			final_str.pop();
//		}
		return fs += '\n';
	} else {
		return "*** NOT A MERGE ***\n";
	}
}

void parse_doc() {
    fstream inpFile;
    cout << "Enter name of input file: ";
    string inp;
    cin >> inp;
    inpFile.open(inp, ios::in);

    fstream outFile;
    cout << "Enter name of ouput file: ";
    string out;
    cin >> out;
    outFile.open(out, ios::out);

    string line;
    int i = 0;
    string args[3] = {""};
    while (getline(inpFile, line)) {
	    if (i == 0) { args[i] = line; }
	    if (i == 1) { args[i] = line; }
	    if (i == 2) { args[i] = line; }
	    if (i == 2) {
		outFile << isInterleaved(args[0], args[1], args[2]);
		i = 0;
		for (int j = 0; j <= 2; j++) {
			args[j] = "";
		}
	    } else { i++; }
    }
    inpFile.close();
    outFile.close();
}


int main() {
	// a -> b -> c
//	cout << isInterleaved("mbn", "abx", "ambbnx");
/*	isInterleaved("chocolate", "chips", "cchocholaiptes");
	isInterleaved("chocolate", "chips", "bananasplit");	
	isInterleaved("abac", "bad", "ababacd");	
	isInterleaved("hello", "world", "wohrelldol");	
	isInterleaved("ab", "ba", "abab");	
	isInterleaved("zzzzzzzzzzzzzzzzzzzzab",
		      "zzzzzzzzzzzzzzzzzzzzac",
		      "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzacab");
	isInterleaved("zzzzzzzzzzzzzzzzzzzzabc",
		      "zzzzzzzzzzzzzzzzzzzzacb",
		      "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzabcbac");
		      */
	parse_doc();
	return 0;
}

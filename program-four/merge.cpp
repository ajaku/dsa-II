#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>

#define MAX_A 1000
#define MAX_B 1000
#define MAX_C 2000

using namespace std;

bool matrix[101][101]; // Make room for extra top node

// s1 is first inp, s2 is 3rd inp, s3 is test
void isInterleaved(const string s1, const string s2, const string s3) {
        int s1_len = s1.length();
        int s2_len = s2.length();
        int s3_len = s3.length();

        if (s3_len != (s1_len + s2_len)) { cout << "NO MATCH\n"; }

        matrix[0][0] = true;

	/*    s3 = ambbnx
	 *
	 *    s1 m b n
	 *  s2 T 
	 *   a	      
	 *   b
	 *   x 
	 *
	 */

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
		for (int c = 0; c <= s1_len; c++) {
			cout << matrix[i][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	// a -> b -> c
	const string s1 = "hello";
	// x -> y -> z
	const string s2 = "world";
	// Would be a valid version
	const string concat = "wohrelldol";
	isInterleaved(s1, s2, concat);
	return 0;
}

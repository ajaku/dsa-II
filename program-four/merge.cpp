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


// Code below follows directly from:
// https://www.youtube.com/watch?v=U49f4WpAhV4

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
	
	// Initialization Step
	for (int r = 1; r <= s1_len; r++) {
		if(s3[r-1] == s1[r-1]) {
			matrix[0][r] = matrix[0][r-1];
		}
	}
	for (int c = 1; c <= s2_len; c++) {
		if(s3[c-1] == s2[c-1]) {
			matrix[c][0] = matrix[c-1][0];
		}
	}
        for (int r = 1; r <= s1_len; r++) {
            for (int c = 1; c <= s2_len; c++) {

		    if (s3[r+c-1] == s2[r-1]) {
			matrix[r][c] = matrix[r-1][c];
		    }

		    if (s3[r+c-1] == s1[c-1]) {
		    	if (!matrix[r][c]) { 
				matrix[r][c] = matrix[r][c-1]; 
			}
		    }

		}
        }

	// Print out dynamic programming table for easier debugging

	cout << "\n  ";

	for (int i = 0; i < s1_len; i++) {
		cout << s1[i] << " ";
	}
	cout << "\n";
	for (int r = 0; r < s2_len; r++) {
		cout << s2[r] << " ";
		for (int c = 0; c < s1_len; c++) {
			cout << matrix[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	// a -> b -> c
	const string s1 = "chocolate";
	// x -> y -> z
	const string s2 = "chips";
	// Would be a valid version
	const string concat = "cchocholaiptes";
	isInterleaved(s1, s2, concat);
	return 0;
}

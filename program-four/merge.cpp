#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <string>
#include <cstdlib>

#include "hash.h"

#define MAX_A 1000
#define MAX_B 1000
#define MAX_C 2000

using namespace std;

bool matrix[101][101]; // Make room for extra top node

void isInterleaved(string s1, string s2, string s3) {
	cout << "S1: " << s1 << "\n";
	cout << "S2: " << s2 << "\n";
        int s1_len = s1.length();
        int s2_len = s2.length();
        int s3_len = s3.length();

        if (s3_len != (s1_len + s2_len)) { cout << "NO MATCH\n"; }

        matrix[0][0] = true;

        // Iterate through s1
        for (int c = 0; c < s1_len; c++) {
            // Iterate through s2
            for (int r = 0; r < s2_len; r++) {
                if (s1[r] == s3[r+c]) {
		    /* Conditions for false:
		     *
		     * 
		     *
		     */



                    if (matrix[(r-1)+1][(c)+1]) {
                        matrix[(r)+1][(c)+1] == true;
                    } else if (matrix[(r)+1][(c-1)+1]) {
                        matrix[(r)+1][(c)+1] == true;
                    }
                } else if (s2[c] == s3[r+c]) {
                    if (matrix[(r-1)+1][(c)+1]) {
                        matrix[(r)+1][(c)+1] == true;
                    } else if (matrix[(r)+1][(c-1)+1]) {
                        matrix[(r)+1][(c)+1] == true;
                    }
                }
            }
        }
}

int main() {
	// a -> b -> c
	string s1 = "mbn";
	// x -> y -> z
	string s2 = "abx";
	// Would be a valid version
	string concat = "ambbnx";
	isInterleaved(s1, s2, concat);
	return 0;
}

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

	/*    
	 * Known Example:
	 *    s3 = ambbnx
	 *    s1 = mbn
	 *    s2 = abx
	 *    
	 *      a m b b n x
	 * s1 = m b n
	 * s2 = a b x   
	 * r = 0; c = 0;
	 *
	 *      m b b n x
	 *
	 * s1 = m b n
	 * s2 = b x   
	 * r = 1; c = 0; 
	 *
	 *      b b n x
	 * s1 = b n
	 * s2 = b x   
	 * r = 1; c = 1;
	 * (Can branch both ways from here!)
	 *
	 *      b n x  or      b n x
	 * s1 = b n	  s1 = n
	 * s2 = x         s2 = b x 
	 * r = 2; c = 1;  r = 1; c = 2;
	 *
	 *      n x  or        n x
	 * s1 = n	  s1 = n
	 * s2 = x         s2 = x 
	 * r = 2; c = 2;  r = 2; c = 2; 
	 *
	 *      x  or          x
	 * s1 = 	  s1 = 
	 * s2 = x         s2 = x 
	 * r = 2; c = 3;  r = 2; c = 3; 
	 *
	 *        or          
	 * s1 = 	  s1 = 
	 * s2 =           s2 =  
	 * r = 3; c = 3;  r = 3; c = 3; 
	 *
	 * MATCH!
	 *
	 *       1 2 3
	 *    s1 m b n
	 *  s2 T 
	 * 1 a T T T	     
	 * 2 b   T T T
	 * 3 x       T
	 *
	 *
	 *       1 2 3
	 *    s1 m b n
	 *  s2 T F F F
	 * 1 a T T T F	       
	 * 2 b F T T T
	 * 3 x F F F T
	 *
	 * Sable Example:
	 *
	 *    s3 = ababacd 
	 *    s1 = abac 
	 *    s2 = bad
	 *    
	 *      a b a b a c d
	 * s1 = a b a c   
	 * s2 = b a d 
	 *
	 *      b a b a c d
	 * s1 = b a c   
	 * s2 = b a d 
	 * (BRANCH!)
	 *
	 *      a b a c d            a b a c d
	 * s1 = a c   		s1 = b a c
	 * s2 = b a d		s2 = a d
	 *
	 *      b a c d              b a c d
	 * s1 = c   		s1 = b a c
	 * s2 = b a d		s2 = d
	 *
	 *
	 *      a c d                a c d
	 * s1 = c   		s1 = b a c
	 * s2 = a d		s2 = 
	 * 			(BRANCH IS DEAD)
	 *
	 *      c d            
	 * s1 = c   		
	 * s2 = d	
	 *
	 *      d            
	 * s1 =   		
	 * s2 = d	
	 *
	 * MATCH!
	 *
	 *
	 *       1 2 3 4
	 *    s1 a b a c 
	 *  s2 T 
	 * 1 b 	       
	 * 2 a 
	 * 3 d
	 *
	 *   First iterate through characters of s1,
	 *   see if they are equal to respective char at idx-1
	 *   and if the previous token (to the left) was true
	 *
	 *   Next iterate through characters of s2,
	 *   repeat same process above but for columns
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
}

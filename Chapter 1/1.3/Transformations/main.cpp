/*
ID: andreww7
PROB: transform
LANG: C++
*/

#include <fstream>
#include <iostream>
using namespace std;

/// function declarations
bool isSame(char** bt, char** at, int sideLength);
char** reflectGrid(char **bt, int sideLength);
char** rotateGrid(char** bt, int sideLength);
int transformation(char** bt, char** at, int sideLength);

int main() { 

	/* overhead initializations and inputs*/
	ifstream fin("transform.in");
	ofstream fout("transform.out");

	int N; 
	fin >> N;

	char** bt = new char*[10]; // before transformation (space of 10 required)
	char** at = new char*[10]; // after transformation

	for (int i = 0; i < 10; i++) { 
		bt[i] = new char[10];
		at[i] = new char[10];
	}

	/* accept input */
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) {
			fin >> bt[i][j]; 
		}
	}

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) {
			fin >> at[i][j]; 
		}
	}

	fout << transformation(bt, at, N) << "\n";

	return 0;
}

bool isSame(char** bt, char** at, int sideLength) {
	// determine whether two char grids, a and b, are the same.
	for (int i = 0; i < sideLength; i++) { 
		for (int j = 0; j < sideLength; j++) {
			if (bt[i][j] != at[i][j]) return false;
			// if one char differs, immediately return false
		}
	} 
	return true;
}

/// function definitions
char** reflectGrid(char **bt, int sideLength) { 
	char** reflectedGrid = new char*[sideLength]; 
	
	for (int i = 0; i < sideLength; i++) { 
		reflectedGrid[i] = new char[sideLength];
	}

	for (int i = 0; i < sideLength; i++) { 
		for (int j = 0; j < sideLength; j++) { 
			char element = bt[i][j];
			reflectedGrid[i][sideLength - j - 1] = element;
		}
	}
	return reflectedGrid;
}

char** rotateGrid(char** bt, int sideLength) { 
	// rotate 90 degrees CW
	char** rotatedGrid = new char*[sideLength];

	for (int i = 0; i < sideLength; i++) { 
		rotatedGrid[i] = new char[sideLength];
	}

	for (int i = 0; i < sideLength; i++) { 
		for (int j = 0; j < sideLength; j++) {
			char element = bt[i][j];
			rotatedGrid[j][sideLength - i - 1] = element; // rotate each square individually.
		}
	}
	return rotatedGrid;
}

int transformation(char** bt, char** at, int sideLength) { 
// determine which transformation (1 - 6), which when applied
// to bt, yields at. If none, return 7.
	if (isSame(rotateGrid(bt, sideLength), at, sideLength)) {
		return 1;// 90 deg
	}
	if (isSame(rotateGrid(rotateGrid(bt, sideLength), sideLength), at, sideLength)) {
	 	return 2; // 90 + 90 deg
	}
	if (isSame(rotateGrid(rotateGrid(rotateGrid(bt, sideLength), sideLength), sideLength), at, sideLength)) {
		return 3;
	}
	if (isSame(reflectGrid(bt, sideLength), at, sideLength)) {
		return 4;// reflect
	}
	if (isSame(rotateGrid(reflectGrid(bt, sideLength), sideLength), at, sideLength) ||
			 isSame(rotateGrid(rotateGrid(reflectGrid(bt, sideLength), sideLength), sideLength), at, sideLength) ||
			 isSame(rotateGrid(rotateGrid(rotateGrid(reflectGrid(bt, sideLength), sideLength), sideLength), sideLength), at, sideLength)){
		return 5;
	} 
	if (isSame(bt, at, sideLength)) return 6;
	else return 7;
}
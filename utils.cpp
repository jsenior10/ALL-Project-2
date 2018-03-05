#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.h"

using namespace std;

void Utility::printMap(vector< vector<int> > map) {
    for(int i=0; i<map.size(); i++) {
	for(int j=0; j<map[i].size(); j++) {
	    cout << map[i][j] << " ";
	}
    
	cout << endl;
    }
}

int Utility::randomNumber(int min, int max) {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return (rand() % (max-min+1)) + min;
}

float Utility::randomProbability() {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return rand() / (RAND_MAX + 1.0);
}

bool Utility::isFieldOverlapping(vector<int> field1, vector<int> field2) { //checks to make sure that the rooms are valid and dont do some shit like overlap and make some retarded room that is impossible to get out of
    sort(field1.begin(), field1.end()); sort(field2.begin(), field2.end());
    if(field1[0] == field2[0]) {
	return true;
    }
    else if(field1[0] < field2[0]) {
	if(field1[1] >= field2[0]) { //Max of field 1 is greater than min of field 2
	    return true;
	}
	else {
	    return false; //Max and min of field 1 are lower than min field 2
	}
    }
    else {
	if(field2[1] >= field1[0]) {
	    return true;
	}
	else {
	    return false;
	}
    }
}



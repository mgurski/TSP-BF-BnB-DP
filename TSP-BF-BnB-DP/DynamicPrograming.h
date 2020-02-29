#ifndef DYNAMICPROGRAMING_H
#define DYNAMICPROGRAMING_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class DynamicPrograming {

private:

	int instance_size;

	vector<vector<int>> parents_memory;

	vector<vector<int>> matrix;

	int IMAX = 999999;

	int visited_all;

	vector<vector<int>> dp_memory;

public:

	DynamicPrograming(int, vector<vector<int>>);

	vector<int> dp();

	int dp_recursion(int, int);

	vector<int> get_path();

};


#endif

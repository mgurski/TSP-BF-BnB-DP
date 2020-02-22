#ifndef TRAVELINGSALESMANPROBLEM_H
#define TRAVELINGSALESMANPROBLEM_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


class TravelingSalesmanProblem {

protected:

	int instance_size;

	vector<vector<int>> matrix;


public:

	int get_instance_size() {
		return instance_size;
	}

	vector<vector<int>> get_matrix() {
		return matrix;
	}

	void print();

	void read(string);

	int distance(vector<int>, int road_size);

};

#endif

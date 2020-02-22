#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include "TravelingSalesmanProblem.h"
#include <algorithm>

class BruteForce {

private:

	int instance_size;

	vector<vector<int>> matrix;

	int best_cost;

	vector<int> best_route;

	int check_cost;

public:

	BruteForce(int, vector<vector<int>>);

	vector<int> bruteforce();

	vector<int> dfs_bruteforce();

	int distance(vector<int>, int);

	void dfs(vector<int>, vector<int>, int);


};


#endif

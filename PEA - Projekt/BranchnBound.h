#ifndef BRANCHNBOUND_H
#define BRANCHNBOUND_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 999999;

struct PrioQ {
	int cost;
	vector<int> route;
	vector<int> vertices_to_check;
};

struct MyComp
{
	bool operator ()(const PrioQ& cost, const PrioQ& cost2)
	{
		if (cost.cost > cost2.cost) return true;
	
		return false;
	}
};


class BranchnBound {

private:

	PrioQ current;

	priority_queue<PrioQ, vector<PrioQ>, MyComp> prio_queue_for_recursion;

	int instance_size;

	vector<vector<int>> matrix;

	vector<int> best_route;

	int upper_bound;

	int check_cost;

public:

	BranchnBound(int, vector<vector<int>>);

	int distance(vector<int>, int);

	int partial_distance(vector<int>, int);

	vector<int> bnb_dfs();

	void bnb_dfs_recursion(vector<int>, vector<int>);

	vector<int> bnb_least_cost_first();

};

#endif 

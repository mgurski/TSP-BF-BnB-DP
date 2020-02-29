#include "DynamicPrograming.h"


DynamicPrograming::DynamicPrograming(int size, vector<vector<int>> mat)
{
	instance_size = size;
	matrix = mat;
}

vector<int> DynamicPrograming::dp() {

	vector<int> route;

	visited_all = (1 << instance_size) - 1;
	
	for (int i = 0; i < (1 << instance_size); i++) {
		for (int j = 0; j < instance_size; j++) {
			route.push_back(-1);
		}
		dp_memory.push_back(route);
		parents_memory.push_back(route);
		route.clear();
	}

	int cost = dp_recursion(1, 0);

	route = get_path();
	
	return route;

}

int DynamicPrograming::dp_recursion(int mask, int current_vertice) {

	if (mask == visited_all) {
		return matrix[current_vertice][0];
	}

	if (dp_memory[mask][current_vertice] != -1) {
		return dp_memory[mask][current_vertice];
	}

	int cost = IMAX;

	for (int city = 0; city < instance_size; city++) {

		if ((mask & (1 << city)) == 0) {

			int newcost = matrix[current_vertice][city] + dp_recursion(mask | (1 << city), city);
			cost = min(cost, newcost);

			if (newcost == cost) {
				dp_memory[mask][current_vertice] = cost;
				parents_memory[mask][current_vertice] = city;
			}
		}
	}

	return cost;
}

vector<int> DynamicPrograming::get_path()
{
	vector<int> best_route;
	int current_vertice = 0;
	int mask = 1;

	best_route.push_back(current_vertice + 1);

	int full_mask = (1 << instance_size) - 1;

	while (mask != visited_all) {
		current_vertice = parents_memory[mask][current_vertice];
		best_route.push_back(current_vertice+1);
		mask = mask | (1 << current_vertice);
	}

	return best_route;
}


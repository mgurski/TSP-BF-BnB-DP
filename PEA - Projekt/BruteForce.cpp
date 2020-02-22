#include "BruteForce.h"

BruteForce::BruteForce(int size, vector<vector<int>> mat)
{
	instance_size = size;
	matrix = mat;
}

int BruteForce::distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size - 1; i++) {
		sum += matrix[salesmans_route[i] - 1][salesmans_route[i + 1] - 1];
	}
	sum += matrix[salesmans_route[route_size - 1] - 1][salesmans_route[0] - 1];

	return sum;
}


vector<int> BruteForce::bruteforce()
{
	vector<int> current_route;

	vector<int> best_route;

	int current_cost;

	for (int i = 0; i < instance_size; i++) {
		current_route.push_back(i + 1);
		best_route.push_back(i + 1);
	}

	int best_cost = distance(current_route, instance_size);

	do {
		current_cost = distance(current_route, instance_size);

		if (current_cost < best_cost) {
			best_cost = current_cost;
			best_route = current_route;
		}

	} while (next_permutation(current_route.begin() + 1, current_route.end()));


	return best_route;
}

vector<int> BruteForce::dfs_bruteforce()
{
	vector<int> vertices_to_check;

	for (int i = 1; i < instance_size; i++) {
		vertices_to_check.push_back(i + 1);
	}

	best_cost = 99999;

	vector<int> route = {};

	route.push_back(1);

	for (int j = 0; j < instance_size - 1; j++) {
		dfs(vertices_to_check, route, vertices_to_check[j]);
	}

	return best_route;
}

void BruteForce::dfs(vector<int> vertices_to_check, vector<int> current_route, int current_vertice)
{
	current_route.push_back(current_vertice);

	for (int i = 0; i < vertices_to_check.size(); i++) {
		if (vertices_to_check[i] == current_vertice) {
			vertices_to_check.erase(vertices_to_check.begin() + i);
		}
	}

	if (vertices_to_check.size() == 0) {
		check_cost = distance(current_route, current_route.size());

		if (check_cost < best_cost) {
			best_cost = check_cost;
			best_route = current_route;
		}

	}
	else {
		for (int j = 0; j < vertices_to_check.size(); j++) {
			dfs(vertices_to_check, current_route, vertices_to_check[j]);
		}
	}
}

#include "BranchnBound.h"

int BranchnBound::distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size-1; i++) {
		sum += matrix[salesmans_route[i]][salesmans_route[i+1]];
	}
	sum += matrix[salesmans_route[route_size - 1]][salesmans_route[0]];

	return sum;
}

int BranchnBound::partial_distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size - 1; i++) {
		sum += matrix[salesmans_route[i]][salesmans_route[i + 1]];
	}

	return sum;
}

BranchnBound::BranchnBound(int size, vector<vector<int>> mat)
{
	instance_size = size;
	matrix = mat;
}

vector<int> BranchnBound::bnb_dfs()
{
	vector<int> vertices_to_check;

	vector<int> standard_route;

	for (int i = 0; i < instance_size; i++) {
		standard_route.push_back(i);
	}

	upper_bound = distance(standard_route, standard_route.size());

	for (int i = 1; i < instance_size; i++) {
		vertices_to_check.push_back(i);
	}

	vector<int> route;

	route.push_back(0);

	bnb_dfs_recursion(vertices_to_check, route);

	for (int i = 0; i < instance_size; i++) {
		best_route[i] = best_route[i] + 1;
	}

	return best_route;

}

void BranchnBound::bnb_dfs_recursion(vector<int> vertices_to_check, vector<int> current_route)
{

	vector<int> next_route = current_route;
	vector<int> next_vertices_to_check = vertices_to_check;

	int lower_bound=0, min_in_row=0;

	if (vertices_to_check.size() > 0) {
		for (int i = 0; i < vertices_to_check.size(); i++) {

			next_route.push_back(vertices_to_check[i]);
			next_vertices_to_check.erase(next_vertices_to_check.begin() + i);
			
			//partial distance cost
			for (int j = 0; j < next_route.size() - 1; j++) {
				lower_bound += matrix[next_route[j]][next_route[j + 1]];
			}

			//minimum possible cost for the last vertice in the partial route. If the route is not complete, this vertice cannot be the one to return to the starting vertice
			if (next_vertices_to_check.size() > 0) {
				min_in_row = matrix[next_route[next_route.size() - 1]][next_vertices_to_check[0]];

				for (int j = 0; j < vertices_to_check.size(); j++) {
					if ((min_in_row > matrix[next_route[next_route.size() - 1]][vertices_to_check[j]]) && (matrix[next_route[next_route.size() - 1]][vertices_to_check[j]] != -1)) {
						min_in_row = matrix[next_route[next_route.size() - 1]][vertices_to_check[j]];
					}
				}

				lower_bound += min_in_row;
			}
			//costs for the other remaining vertices. They can go to other remaining vertices or to the starting vertice
			for (int j = 0; j < next_vertices_to_check.size(); j++) {
				min_in_row = matrix[next_vertices_to_check[j]][0];
				for (int k = 0; k < next_vertices_to_check.size(); k++) {
					if ((matrix[next_vertices_to_check[j]][next_vertices_to_check[k]] < min_in_row) && matrix[next_vertices_to_check[j]][next_vertices_to_check[k]] != -1) {
						min_in_row = matrix[next_vertices_to_check[j]][next_vertices_to_check[k]];
					}
				}
				lower_bound += min_in_row;
			}
			
			if (lower_bound < upper_bound) {
				bnb_dfs_recursion(next_vertices_to_check, next_route);
			}

			next_route = current_route;
			next_vertices_to_check = vertices_to_check;
			lower_bound = 0;
		}
	}
	else {

		lower_bound = distance(current_route, current_route.size());

		if (lower_bound < upper_bound) {
			upper_bound = lower_bound;
			best_route = current_route;
		}
	}
}

vector<int> BranchnBound::bnb_least_cost_first()
{
	vector<int> best_route;

	for (int i = 0; i < instance_size; i++) {
		best_route.push_back(i);
	}

	upper_bound = distance(best_route, best_route.size());

	PrioQ current;
	priority_queue<PrioQ, vector<PrioQ>, MyComp> prio_queue;
	vector<int> current_route, next_route, vertices_to_check, next_vertices_to_check;
	int lower_bound = 0, min_in_row = 0;


	current_route.push_back(0);

	for (int i = 1; i < instance_size; i++) {
		vertices_to_check.push_back(i);
	}

	current.route = current_route;
	current.cost = 0;
	current.vertices_to_check = vertices_to_check;

	prio_queue.push(current);

	while (!prio_queue.empty())
	{
		current_route = prio_queue.top().route;
		vertices_to_check = prio_queue.top().vertices_to_check;
		lower_bound = prio_queue.top().cost;
		prio_queue.pop();

		if (vertices_to_check.size() == 0) {
			lower_bound = distance(current_route, current_route.size());
		}

		if (lower_bound < upper_bound) {
			if (vertices_to_check.size() > 0) {
				for (int i = 0; i < vertices_to_check.size(); i++) {

					next_route = current_route;
					next_route.push_back(vertices_to_check[i]);
					next_vertices_to_check = vertices_to_check;
					next_vertices_to_check.erase(next_vertices_to_check.begin() + i);
					lower_bound = 0;
					
					//partial distance cost
					for (int j = 0; j < next_route.size() - 1; j++) {
						lower_bound += matrix[next_route[j]][next_route[j + 1]];
					}

					//minimum possible cost for the last vertice in the partial route. If the route is not complete, this vertice cannot be the one to return to the starting vertice
					if (next_vertices_to_check.size() > 0) {
						min_in_row = matrix[next_route[next_route.size() - 1]][next_vertices_to_check[0]];

						for (int j = 0; j < vertices_to_check.size(); j++) {
							if ((min_in_row > matrix[next_route[next_route.size() - 1]][vertices_to_check[j]]) && (matrix[next_route[next_route.size() - 1]][vertices_to_check[j]] != -1)) {
								min_in_row = matrix[next_route[next_route.size() - 1]][vertices_to_check[j]];
							}
						}

						lower_bound += min_in_row;
					}
					//costs for the other remaining vertices. They can go to other remaining vertices or to the starting vertice
					for (int j = 0; j < next_vertices_to_check.size(); j++) {
						min_in_row = matrix[next_vertices_to_check[j]][0];
						for (int k = 0; k < next_vertices_to_check.size(); k++) {
							if ((matrix[next_vertices_to_check[j]][next_vertices_to_check[k]] < min_in_row) && matrix[next_vertices_to_check[j]][next_vertices_to_check[k]] != -1) {
									min_in_row = matrix[next_vertices_to_check[j]][next_vertices_to_check[k]];
							}
						}
						lower_bound += min_in_row;
					}
					
					if (lower_bound < upper_bound) {
						current.route = next_route;
						current.cost = lower_bound;
						current.vertices_to_check = next_vertices_to_check;
						prio_queue.push(current);
					}

				}
			}
			else {
					upper_bound = lower_bound;
					best_route = current_route;
			}
		}
		else {
			break;
		}
	}

	for (int i = 0; i < best_route.size(); i++) {
		best_route[i] = best_route[i] + 1;
	}

	return best_route;
}
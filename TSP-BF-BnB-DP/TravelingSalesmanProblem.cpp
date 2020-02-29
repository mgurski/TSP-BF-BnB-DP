#include "TravelingSalesmanProblem.h"


void TravelingSalesmanProblem::print()
{

	for (int i = 0; i < instance_size; i++) {
		for (int j = 0; j < instance_size; j++) {
			cout << setw(4) << matrix[i][j];
		}
		cout << endl;
	}

}

void TravelingSalesmanProblem::read(string name)
{

	int distance_reader;
	string instance_name;
	vector<int> tmp;

	ifstream file;

	file.open(name + ".txt");

	if (!file) {
		cout << "Unable to open file" << endl;
	}
	else {

		file >> instance_name;
		file >> instance_size;

		for (int i = 0; i < instance_size; i++) {
			for (int j = 0; j < instance_size; j++) {

				file >> distance_reader;
				tmp.push_back(distance_reader);
			}

			matrix.push_back(tmp);
			tmp.clear();
		}

	}

	file.close();

}

int TravelingSalesmanProblem::distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size-1; i++) {
		sum += matrix[salesmans_route[i]-1][salesmans_route[i+1]-1];
	}
	sum += matrix[salesmans_route[route_size - 1]-1][salesmans_route[0]-1];

	return sum;
}

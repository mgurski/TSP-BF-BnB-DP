#include <iostream>
#include "TravelingSalesmanProblem.h"
#include <ctime>
#include "BranchnBound.h"
#include "DynamicPrograming.h"
#include "BruteForce.h"
#include "Timemeasurement.h"
#include <string>

using namespace std;

vector<int> random_route(int instance_size) {

	vector<int> tmp;
	vector<int> random_route;
	int random_number;


	for (int i = 0; i < instance_size; i++) {
		tmp.push_back(i + 1);
	}

	for (int j = 0; j < instance_size; j++) {
		random_number = rand() % (instance_size - j);
		random_route.push_back(tmp[random_number]);
		tmp.erase(tmp.begin()+random_number);
	}

	return random_route;
}

void DP_auto_tests() {

	TravelingSalesmanProblem* etap0;
	DynamicPrograming* dp;
	Timemeasurement time;
	string file_name;

	//DP - tests

	int number_of_tests = 10;

	double* time_tab = new double[number_of_tests];
	int* cost_tab = new int[number_of_tests];
	double suma = 0;

	vector<int> best_route;

	for (int i = 10; i < 19; i++) {
		file_name = "data" + to_string(i);
		cout << "Testing Dynamic Programming, at " + file_name + "..." << endl;
		for (int j = 0; j < number_of_tests; j++) {
			etap0 = new TravelingSalesmanProblem();
			etap0->read(file_name);
			dp = new DynamicPrograming(etap0->get_instance_size(), etap0->get_matrix());

			time.time_start();
			best_route = dp->dp();
			time.time_stop();

			cost_tab[j] = etap0->distance(best_route, best_route.size());
			time_tab[j] = time.get_time();
			delete etap0;
			delete dp;
		}
		ofstream zapis;
		zapis.open("DP" + file_name + ".txt");
		for (int j = 0; j < number_of_tests; j++) {
			zapis << "Wynik " << time_tab[j] << "Koszt " << cost_tab[j] << endl;
			suma += time_tab[j];
		}
		zapis << "sredni wynik = " << suma / number_of_tests << endl;
		zapis.close();
		suma = 0;
	}

}

void BNB_LCF_auto_tests() {

	TravelingSalesmanProblem* etap0;
	BranchnBound* bnb;
	Timemeasurement time;
	string file_name;

	//Branch and Bound - LCF - tests

	int number_of_tests = 10;

	double* time_tab = new double[number_of_tests];
	int* cost_tab = new int[number_of_tests];
	double suma = 0;

	vector<int> best_route;

	for (int i = 10; i < 19; i++) {
		if (i != 17) {
			file_name = "data" + to_string(i);
			cout << "Testing Branch and bound - LCF - iterative, at " + file_name + "..." << endl;
			for (int j = 0; j < number_of_tests; j++) {
				etap0 = new TravelingSalesmanProblem();
				etap0->read(file_name);
				bnb = new BranchnBound(etap0->get_instance_size(), etap0->get_matrix());

				time.time_start();
				best_route = bnb->bnb_least_cost_first();
				time.time_stop();

				cost_tab[j] = etap0->distance(best_route, best_route.size());
				time_tab[j] = time.get_time();
				delete etap0;
				delete bnb;
			}
			ofstream zapis;
			zapis.open("Branchandbound-LCF-iterative" + file_name + ".txt");
			for (int j = 0; j < number_of_tests; j++) {
				zapis << "Wynik " << time_tab[j] << "Koszt " << cost_tab[j] << endl;
				suma += time_tab[j];
			}
			zapis << "sredni wynik = " << suma / number_of_tests << endl;
			zapis.close();
			suma = 0;
		}
	}

}

void BNB_DFS_auto_tests() {

	TravelingSalesmanProblem* etap0;
	BranchnBound* bnb;
	Timemeasurement time;
	string file_name;

	//Branch and Bound - DFS - tests

	int number_of_tests = 10;

	double* time_tab = new double[number_of_tests];
	int* cost_tab = new int[number_of_tests];
	double suma = 0;

	vector<int> best_route;

	for (int i = 10; i < 19; i++) {
		file_name = "data" + to_string(i);
		cout << "Testing Branch and bound - DFS - recursion, at " + file_name + "..." << endl;
		for (int j = 0; j < number_of_tests; j++) {
			etap0 = new TravelingSalesmanProblem();
			etap0->read(file_name);
			bnb = new BranchnBound(etap0->get_instance_size(), etap0->get_matrix());

			time.time_start();
			best_route = bnb->bnb_dfs();
			time.time_stop();

			cost_tab[j] = etap0->distance(best_route, best_route.size());
			time_tab[j] = time.get_time();
			delete etap0;
			delete bnb;
		}
		ofstream zapis;
		zapis.open("Branchandbound-DFS" + file_name + ".txt");
		for (int j = 0; j < number_of_tests; j++) {
			zapis << "Wynik " << time_tab[j] << "Koszt " << cost_tab[j] << endl;
			suma += time_tab[j];
		}
		zapis << "sredni wynik = " << suma / number_of_tests << endl;
		zapis.close();
		suma = 0;
	}

}

void BF_DFS_auto_tests() {

	TravelingSalesmanProblem* etap0;
	BruteForce* bf;
	Timemeasurement time;
	string file_name;

	//BF - DFS - tests

	int number_of_tests = 10;

	double* time_tab = new double[number_of_tests];
	int* cost_tab = new int[number_of_tests];
	double suma = 0;

	vector<int> best_route;

	for (int i = 10; i < 13; i++) {
		file_name = "data" + to_string(i);
		cout << "Testing BF - DFS at " + file_name + "..." << endl;
		for (int j = 0; j < number_of_tests; j++) {
			etap0 = new TravelingSalesmanProblem();
			etap0->read(file_name);
			bf = new BruteForce(etap0->get_instance_size(), etap0->get_matrix());

			time.time_start();
			best_route = bf->dfs_bruteforce();
			time.time_stop();

			cost_tab[j] = etap0->distance(best_route, best_route.size());
			time_tab[j] = time.get_time();
			delete etap0;
			delete bf;
		}
		ofstream zapis;
		zapis.open("BF-DFS" + file_name + ".txt");
		for (int j = 0; j < number_of_tests; j++) {
			zapis << "Wynik " << time_tab[j] << "Koszt " << cost_tab[j] << endl;
			suma += time_tab[j];
		}
		zapis << "sredni wynik = " << suma / number_of_tests << endl;
		zapis.close();
		suma = 0;
	}

}

void BF_permutations_auto_tests() {

	TravelingSalesmanProblem* etap0;
	BruteForce* bf;
	Timemeasurement time;
	string file_name;

	//BF - permutations - tests

	int number_of_tests = 10;

	double* time_tab = new double[number_of_tests];
	int* cost_tab = new int[number_of_tests];
	double suma = 0;
	
	vector<int> best_route;

	for (int i = 10; i < 13; i++) {
		file_name = "data" + to_string(i);
		cout << "Testing BF - permutation based at " + file_name + "..." << endl;
		for (int j = 0; j < number_of_tests; j++) {
			etap0 = new TravelingSalesmanProblem();
			etap0->read(file_name);
			bf = new BruteForce(etap0->get_instance_size(), etap0->get_matrix());

			time.time_start();
			best_route = bf->bruteforce();
			time.time_stop();

			cost_tab[j] = etap0->distance(best_route, best_route.size());
			time_tab[j] = time.get_time();
			delete etap0;
			delete bf;
		}
		ofstream zapis;
		zapis.open("BF-permutations" + file_name + ".txt");
		for (int j = 0; j < number_of_tests; j++) {
			zapis << "Wynik " << time_tab[j] << "Koszt " << cost_tab[j] << endl;
			suma += time_tab[j];
		}
		zapis << "sredni wynik = " << suma / number_of_tests << endl;
		zapis.close();
		suma = 0;
	}

}


int main() {

	/*

	srand(time(NULL));
	TravelingSalesmanProblem etap0;
	Timemeasurement time;
	string file_name;

	cout << "Enter the file name: " << endl;
	cin >> file_name;

	etap0.read(file_name);

	BruteForce etap1_1(etap0.get_instance_size(), etap0.get_matrix());
	BranchnBound etap1_2(etap0.get_instance_size(), etap0.get_matrix());
	DynamicPrograming etap1_3(etap0.get_instance_size(), etap0.get_matrix());

	etap0.print();

	cout << endl << endl;

	cout << "1. Brute Force - permutations " << endl;
	cout << "2. Brute Force - DFS " << endl;
	cout << "3. Branch and Bound - DFS - Recursion" << endl;
	cout << "4. Branch and Bound - Least cost first - Iterative" << endl;
	cout << "5. DP " << endl;

	vector<int> best_route;

	int choice = 0;

	cin >> choice;

	cout << "The best route is ";

	switch (choice)
	{
	case 1:
		time.time_start();
		best_route = etap1_1.bruteforce();
		time.time_stop();

		for (int i = 0; i < etap0.get_instance_size(); i++) {
			cout << best_route[i] << "  ";
		}

		cout << endl << "and its cost is : " << etap0.distance(best_route, etap0.get_instance_size()) << endl;
		cout << endl << "Duration time : " << time.get_time() << "ms" << endl;
		break;
	case 2:
		time.time_start();
		best_route = etap1_1.dfs_bruteforce();
		time.time_stop();

		for (int i = 0; i < etap0.get_instance_size(); i++) {
			cout << best_route[i] << "  ";
		}

		cout << endl << "and its cost is : " << etap0.distance(best_route, etap0.get_instance_size()) << endl;
		cout << endl << "Duration time : " << time.get_time() << "ms" << endl;
		break;
	case 3:
		time.time_start();
		best_route = etap1_2.bnb_dfs();
		time.time_stop();

		for (int i = 0; i < best_route.size(); i++) {
			cout << best_route[i] << "  ";
		}

		cout << endl << "and its cost is : " << etap0.distance(best_route, best_route.size()) << endl;
		cout << endl << "Duration time : " << time.get_time() << "ms" << endl;
		break;
	case 4:
		time.time_start();
		best_route = etap1_2.bnb_least_cost_first();
		time.time_stop();

		for (int i = 0; i < best_route.size(); i++) {
			cout << best_route[i] << "  ";
		}

		cout << endl << "and its cost is : " << etap0.distance(best_route, best_route.size()) << endl;
		cout << endl << "Duration time : " << time.get_time() << "ms" << endl;
		break;
	case 5:
		time.time_start();
		best_route = etap1_3.dp();
		time.time_stop();

		for (int i = 0; i < best_route.size(); i++) {
			cout << best_route[i] << "  ";
		}

		cout << endl << "and its cost is : " << etap0.distance(best_route, best_route.size()) << endl;
		cout << endl << "Duration time : " << time.get_time() << "ms" << endl;
		break;		
	default:
		break;
	}
	system("PAUSE");
	

	*/

	//tests
	DP_auto_tests();
	BNB_DFS_auto_tests();
	BF_permutations_auto_tests();
	BF_DFS_auto_tests();
	BNB_LCF_auto_tests();

}

#pragma once
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class Timemeasurement {
private:
	high_resolution_clock::time_point t1, t2;

public:
	void time_start();
	void time_stop();
	double get_time();
};

#include "Timemeasurement.h"

void Timemeasurement::time_start()
{
	t1 = high_resolution_clock::now();
}

void Timemeasurement::time_stop()
{
	t2 = high_resolution_clock::now();
}

double Timemeasurement::get_time()
{
	return duration_cast<milliseconds>(Timemeasurement::t2 - Timemeasurement::t1).count();
}

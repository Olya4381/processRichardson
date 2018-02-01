#include "GeneralizedProcessR3.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
void GeneralizedProcessR3::generalized_processR3(int n, double alh)
{
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(0, 100000); // distribute results between 1 and 6 inclusive.
	init_gener_process(alh);

	//введем подсчет времени
	//unsigned int start_time = clock(); // начальное время
	//unsigned int end_time = 0; // конечное время

	for (int i = 0; i < n; i++) {
		int k = distribution_p(dist(gen));
	    add_vertex(sockets_x[k], sockets_y[k],sockets_z[k]);
		calculate_p();
		if (i % 100000 == 0 && i != 0) {
			cout << i << "\n";
			//end_time = clock();
			//std::cout << i << '\t' << (end_time - start_time) / 1000 << '.' << (end_time - start_time) % 1000 << '\n';
			//start_time = end_time;
		}
	}
}

int GeneralizedProcessR3::distribution_p(int rn){
	//генерим точку
	//std::cout << rn << "\n";
	double q = double(rn) / 100000.0;
	double sum = 0;
	int j = 0;
	//определение промежутка куда попало
	for (j = 0; j<(sockets_p.size()-1); j++) {
		if (q >= sum && q<(sum + sockets_p[j] / weight))
		{
			break;
		}
		sum += sockets_p[j] / weight;
	}
	return j;
}

void GeneralizedProcessR3::init_gener_process(double a)
{
	alpha = a;
	calculate_p();
}

void GeneralizedProcessR3::calculate_p()
{
	if (sockets_p.size() != 0)
	{
		sockets_p.clear();
		weight = 0;
	}
	for (int i = 0; i<sockets_x.size(); i++)
	{
		sockets_p.push_back(weight_function(sockets_x[i], sockets_y[i],sockets_z[i]));
		weight += sockets_p[i];
	}
}

double GeneralizedProcessR3::weight_function(int x, int y, int z)
{
	return pow(double(x + y+z), alpha);
}



void GeneralizedProcessR3::processR(int n) {
	for (int i = 0; i < n; i++) {
		int k = rand() % (sockets_x.size());
		//std::cout << "Add: (" << sockets_x[k] << " , " << sockets_y[k] << " , " << sockets_z[k] << ")\n";
		Diagram3::add_vertex(sockets_x[k], sockets_y[k], sockets_z[k]);
		//print_level();
		//if (i % 100000 == 0) {
		//	std::cout << i << "\n";
		//}
	}
}

#pragma once
#include "Diagram3.h"
class GeneralizedProcessR3 :
	public Diagram3
{
private:
	double alpha;
	double weight;
	vector<double> sockets_p;
private:
	int distribution_p(int rn);
	void init_gener_process(double a);
	void calculate_p();
	double weight_function(int x, int y, int z);
public:
	void generalized_processR3(int n, double alh);
	void processR(int n = 1);
	GeneralizedProcessR3() :Diagram3() {};
	~GeneralizedProcessR3() {};
};


#pragma once
#include <iostream>
#include "diagram2.h"

using namespace std;

class Diagram3
{
protected:
	vector<int> sockets_x;
	vector<int> sockets_y;
	vector<int> sockets_z;
private:
	vector<class Diagram2 *> level;
protected :
	void add_point_sockets(int x, int y, int z);
	void calculate_sockets();//подсчет угловых дополнений
public:
	void add_vertex(int x, int y, int z);
	void print_level();
	void print_sockets();
	Diagram3();
	~Diagram3();
};


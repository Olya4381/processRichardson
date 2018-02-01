#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "diagram2.h"

using namespace std;

class Diagram3
{
protected:
	vector<int> sockets_x;
	vector<int> sockets_y;
	vector<int> sockets_z;
	map<std::pair<int, int>, priority_queue<int>> sockets; //хранит угл доп ввиде map<>
private:
	vector<class Diagram2 *> level;
protected :
	void init_sockets(); /**/
	void add_point_sockets(int x, int y, int z);
	void del_point_sockets(int x, int y, int z);
	void calculate_sockets();//подсчет угловых дополнений
public:
	void add_vertex(int x, int y, int z);
	void print_level();
	void print_sockets();
	Diagram3();
	~Diagram3();
};


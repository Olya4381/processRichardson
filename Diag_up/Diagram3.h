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
	map<std::pair<int, int>, int> mem_sock;
private:
	vector<class Diagram2 *> level;
protected :
	void init_sockets(); /*инициализируем структуру map*/
	void add_point_sockets(int x, int y, int z);//добавлеие угл доп  в вектор
	void add_point_sockets1(int x, int y, int z); /*добавлеие угловой доп в мэп*/
	void del_point_sockets(int x, int y, int z); /*удаление угл точки в мэп*/
	void calculate_sockets();//подсчет угловых дополнений  в векторе
public:
	void add_vertex(int x, int y, int z);
	void print_level();
	void print_sockets();
	Diagram3();
	~Diagram3();
};


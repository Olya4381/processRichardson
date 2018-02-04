#include "GeneralizedProcessR3.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
void GeneralizedProcessR3::generalized_processR3(int n, double alh)
{
	////////////////////////////////////////////////
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(0, 100000); // distribute results between 1 and 6 inclusive.
	init_gener_process(alh);
	for (int i = 0; i < n; i++) {
		std::pair<int, int> p = distribution_p(dist(gen));
		GeneralizedProcessR3::add_vertex(p.first, p.second, sockets[p].top()*-1);
		if (i % 100 == 0 && i != 0) {
			cout << i << "\n";
		}
	}
}

std::pair<int, int> GeneralizedProcessR3::distribution_p(int rn){
	//генерим точку
	double q = double(rn) / 100000.0;
	double sum = 0;
	std::pair<int, int> tmp;
	for (auto item : sockets_p)
	{
		tmp = item.first;
		if (q >= sum && q<(sum + item.second / weight))
		{
			break;
		}
		sum += item.second / weight;
	}
	return tmp;
}

void GeneralizedProcessR3::init_gener_process(double a)
{
	alpha = a;
	calculate_p();
}

void GeneralizedProcessR3::calculate_p()
{
	//очищаем
	if (sockets_p.size() != 0)
	{
		sockets_p.clear();
		weight = 0;
	}
	//по всем существующим точкам
	for (auto item : sockets)
	{
		//записываем их в мэп вероятностей
		sockets_p[item.first] = weight_function(item.first.first, item.first.second, item.second.top()*-1);
		weight += sockets_p[item.first];
	}
}

double GeneralizedProcessR3::weight_function(int x, int y, int z)
{
	return pow(double(x + y+z), alpha);
}

void GeneralizedProcessR3::processR(int n) {
	for (int i = 0; i < n; i++) {
		//int k = rand() % (sockets_x.size());
		int k = rand() % (sockets.size());
		//std::cout << "Add: (" << sockets_x[k] << " , " << sockets_y[k] << " , " << sockets_z[k] << ")\n";
		//Diagram3::add_vertex(sockets_x[k], sockets_y[k], sockets_z[k]);
		int j = 0;
		for (auto item : sockets)
		{
			if (j == k)
			{
				Diagram3::add_vertex(item.first.first, item.first.second, item.second.top()*-1);
				break;
			}
			j++;
		}
		//print_level();
		//if (i % 100000 == 0) {
		//	std::cout << i << "\n";
		//}
	}
}

//переопределяемый методы

void GeneralizedProcessR3::add_point_sockets1(int x, int y, int z)
{
	Diagram3::add_point_sockets1(x, y, z);
	if (sockets[std::make_pair(x, y)].top() == z*-1)
	{
		sockets_p[std::make_pair(x, y)] = weight_function(x, y, z);
		weight += sockets_p[std::make_pair(x, y)];
	}

}

void GeneralizedProcessR3::del_point_sockets(int x, int y, int z)
{
	if (sockets[std::make_pair(x, y)].top() == z*-1) //требуемая точка находить на вершине очереди
	{
		weight -= sockets_p[std::make_pair(x, y)];//
		sockets[std::make_pair(x, y)].pop();
		if (sockets[std::make_pair(x, y)].empty()) //если очередь пуста
		{
			sockets.erase(std::make_pair(x, y));
			sockets_p.erase(std::make_pair(x, y));//
			
		}
		else// иначе перевычисляем вероятность
		{
			sockets_p[std::make_pair(x, y)] = weight_function(x, y, sockets[std::make_pair(x, y)].top()*-1);
			weight += sockets_p[std::make_pair(x, y)];
		}
	}else//если не находиться
	{
		int min = sockets[std::make_pair(x, y)].top();//вытаскиваем все до требуемого значения
		do {
			sockets[std::make_pair(x, y)].pop();
		} while (min = sockets[std::make_pair(x, y)].top() > z*-1);

		while (min == z*-1)//заносим все обратно
		{
			sockets[std::make_pair(x, y)].push(min);
			min--;
		}

	}
}

void GeneralizedProcessR3::add_vertex(int x, int y, int z) {
	// вырожденный случай по level
	if (z > level.size())
	{
		level.push_back(new class Diagram2());
		del_point_sockets(1, 1, z);
		add_point_sockets1(1, 2, z);
		add_point_sockets1(2, 1, z);
		add_point_sockets1(1, 1, z + 1);
	}
	else
	{
		mem_sock.clear();

		level[z - 1]->add_vertex(x, y, mem_sock);

		for (auto& item : mem_sock)
		{
			if (item.second > 0)
			{
				add_point_sockets1(item.first.first, item.first.second, z);
			}
			else if (item.second < 0)
			{
				del_point_sockets(item.first.first, item.first.second, z);
			}
		}
	}
}

#include "GeneralizedProcessR.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
void GeneralizedProcessR::processR(int n) {
	for (int i = 0; i < n; i++) {
		int k = rand() % (sockets_x.size());
		Diagram2::add_vertex(sockets_x[k], sockets_y[k]);
		if (i % 10000 == 0) {
			std::cout << i << "\n";
		}
	}
}
//запись в файл

void GeneralizedProcessR::generalized_processR(int n, double alh)// обощенный процесс Ричардсона
{
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(0, 100000); // distribute results between 1 and 6 inclusive.
	init_gener_process(alh);

	//введем подсчет времени
	unsigned int start_time = clock(); // начальное время
	unsigned int end_time = 0; // конечное время

	for (int i = 0; i < n; i++) {
		int k = distribution_p(dist(gen));
		GeneralizedProcessR::add_vertex(sockets_x[k], sockets_y[k]);
		if(i % 100000 == 0 && i!=0) {
			//cout << i << "\n";
			end_time = clock();
			std::cout << i << '\t'<< (end_time - start_time) / 1000 << '.' << (end_time - start_time) % 1000 << '\n';
			start_time = end_time;
		}
	}
}

void GeneralizedProcessR::print_p()
{
	std::cout << "P:";
	for (int i = 0; i < sockets_p.size(); i++)
	{
		std::cout << sockets_p[i] << " ";
	}
	std::cout << "\n";
}

void GeneralizedProcessR::init_gener_process(double a) {
	alpha = a;
	calculate_p();
}

void GeneralizedProcessR::calculate_p()
{
	if (sockets_p.size() != 0)
	{
		sockets_p.clear();
		weight = 0;
	}
	for (int i = 0; i<sockets_x.size(); i++)
	{
		sockets_p.push_back(weight_function(sockets_x[i], sockets_y[i]));
		weight += sockets_p[i];
	}
}

double GeneralizedProcessR::weight_function(int x, int y) {
	return pow(double(x + y), alpha);
}

int GeneralizedProcessR::distribution_p(int rn){
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

void GeneralizedProcessR::add_point_sockets(int x, int y, int i) {
	//удаляем те, точки которые были затронуты
	weight -= sockets_p[i];
	sockets_p.erase(sockets_p.begin() + i);
	//добавляем образовавшуюся точку
	sockets_p.insert(sockets_p.begin() + i, weight_function(x, sockets_y[i]));
	weight += sockets_p[i];
	sockets_p.insert(sockets_p.begin() + i+1, weight_function(sockets_x[i], y));
	weight += sockets_p[i+1];
	Diagram2::add_point_sockets(x, y, i);
}

void GeneralizedProcessR::del_points_sockets(int i) {
	//удаляем те, точки которые были затронуты
	weight -= sockets_p[i];
	sockets_p.erase(sockets_p.begin() + i);
	weight -= sockets_p[i];
	sockets_p.erase(sockets_p.begin() + i );
	//добавляем образовавшуюся точку
	sockets_p.insert(sockets_p.begin() + i, weight_function(sockets_x[i+1], sockets_y[i]));
	weight += sockets_p[i];
	Diagram2::del_points_sockets(i);
}

void GeneralizedProcessR::recalculate(int x, int y) {
	// пересчет угловых точек
	//удаление точек содержащие данные координаты
	int ix = search_element(corners_x, x, false);
	if (ix != -1)
	{
		//удаляем угловое дополнения для этой точки
		del_points_sockets(ix);
		del_point_corners(ix);

	}
	int iy = search_element(corners_y, y, true);
	if (iy != -1)
	{
		del_points_sockets(iy);
		del_point_corners(iy);
	}

	//добавление новой угловой точки
	if (ix == -1 && iy == -1)
	{
		//поиск позиции
		int ix1 = insert_element(corners_x, x, false);
		add_point_corners(x, y, ix1);
	}
	else if (iy != -1)
	{
		//делаем вставку по iy
		add_point_corners(x, y, iy);
	}
	else {
		//делаем вставку по ix
		add_point_corners(x, y, ix);
	}
	// вставляем угловое дополнение
	int ix1 = insert_element(sockets_x, x + 1, false);
	//поиск не даст правильного ответа, если не сможет определить порядок сортировки
	add_point_sockets(x + 1, y + 1, ix1);
}

void GeneralizedProcessR::add_vertex(int x, int y)
{
	if (x == 1) {
		str.push_back(1);
	}
	else {
		str[y - 1]++;
	}

	if (y == 1) {
		col.push_back(1);
	}
	else {
		col[x - 1]++;
	}
	count++;
	recalculate(x, y);
}

//для усреднения
void GeneralizedProcessR::average_col(GeneralizedProcessR & d)
{
	int i = 0;
	for ( i = 0; i < d.col.size() && i<col.size(); i++)
	{
		col[i] += d.col[i];
	}
	for (; i < d.col.size(); i++)
	{
		col.push_back(d.col[i]);
	}
}

void GeneralizedProcessR::generalized_processR(int n, double alh, int average)
{
	GeneralizedProcessR * d = new GeneralizedProcessR();
	for (int i = 0; i < average; i++)
	{
		d->generalized_processR(n, alh);
		average_col(*d);
		d->clear();
	}
	//деление на средние
	count = 0;
	for (int i = 0; i < col.size(); i++)
	{
		col[i] /= average;
		count += col[i];
	}
	//удаление 0
	for (int i = col.size()-1; i >=0; i--)
	{
		if (col[i] == 0)
		{
			col.pop_back();
		}
		else
		{
			break;
		}
		
	}
	delete d;
}
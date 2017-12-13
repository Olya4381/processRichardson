#pragma once
#include "diagram2.h"
#include <iostream>

class GeneralizedProcessR :
	public Diagram2 //класс моделирующий двумерный процесс Ричрдсона
{
private:  
	double alpha;
	double weight;
	vector<double> sockets_p;
private:
	void init_gener_process(double alh);
	void calculate_p();
	double weight_function(int x, int y);
	int distribution_p(int rn);
	//переопределяемые методы
	void add_vertex(int x, int y);//не меняется
	void recalculate(int x, int y); //пересчет свойств при добавлении точки // не меняется
 	void add_point_sockets(int x, int y, int i);// вставка в массив угловых допов. позиция в массив y больше на еденицу
	void del_points_sockets(int i);//удаление в массив угловых допов. позиция в массив y больше на еденицу
public:
	void processR(int n = 1);
	void generalized_processR(int n, double alh);// обощенный процесс Ричардсона
	void print_p();
	void ptint_w() { std::cout << "w: " << weight << '\n'; };
	GeneralizedProcessR() :Diagram2() {};
	GeneralizedProcessR(vector<int> & s, bool f) : Diagram2(s, f) {};
	~GeneralizedProcessR() {};
};


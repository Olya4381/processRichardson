#pragma once
#include "diagram2.h"
//#include "GeneralizedProcessR_Averaged.h"
#include <iostream>
using namespace std;
class GeneralizedProcessR : 
	public Diagram2//класс моделирующий двумерный процесс Ричрдсона
{
private:  
	double alpha;//параметр
	double weight;//общий вес
	vector<double> sockets_p;//веса
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
	void average_col(GeneralizedProcessR & d);//использует столбец диагрммы для устреднения
public:
	friend class GeneralizedProcessR_Averaged;
	void processR(int n = 1);
	void generalized_processR(int n, double alh);// обощенный процесс Ричардсона
	void generalized_processR(int n, double alh, int average);//общенный процесс ричардсна с усреднением
	void print_p();
	void ptint_w() { std::cout << "w: " << weight << '\n'; };
	GeneralizedProcessR() :Diagram2() {};
	GeneralizedProcessR(vector<int> & s, bool f) : Diagram2(s, f) {};
	GeneralizedProcessR(char * name_file) : Diagram2(name_file) {}//добавление диграммы из файла (столюцы)
	~GeneralizedProcessR() {};
};

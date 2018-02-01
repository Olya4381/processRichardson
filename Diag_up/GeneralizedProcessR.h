#pragma once
#include "diagram2.h"
//#include "GeneralizedProcessR_Averaged.h"
#include <iostream>
using namespace std;
class GeneralizedProcessR : 
	public Diagram2//класс моделирующий двумерный процесс –ичрдсона
{
private:  
	double alpha;//параметр
	double weight;//общий вес
	vector<double> sockets_p;//веса
private:
	void init_gener_process(double alh);
	void calculate_p();//вычисл€ет первоначальное значение весов
	double weight_function(int x, int y);//функци€ вычисл€юща€ веса
	int distribution_p(int rn); //распределение задаваемое массивом весов
	//переопредел€емые методы
	void add_vertex(int x, int y);//не мен€етс€
	void recalculate(int x, int y); //пересчет свойств при добавлении точки // не мен€етс€
 	void add_point_sockets(int x, int y, int i);// вставка в массив угловых допов. позици€ в массив y больше на еденицу
	void del_points_sockets(int i);//удаление в массив угловых допов. позици€ в массив y больше на еденицу
	void average_col(GeneralizedProcessR & d);//использует столбец диагрммы дл€ устреднени€
public:
	friend class GeneralizedProcessR_Averaged;
	void processR(int n = 1);
	void generalized_processR(int n, double alh);// обощенный процесс –ичардсона
	void generalized_processR(int n, double alh, int average);//общенный процесс ричардсна с усреднением
	void print_p();
	void ptint_w() { std::cout << "w: " << weight << '\n'; };
	GeneralizedProcessR() :Diagram2() {};
	GeneralizedProcessR(vector<int> & s, bool f) : Diagram2(s, f) {};
	GeneralizedProcessR(char * name_file) : Diagram2(name_file) {}//добавление диграммы из файла (столюцы)
	~GeneralizedProcessR() {};
};

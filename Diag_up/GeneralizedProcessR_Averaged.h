#pragma once
#include <vector>
#include "diagram2.h"
#include "GeneralizedProcessR.h"
class GeneralizedProcessR_Averaged //класс считает усредненную диаграмму и получает ее в формате double
{
protected:
	vector<double> col;
	double count;
	int aver;
	GeneralizedProcessR d;
public:
	friend class StandardDeviation;
	void average_col();//использует столбец диагрммы для устреднения
	void generalized_processR_aver(int n, double alh, int average);//общенный усредненный
	void generalized_processR_aver(int n, double alh);//усредненный инициализорованной переменной
	void print_in_file_col(string & file_name);
	void clear();
	GeneralizedProcessR_Averaged();
	~GeneralizedProcessR_Averaged();
};


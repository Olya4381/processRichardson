#pragma once
#include <vector>
#include "Standarddeviation.h"
using namespace std;
class GeneralizedProcessR_Averaged //класс считает усредненную диаграмму и получает ее в формате double
{
protected:
	vector<double> col;
	double count;
	int aver;
public:
	friend class StandardDeviation;
	void average_col();//использует столбец диагрммы для устреднения
	void generalized_processR_aver(int n, double alh, int average);//общенный усредненный
	void generalized_processR_aver(int n, double alh);//усредненный инициализорованной переменной
	void print_in_file_col(std::string & file_name);
	void print_in_file_col(char * file_name);
	void clear();
	GeneralizedProcessR_Averaged();
	~GeneralizedProcessR_Averaged();
};


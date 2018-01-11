#include "GeneralizedProcessR_Averaged.h"
#include <fstream>
#include <string>

void GeneralizedProcessR_Averaged::average_col() {
	int i = 0;
	for (i = 0; i < d.col.size() && i<col.size(); i++)
	{
		col[i] += (double)d.col[i];
	}
	for (; i < d.col.size(); i++)
	{
		col.push_back((double)d.col[i]);
	}
}//использует столбец диагрммы для устреднения
void GeneralizedProcessR_Averaged::generalized_processR_aver(int n, double alh, int average) {
	for (int i = 0; i < average; i++)
	{
		d.generalized_processR(n, alh);
		average_col();
		d.clear();
	}
	//деление на средние
	for (int i = 0; i < col.size(); i++)
	{
		col[i] /= (double)average;
		count += col[i];
	}
}//общенный усредненный

void GeneralizedProcessR_Averaged::clear()
{
	count = 0.0;
	aver = 1;
	col.clear();
	d.clear();
}


void GeneralizedProcessR_Averaged::generalized_processR_aver(int n, double alh) {
	generalized_processR_aver(n, alh, aver);
}//усредненный инициализорованной переменной

GeneralizedProcessR_Averaged::GeneralizedProcessR_Averaged()
{
	aver = 1;
	count = 0.0;
	d = GeneralizedProcessR();
}


GeneralizedProcessR_Averaged::~GeneralizedProcessR_Averaged()
{
}


void GeneralizedProcessR_Averaged::print_in_file_col(string & file_name)
{
	if (file_name.empty())
	{
		std::cout << "Error: file is NULL";
		return;
	}
	ofstream fout;
	fout.open(file_name);

	if (!fout.is_open()) {
		std::cout << "Error: file can't open\n";
		return;
	}

	for (int i = 0; i < col.size(); i++)
	{
		fout << col[i] << " ";
	}
	fout.close();
	std::cout << "Write in file" << "done\n";

}
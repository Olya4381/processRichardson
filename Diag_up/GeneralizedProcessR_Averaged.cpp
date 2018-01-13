#include "GeneralizedProcessR_Averaged.h"
#include "GeneralizedProcessR.h"
#include <fstream>
#include <string>

void GeneralizedProcessR_Averaged::average_col() {
	/*int i = 0;
	for ( i = 0; i < d.col.size() && i<col.size(); i++)
	{
	col[i] += d.col[i];
	}
	for (; i < d.col.size(); i++)
	{
	col.push_back(d.col[i]);
	}*/
}//использует столбец диагрммы для устреднения
void GeneralizedProcessR_Averaged::generalized_processR_aver(int n, double alh, int average) {
	GeneralizedProcessR * d = new GeneralizedProcessR();
	std::cout << '1\n';
	for (int i = 0; i < average; i++)
	{
		std::cout << i << '\n';
		d->generalized_processR(n, alh);
		//average_col();
		int k = 0;
		for ( k = 0; k < d->col.size() && k<col.size(); k++)
		{
			col[k] += (double)d->col[k];
		}
		for (; k < d->col.size(); k++)
		{
			col.push_back((double)d->col[i]);
		}
		d->clear();
	}
	//деление на средние
	count = 0;
	for (int i = 0; i < col.size(); i++)
	{
		col[i] /= (double)average;
		count += col[i];
	}
	delete d;
}//общенный усредненный

void GeneralizedProcessR_Averaged::clear()
{
	count = 0.0;
	aver = 1;
	col.clear();
	//d->clear();
}


void GeneralizedProcessR_Averaged::generalized_processR_aver(int n, double alh) {
	generalized_processR_aver(n, alh, aver);
}//усредненный инициализорованной переменной

GeneralizedProcessR_Averaged::GeneralizedProcessR_Averaged()
{
	aver = 1;
	count = 0.0;
	//d = new GeneralizedProcessR();
}


GeneralizedProcessR_Averaged::~GeneralizedProcessR_Averaged()
{
	//delete d;
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

void GeneralizedProcessR_Averaged::print_in_file_col(char * file_name)
{
	if (file_name==NULL)
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

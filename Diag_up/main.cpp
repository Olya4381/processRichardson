#include "GeneralizedProcessR.h"
//#include "Standarddeviation.h"
#include "GeneralizedProcessR_Averaged.h"
//#include "diagram2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>

void proc(double alpha, int count, char* name_file);
void alpha_aver();
void aver(double aplha, int count, int aver, char* name_file);
void proc_aver(double alpha, int count, int aver, char* name_file);
int main(void)
{
	std::map<std::pair<int, int>, priority_queue<int>> myMap;
	//добавление
	myMap[std::make_pair(10, 10)].push(-10);
	myMap[std::make_pair(10, 10)].push(5);
	myMap[std::make_pair(10, 10)].push(0);
	//myMap[std::make_pair(10, 20)] = 30;
	//myMap[std::make_pair(10, 30)] = 40;
	//проверка
    if (myMap.count(std::make_pair(10, 10)) > 0)
	{
		std::cout << myMap[std::make_pair(10, 10)].top();
	}
	else
	{
		std::cout << "Not\n";
	}
	//std::cout << myMap[std::make_pair(10, 20)] << std::endl;
	//aver(-0.37,10000,50, "col_037_aver_double.txt");
	//proc(-0.37, 2000000, "col_037_2m.txt");
	//proc_aver(-0.37, 10000, 50, "col_037_aver_int.txt");
	//alpha_aver();
	return 0;
}


void aver(double alpha, int count, int aver, char* name_file)
{
	GeneralizedProcessR_Averaged * d = new GeneralizedProcessR_Averaged();
	StandardDeviation* s = new StandardDeviation(count + 1);

	d->generalized_processR_aver(count,alpha,aver);
	d->print_in_file_col(name_file);
	//std::cout << "_" << s->SD_gener_process(*d);
	delete d;
	delete s;
}


void proc(double alpha, int count, char* name_file)
{
	GeneralizedProcessR * d = new GeneralizedProcessR();
	StandardDeviation* s = new StandardDeviation(count + 1);

	d->generalized_processR(count, alpha);
	d->print_in_file_col(name_file);
	std::cout << "_" << s->SD_gener_process(*d);
	delete d;
	delete s;
}

void proc_aver(double alpha, int count, int aver, char* name_file)
{
	GeneralizedProcessR * d = new GeneralizedProcessR();
	StandardDeviation* s = new StandardDeviation(count + 1);

	d->generalized_processR(count, alpha, aver);
	d->print_in_file_col(name_file);
	std::cout << "_" << s->SD_gener_process(*d);
	delete d;
	delete s;
}

void alpha_aver()
{
	int count = 100000;
	GeneralizedProcessR_Averaged * d = new GeneralizedProcessR_Averaged();
	StandardDeviation* s = new StandardDeviation(count + 1);
	string tr = "file\\col100x20_double_";
	string  en = ".txt";

	ofstream fout;
	fout.open("alpha_100x20_1.txt");
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
	}


	for (double a = -0.6; a <= -0.2; a += 0.015)
	{
		std::cout << a << "\n";
		d->generalized_processR_aver(count,a,20);
		d->print_in_file_col(tr+std::to_string(a)+en);
		fout << a << "\t" << s->SD_gener_process(*d) << "\n";
		d->clear();
	}
	fout.close();

	delete d;
	delete s;
}


void std_dlya_filov()
{
	int count = 10000;

	StandardDeviation* s = new StandardDeviation(1);
	string tr = "file\\col10x100_";
	string  en = ".txt";

	Diagram2 * d;

	ofstream fout;
	fout.open("alpha_10x100_2.txt");
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
	}


	for (double a = -0.6; a <= -0.2; a += 0.015)
	{
		std::cout << a << "\n";
		d = new Diagram2(tr + std::to_string(a) + en);
		fout << a << "\t" << s->SD_gener_process(*d) << "\n";
		delete d;
	}
	fout.close();

	delete s;
}
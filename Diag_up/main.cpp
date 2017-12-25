#include "GeneralizedProcessR.h"
#include "Standarddeviation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
int main(void)
{

	int count = 10000;
	GeneralizedProcessR * d = new GeneralizedProcessR();
	StandardDeviation* s = new StandardDeviation(count+1);
	string tr = "col10x100_";
	string  en = ".txt";

	ofstream fout;
	fout.open("alpha_10x100.txt");
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
	}

	for (double a = (-0.54+0.015); a <= -0.2; a += 0.015)
	{
		std::cout << a << "\n";
		d->generalized_processR(count,a,100);
		d->print_in_file_col(tr+std::to_string(a)+en);
		fout << a << "\t" << s->SD_gener_process(*d) << "\n";
		d->clear();
	}
	fout.close();

	//d->generalized_processR(count,-0.37,10);
	//d->print_in_file_col("col_037_aver1.txt");
	//std::cout << "_" << s->SD_gener_process(*d);
	//d->print_picture();

	delete d;
	//delete s;
	return 0;
}


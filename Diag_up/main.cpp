#include "GeneralizedProcessR.h"
#include "Standarddeviation.h"
#include <iostream>
#include <fstream>

#include <random>
int main(void)
{

	int count = 10000;
	GeneralizedProcessR * d = new GeneralizedProcessR();
	StandardDeviation* s = new StandardDeviation(count+1);

	ofstream fout;
	fout.open("alpha_2.txt");
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
	}

	for (double a = -1.0; a <= 1.0; a += 0.05)
	{
		std::cout << a << "\n";
		d->generalized_processR(count,a,10);
		fout << a << "\t" << s->SD_gener_process(*d) << "\n";
		d->clear();
	}
	fout.close();

	//d->generalized_processR(count,-0.37,10);
	//d->print_in_file_col("col_037_aver1.txt");
	//std::cout << "_" << s->SD_gener_process(*d);
	//d->print_picture();

	delete d;
	delete s;
	return 0;
}


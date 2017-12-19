#include "GeneralizedProcessR.h"
//#include "GeneralizedProcessR3.h"
#include "Standarddeviation.h"
#include <iostream>

#include <random>
int main(void)
{


	//Diagram2 *d = new Diagram2(str,1);
	//d->print_picture();

	GeneralizedProcessR * d = new GeneralizedProcessR();
	StandardDeviation* s = new StandardDeviation();


	d->generalized_processR(10000,-0.37);
	//d->print_in_file_col("col_test.txt");
	std::cout << "_" << s->SD_gener_process(*d);
	//d->print_picture();

	delete d;
	delete s;
	return 0;
}


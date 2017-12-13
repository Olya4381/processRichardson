#include "GeneralizedProcessR.h"
#include "GeneralizedProcessR3.h"
#include <iostream>

#include <random>
int main(void)
{
	GeneralizedProcessR3 *d = new GeneralizedProcessR3();
	d->processR(500);

	d->print_level();


	//Diagram2 *d = new Diagram2(str,1);
	//d->print_picture();

	/*GeneralizedProcessR * d = new GeneralizedProcessR();
	d->generalized_processR(100000,-0.5);
	d->print_in_file_col("col.txt");*/
	//d->print_corners();
	//d->print_picture();

	delete d;
	return 0;
}


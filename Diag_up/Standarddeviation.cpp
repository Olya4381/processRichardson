#include "Standarddeviation.h"
#include <cmath>
#include <new>

StandardDeviation::StandardDeviation(int coun)
{
	len_f1 = 0;
	count = coun;
	init_func1(coun);
}


StandardDeviation::~StandardDeviation()
{
	delete f1;
}


int StandardDeviation::init_func1(int count) {
	if (len_f1 != 0)
	{
		len_f1 = 0;
		delete f1;
	}
		//знаем  максимум функции 2;
		//узначем сколько значений меньше
		double sqcount = sqrt(double(count));
		int n = int(ceil(2.0 * sqcount))-1;
		//выделяем память
		f1 = new double[n];
		if (f1 == NULL)
		{
			std::cout << "Error: new init_func1\n";
			return -1;
		}
		else {
			//общие переменные
			max_f1 = 2;
			len_f1 = n;

			//переменные для вычиления функции
			double j = -1.0;
			double del = 0.5 / double(LENGTH_FUNC);


			double k = 1;
			double x;
			double x1 = 0;
			for (int i = 0, m = 0; i < LENGTH_FUNC, m<n; i++)
			{
				//вычисление x
				x = (j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
				//попадает ли точка в интерва
				if (k/sqcount > x1 && k/sqcount < x) {
					if (abs(k/sqcount - x1) < abs(k/sqcount - x))
					{
						//приминаем значение ч1
						j -= del;
						f1[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						j += del;
					}
					else {
						f1[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						//принимаем значение ч
					}
					m++;
					k++;
				}


				x1 = x;
				j += del;
			}

		}
	
		this->count = count;
	return 0;
}

int StandardDeviation::init_func1(double count) {
	if (len_f1 != 0)
	{
		len_f1 = 0;
		delete f1;
	}
	//знаем  максимум функции 2;
	//узначем сколько значений меньше
	double sqcount = sqrt(double(count));
	int n = int(ceil(2.0 * sqcount)) - 1;
	//выделяем память
	f1 = new double[n];
	if (f1 == NULL)
	{
		std::cout << "Error: new init_func1\n";
		return -1;
	}
	else {
		//общие переменные
		max_f1 = 2;
		len_f1 = n;

		//переменные для вычиления функции
		double j = -1.0;
		double del = 0.5 / double(LENGTH_FUNC);


		double k = 1;
		double x;
		double x1 = 0;
		for (int i = 0, m = 0; i < LENGTH_FUNC, m<n; i++)
		{
			//вычисление x
			x = (j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
			//попадает ли точка в интерва
			if (k / sqcount > x1 && k / sqcount < x) {
				if (abs(k / sqcount - x1) < abs(k / sqcount - x))
				{
					//приминаем значение ч1
					j -= del;
					f1[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
					j += del;
				}
				else {
					f1[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
					//принимаем значение ч
				}
				m++;
				k++;
			}


			x1 = x;
			j += del;
		}

	}
	this->count1 = count;
	return 0;
}


double StandardDeviation::func1(double x, int i){
	if (i>=len_f1)
	{
		return 0;
	}
	return f1[i];
}

double StandardDeviation:: SD_gener_process(class Diagram2 & d)
{
	if (count != d.count)
	{
		init_func1(d.count);
	}
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt(d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = (d.col[i]) / size;
		double tmp2 = func1(j / size, i);
		S += pow((d.col[i]) / size - func1(j / size,i), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

double StandardDeviation::SD_gener_process(class GeneralizedProcessR_Averaged & d)
{
	if (count1 != d.count)
	{
		init_func1(d.count);
	}
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt((double)d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = ((double)d.col[i]) / size;
		double tmp2 = func1(j / size, i);
		S += pow(((double)d.col[i]) / size - func1(j / size, i), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

void StandardDeviation::print_func()
{
	init_func1(101);
	for (int i = 0; i<len_f1; i++)
	{
		std::cout << " " << f1[i];
	}
}
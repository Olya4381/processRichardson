#include "Standarddeviation.h"

#include <new>

StandardDeviation::StandardDeviation()
{
}


StandardDeviation::~StandardDeviation()
{
	delete f1;
}

int StandardDeviation::init_func1(int count) {
	//знаем  максимум функции sqrt(2);
	//узначем сколько значений меньше


	if (len_f1 != count)
	{
		double sqcount = sqrt(double(count));
		int n = int(ceil(sqrt(2 * double(count))));
		//выделяем память
		f1 = new double[n];
		if (f1 == NULL)
		{
			return -1;
		}
		else {
			max_f1 = sqrt(2);
			len_f1 = n;

			double j = -1.0;
			double del = 0.5 / double(LENGTH_FUNC);

			double k = 1;
			double x;
			double x1 = 0;
			for (int i = 0, m = 0; i < LENGTH_FUNC, m<n; i++)
			{
				//вычисление x
				x = sqrt(2) / 2 * (j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
				//попадает ли точка в интерва
				if (k*sqcount > x1 && k*sqcount < x) {
					if (abs(k*sqcount - x1) < abs(k*sqcount - x1))
					{
						//приминаем значение ч1
						j -= del;
						f1[m] = sqrt(2) / 2 * (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						j += del;
					}
					else {
						f1[m] = sqrt(2) / 2 * (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						//принимаем значение ч
					}
					m++;
					k++;
				}


				x1 = x;
				j += del;
			}

		}
	}
	return 0;
}
double StandardDeviation::func1(double x, int i){
	if (abs(x- max_f1) < EPS)
	{
		return 0;
	}
	return f1[i-1];
}

double StandardDeviation:: SD_gener_process(class Diagram2 & d)
{
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt((double) d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		S += pow(((double)d.col[i]) / size - func1(j / size,i), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

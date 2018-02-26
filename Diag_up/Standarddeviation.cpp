#include "Standarddeviation.h"
#include <cmath>
#include <new>

StandardDeviation::StandardDeviation(int coun)
{
	len_Plancherel2d = 0;
	count = coun;
	init_Plancherel2d(coun);
}


StandardDeviation::~StandardDeviation()
{
	delete Plancherel2d;
}


int StandardDeviation::init_Plancherel2d(int count) {
	if (len_Plancherel2d != 0)
	{
		len_Plancherel2d = 0;
		delete Plancherel2d;
	}
		//знаем  максимум функции 2;
		//узначем сколько значений меньше
		double sqcount = sqrt(double(count));
		int n = int(ceil(2.0 * sqcount))-1;
		//выделяем память
		Plancherel2d = new double[n];
		if (Plancherel2d == NULL)
		{
			std::cout << "Error: new init_func1\n";
			return -1;
		}
		else {
			//общие переменные
			max_Plancherel2d = 2;
			len_Plancherel2d = n;

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
						Plancherel2d[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						j += del;
					}
					else {
						Plancherel2d[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
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

int StandardDeviation::init_Plancherel2d(double count) {
	if (len_Plancherel2d != 0)
	{
		len_Plancherel2d = 0;
		delete Plancherel2d;
	}
	//знаем  максимум функции 2;
	//узначем сколько значений меньше
	double sqcount = sqrt(double(count));
	int n = int(ceil(2.0 * sqcount)) - 1;
	//выделяем память
	Plancherel2d = new double[n];
	if (Plancherel2d == NULL)
	{
		std::cout << "Error: new init_func1\n";
		return -1;
	}
	else {
		//общие переменные
		max_Plancherel2d = 2;
		len_Plancherel2d = n;

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
					Plancherel2d[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
					j += del;
				}
				else {
					Plancherel2d[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
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


double StandardDeviation::func_Plancherel2d(double x, int i){
	if (i>=len_Plancherel2d)
	{
		return 0;
	}
	return Plancherel2d[i];
}

double StandardDeviation:: SD_Plancherel_2d(class Diagram2 & d)
{
	if (count != d.count)
	{
		init_Plancherel2d(d.count);
	}
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt(d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = (d.col[i]) / size;
		double tmp2 = func_Plancherel2d(j / size, i);
		S += pow((d.col[i]) / size - func_Plancherel2d(j / size,i), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

double StandardDeviation::SD_Plancherel_2d(class GeneralizedProcessR_Averaged & d)
{
	if (count1 != d.count)
	{
		init_Plancherel2d(d.count);
	}
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt((double)d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = ((double)d.col[i]) / size;
		double tmp2 = func_Plancherel2d(j / size, i);
		S += pow(((double)d.col[i]) / size - func_Plancherel2d(j / size, i), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

double  StandardDeviation::func_EvenDistr2d(double x)
{
	return log(1 - exp(-3.141526 / sqrt(6.0)*x))*-sqrt(6.0) / 3.141526;
}

double StandardDeviation::SD_EvenDistr_2d(class Diagram2 & d)
{
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt(d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = (d.col[i]) / size;
		double tmp2 = func_EvenDistr2d(j / size);
		S += pow((d.col[i]) / size - func_EvenDistr2d(j / size), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

double StandardDeviation::SD_EvenDistr_2d(class GeneralizedProcessR_Averaged & d)
{
	double S = 0;
	double n = (double)d.col.size();
	double size = sqrt((double)d.count);
	double j = 1.0;
	int in = d.col.size();

	for (int i = 0; i < in; i++)
	{
		double tmp1 = ((double)d.col[i]) / size;
		double tmp2 = func_EvenDistr2d(j / size);
		S += pow(((double)d.col[i]) / size - func_EvenDistr2d(j / size), 2);
		j += 1.0;
	}

	return sqrt(S / (n - 1));
}

void StandardDeviation::print_func()
{
	init_Plancherel2d(101);
	for (int i = 0; i<len_Plancherel2d; i++)
	{
		std::cout << " " << Plancherel2d[i];
	}
}


double StandardDeviation::SD_two_diagrams3d(class Diagram3 & a, class Diagram3 & b)
{
	double sum=0;
	int i = 0;
	int n = 0;
	for (;i < a.level.size() || i< b.level.size();i++)
	{
		sum += sub_sd_two_diarams2(*(a.level[i]), *(b.level[i]));
		a.level[i]->col.size() < b.level[i]->col.size() ? n += b.level[i]->col.size() : n += a.level[i]->col.size();
	}
	if (a.level.size() > b.level.size())
	{
		for (;i < a.level.size() ;i++)
		{
			sum += sub_sd_two_diarams2(*(a.level[i]));
			n += a.level[i]->col.size();
		}
	}
	else {
		for (;i < b.level.size();i++)
		{
			sum += sub_sd_two_diarams2(*(b.level[i]));
			n += b.level[i]->col.size();
		}
	}
	return sum / (double(n) - 1.0);
}



double StandardDeviation::sub_sd_two_diarams2(class Diagram2 & a, class Diagram2 & b)
{
	int sum=0;
	int tmp = 0;
	for (int i = 0;i < a.col.size() || i < b.col.size();i++)
	{
		tmp = get_col(a, i) - get_col(b, i);
		sum += tmp*tmp;
	}
	return double(sum);
}

double StandardDeviation::sub_sd_two_diarams2( class Diagram2 & a)
{
	int sum=0;
	int tmp = 0;
	for (int i = 0;i < a.col.size();i++)
	{
		tmp = get_col(a, i);
		sum += tmp*tmp;
	}
	return double(sum);
}


int StandardDeviation::get_col(class Diagram2 & d, int i)
{
	if (i < d.col.size())
	{
		return d.col[i];
	}
	return 0;
}
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
		//�����  �������� ������� 2;
		//������� ������� �������� ������
		double sqcount = sqrt(double(count));
		int n = int(ceil(2.0 * sqcount))-1;
		//�������� ������
		f1 = new double[n];
		if (f1 == NULL)
		{
			std::cout << "Error: new init_func1\n";
			return -1;
		}
		else {
			//����� ����������
			max_f1 = 2;
			len_f1 = n;

			//���������� ��� ��������� �������
			double j = -1.0;
			double del = 0.5 / double(LENGTH_FUNC);


			double k = 1;
			double x;
			double x1 = 0;
			for (int i = 0, m = 0; i < LENGTH_FUNC, m<n; i++)
			{
				//���������� x
				x = (j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
				//�������� �� ����� � �������
				if (k/sqcount > x1 && k/sqcount < x) {
					if (abs(k/sqcount - x1) < abs(k/sqcount - x))
					{
						//��������� �������� �1
						j -= del;
						f1[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						j += del;
					}
					else {
						f1[m] =  (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
						//��������� �������� �
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
	//�����  �������� ������� 2;
	//������� ������� �������� ������
	double sqcount = sqrt(double(count));
	int n = int(ceil(2.0 * sqcount)) - 1;
	//�������� ������
	f1 = new double[n];
	if (f1 == NULL)
	{
		std::cout << "Error: new init_func1\n";
		return -1;
	}
	else {
		//����� ����������
		max_f1 = 2;
		len_f1 = n;

		//���������� ��� ��������� �������
		double j = -1.0;
		double del = 0.5 / double(LENGTH_FUNC);


		double k = 1;
		double x;
		double x1 = 0;
		for (int i = 0, m = 0; i < LENGTH_FUNC, m<n; i++)
		{
			//���������� x
			x = (j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
			//�������� �� ����� � �������
			if (k / sqcount > x1 && k / sqcount < x) {
				if (abs(k / sqcount - x1) < abs(k / sqcount - x))
				{
					//��������� �������� �1
					j -= del;
					f1[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
					j += del;
				}
				else {
					f1[m] = (-j + 2 / 3.141526*(j * asin(j) + sqrt(1 - j * j)));
					//��������� �������� �
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


double StandardDeviation::SD_two_diagrams3d(class Diagram3 & a, class Diagram3 & b)
{
	double sum;
	int i = 0;
	int n = 0;
	for (;i < a.print_level.size() || b.print_level.size();i++)
	{
		sum += sub_sd_two_diarams2(*(a.level[i]), *(b.level[i]));
		a.level[i]->col.size() < b.level[i]->col.size() ? n += b.level[i]->col.size() : n += a.level[i]->col.size();
	}
	if (a.level.size() > b.level.size)
	{
		for (;i < a.print_level.size() ;i++)
		{
			sum += sub_sd_two_diarams2(*(a.level[i]));
			n += a.level[i]->col.size();
		}
	}
	else {
		for (;i < b.print_level.size();i++)
		{
			sum += sub_sd_two_diarams2(*(b.level[i]));
			n += b.level[i]->col.size();
		}
	}
	return sum / (double(n) - 1.0);
}



double StandardDeviation::sub_sd_two_diarams2(class Diagram2 & a, class Diagram2 & b)
{
	int sum;
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
	int sum;
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
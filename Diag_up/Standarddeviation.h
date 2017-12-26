#pragma once
#include <math.h>
#include <iostream>
#include "diagram2.h"


#define LENGTH_FUNC 2000
#define EPS 0.001
class StandardDeviation //класс для подсчета СКО
{
private:
	int count;
	double *f1;
	double max_f1;
	int len_f1;
private:
	int init_func1(int count); //функция определяет примермые значения 0..n/sqrt()
	double func1(double x, int i);
public:
	void print_func();
	double SD_gener_process(class Diagram2 & d);
	StandardDeviation(int count);
	~StandardDeviation();
};

/*

double Diagram2::func_compare(double x) {
//ищем подходящее значение y
double eps = 0.0001;
while (x < (func_compare_x[last_pos]-eps) && last_pos<LENGTH_FUNC_COMPARE)
{
last_pos++;
}
if (last_pos >= LENGTH_FUNC_COMPARE) return 0;
return func_compare_y[last_pos];
}

int Diagram2::init_func() {
//инициализируем 1000 значений

func_compare_x = new double[LENGTH_FUNC_COMPARE];
func_compare_y = new double[LENGTH_FUNC_COMPARE];

if (func_compare_x == NULL || func_compare_y==NULL)
{
std::cout << "Error: new func_compare_x_y";
return 0;
}
else
{
double xx;
double yy;
double j=-1;
double step =(double) LENGTH_FUNC_COMPARE;
for (int i = 0; i < LENGTH_FUNC_COMPARE; i++)//заполняем массив начальными значениями
{
xx= j;
yy = 2 / 3.141526*(xx * asin(xx) + sqrt(1 - xx * xx));
func_compare_x[i] = sqrt(2) / 2 * (xx + yy);
func_compare_y[i] = sqrt(2) / 2 * (-xx + yy)/0.5;
j += 0.5/step;
}
}
last_pos = 0;
return 1;
}
double Diagram2::calculate_std_deviation() {
if(func_compare_x == 0)
{
init_func();
}
last_pos = 0;

double S = 0;
double n = sqrt((double)count);
double j = 1;
for (int i = 0; i < col.size(); i++)
{
S += pow(((double)col[i]) / n - func_compare(j / n), 2);
j += 1.0;
}
return sqrt(S / ((double)col.size() - 1.0));
}

*/
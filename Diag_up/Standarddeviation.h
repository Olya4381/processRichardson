#pragma once
#include <math.h>
#include <iostream>
#include "diagram2.h"
#include "GeneralizedProcessR_Averaged.h"
#include <cmath>


#define LENGTH_FUNC 2000
#define EPS 0.001
class StandardDeviation //����� ��� �������� ���
{
private:
	int count;
	double count1;
	double *Plancherel2d;
	double max_Plancherel2d;
	int len_Plancherel2d;
private:
	int init_Plancherel2d(double count);//���������� ����� ����������
	int init_Plancherel2d(int count); //������� ���������� ��������� �������� 0..n/sqrt()
	double func_Plancherel2d(double x, int i);
	double func_EvenDistr2d(double x);
	//��� �������
	double sub_sd_two_diarams2(class Diagram2 & a, class Diagram2 & b);//��� 2� �������� ��� ������� �� ���-�� ������
	double sub_sd_two_diarams2(class Diagram2 & a);//��� 2� �������� ��� ������� �� ���-�� ������
	int get_col(class Diagram2 & d, int i);
public:
	void print_func();
	double SD_Plancherel_2d(class Diagram2 & d);
	double SD_Plancherel_2d(class GeneralizedProcessR_Averaged & d);
	double SD_EvenDistr_2d(class Diagram2 & d);
	double SD_EvenDistr_2d(class GeneralizedProcessR_Averaged & d);



	//��� ���� ��������
	double SD_two_diagrams3d(class Diagram3 & a, class Diagram3 & b);
	StandardDeviation(int count);
	~StandardDeviation();
};

/*

double Diagram2::func_compare(double x) {
//���� ���������� �������� y
double eps = 0.0001;
while (x < (func_compare_x[last_pos]-eps) && last_pos<LENGTH_FUNC_COMPARE)
{
last_pos++;
}
if (last_pos >= LENGTH_FUNC_COMPARE) return 0;
return func_compare_y[last_pos];
}

int Diagram2::init_func() {
//�������������� 1000 ��������

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
for (int i = 0; i < LENGTH_FUNC_COMPARE; i++)//��������� ������ ���������� ����������
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
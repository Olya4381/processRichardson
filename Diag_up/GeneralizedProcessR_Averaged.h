#pragma once
#include <vector>
#include "diagram2.h"
#include "GeneralizedProcessR.h"
class GeneralizedProcessR_Averaged //����� ������� ����������� ��������� � �������� �� � ������� double
{
protected:
	vector<double> col;
	double count;
	int aver;
	GeneralizedProcessR d;
public:
	friend class StandardDeviation;
	void average_col();//���������� ������� �������� ��� �����������
	void generalized_processR_aver(int n, double alh, int average);//�������� �����������
	void generalized_processR_aver(int n, double alh);//����������� ������������������ ����������
	void print_in_file_col(string & file_name);
	void clear();
	GeneralizedProcessR_Averaged();
	~GeneralizedProcessR_Averaged();
};


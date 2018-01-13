#pragma once
#include <vector>
#include "Standarddeviation.h"
using namespace std;
class GeneralizedProcessR_Averaged //����� ������� ����������� ��������� � �������� �� � ������� double
{
protected:
	vector<double> col;
	double count;
	int aver;
public:
	friend class StandardDeviation;
	void average_col();//���������� ������� �������� ��� �����������
	void generalized_processR_aver(int n, double alh, int average);//�������� �����������
	void generalized_processR_aver(int n, double alh);//����������� ������������������ ����������
	void print_in_file_col(std::string & file_name);
	void print_in_file_col(char * file_name);
	void clear();
	GeneralizedProcessR_Averaged();
	~GeneralizedProcessR_Averaged();
};


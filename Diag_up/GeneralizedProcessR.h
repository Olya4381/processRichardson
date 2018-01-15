#pragma once
#include "diagram2.h"
//#include "GeneralizedProcessR_Averaged.h"
#include <iostream>
using namespace std;
class GeneralizedProcessR : 
	public Diagram2//����� ������������ ��������� ������� ���������
{
private:  
	double alpha;//��������
	double weight;//����� ���
	vector<double> sockets_p;//����
private:
	void init_gener_process(double alh);
	void calculate_p();
	double weight_function(int x, int y);
	int distribution_p(int rn);
	//���������������� ������
	void add_vertex(int x, int y);//�� ��������
	void recalculate(int x, int y); //�������� ������� ��� ���������� ����� // �� ��������
 	void add_point_sockets(int x, int y, int i);// ������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void del_points_sockets(int i);//�������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void average_col(GeneralizedProcessR & d);//���������� ������� �������� ��� �����������
public:
	friend class GeneralizedProcessR_Averaged;
	void processR(int n = 1);
	void generalized_processR(int n, double alh);// ��������� ������� ����������
	void generalized_processR(int n, double alh, int average);//�������� ������� ��������� � �����������
	void print_p();
	void ptint_w() { std::cout << "w: " << weight << '\n'; };
	GeneralizedProcessR() :Diagram2() {};
	GeneralizedProcessR(vector<int> & s, bool f) : Diagram2(s, f) {};
	GeneralizedProcessR(char * name_file) : Diagram2(name_file) {}//���������� �������� �� ����� (�������)
	~GeneralizedProcessR() {};
};

#pragma once
#include "Diagram3.h"
class GeneralizedProcessR3 :
	public Diagram3
{
private:
	double alpha;
	double weight;
	map<std::pair<int, int>, double> sockets_p;//
	/*��������� map(x,y)=weight_function*/
private:
	std::pair<int,int> distribution_p(int rn);
	void init_gener_process(double a); //������������� ������ ��������
	void calculate_p(); //�������������� ��������� �����
	double weight_function(int x, int y, int z);//������� �������
	//���������������� ������
	void add_vertex(int x, int y, int z);//���������� �������
	void add_point_sockets1(int x, int y, int z); /*��������� ������� ��� � ���*/
	void del_point_sockets(int x, int y, int z); /*�������� ��� ����� � ���*/
public:
	void generalized_processR3(int n, double alh); //���������� ������� ����������
	void processR(int n = 1);//������� ����������
	GeneralizedProcessR3() :Diagram3() {};
	~GeneralizedProcessR3() {};
};


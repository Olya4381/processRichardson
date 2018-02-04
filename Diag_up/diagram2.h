#pragma once
#include <vector>
#include "Standarddeviation.h"
#include "Diagram3.h"
#include <string>
#include <map>
using namespace std;
class Diagram2 //����� ��������� ��������� ����
{
protected:
	vector<int> str; //�������
	vector<int> col; //������
	int count;
	vector<int> corners_x; //���������� ������� �����
	vector<int> corners_y;
	vector<int> sockets_x; //���������� ������� ����������
	vector<int> sockets_y;
public:
	friend class StandardDeviation;
	friend class Diagram3;
	Diagram2();//������� ��������
	Diagram2(vector<int> & s, bool f);//���������� ������������ �������� 0-������, 1 -�������
	Diagram2(char * name_file);//���������� �������� �� ����� (�������)
	Diagram2(string & name_file);//���������� �������� �� ����� (�������)
	~Diagram2() {}
protected:
	void calculate_value();
	void recalculate(int x, int y); //�������� ������� ��� ���������� �����
	void recalculate(int x, int y, map<std::pair<int, int>, int>& mem_sock); //�������� ������� ��� ���������� �����
	int search_element(vector<int> & v, int x, bool f);//���������� ������ ����� � ������� (��������������� ������)
	int insert_element(vector<int> & v, int x, bool f);//���������� ������ ����� � ������� ��� �������
	void add_point_corners(int x, int y, int i); // ������� � ������ ������� �����, ������� ���������
	void add_point_sockets(int x, int y, int i);// ������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void add_point_sockets(int x, int y, int i, map<std::pair<int, int>, int>& mem_sock);// ������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void del_point_corners(int i);// �������� � ������ ������� �����, ������� ���������
	void del_points_sockets(int i);//�������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void del_points_sockets(int i, map<std::pair<int, int>, int>& mem_sock);//�������� � ������ ������� �����. ������� � ������ y ������ �� �������
	void init_map(map<std::pair<int, int>, int> mem_sock,int x,int y);
public:
	void add_vertex(int x, int y);//����������
	void add_vertex(int x, int y, map<std::pair<int, int>, int> & mem_sock);//���������� ������� � ������� ��������� � ����������� ������� ����������
public://����� ������ �����
	void clear();
	void print_in_file_col(char * file_name = "out.txt");
	void print_in_file_col(string & file_name);
	void print_count();
	void print_diag_str();
	void print_diag_col();
	void print_corners();
	void print_sockets();
	void print_picture();
	void print_diag_col_s();
};


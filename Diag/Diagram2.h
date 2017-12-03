#include <vector>
#include <iostream>
using namespace std;

class Diagram2{
private:
	vector<int> str;
	vector<int> col;
	int count;
	vector<int> angular_points;
	vector<int> angular_complements;
	vector<int> corners_x;
	vector<int> corners_y;
	vector<int> sockets_x;
	vector<int> sockets_y;
	vector<double> sockets_p;
	int alpha;
public:
	 Diagram2();
	 Diagram2(vector<int> & s,bool);//�� ���� �������� ���� ��� - ������ ����� (x,y,x,y...), ���� ����� - ��������
	void calculate_value();
	void recalculate(int x, int y); 
	int search_element(vector<int> & v,int x);//���������� ������ ����� � ������� (��������������� ������)
	int insert_element(vector<int> & v, int x);//���������� ������ ����� � ������� ��� �������
	void add_vertex(int x, int y);
	void processR(int n);
	double weight_function(int x, int y);
	int distribution_p();
	void calculate_p();
	void init_generalized_processR(double a);
	void generalized_processR(int n);
	int get_count();
	const vector<int>  & get_diag_str();
	const vector<int>  & get_diag_col();
	const vector<int>  & get_angular_point();
	const vector<int>  & get_angular_complements();
	~Diagram2() {};
};
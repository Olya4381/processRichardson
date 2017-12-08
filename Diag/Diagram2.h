#include <vector>
#include <iostream>
using namespace std;
#define LENGTH_FUNC_COMPARE 2000
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
	//дл€ весов
	vector<double> sockets_p;
	double alpha;
	//дл€ мнк 
	double* func_compare_x;
	double* func_compare_y;
	int last_pos;
public:
	 Diagram2();
	 Diagram2(vector<int> & s,bool);//на вход подаетс€ если тру - вектор строк (x,y,x,y...), если фолсе - столбцов
	void calculate_value();
	void recalculate(int x, int y); 
	int search_element(vector<int> & v,int x);//возвращает индекс числа в векторе (отсортированный массив)
	int insert_element(vector<int> & v, int x);//возвращает индекс числа в векторе дл€ вставки
	void add_vertex(int x, int y);
	void clear_diag();
	//процесс
	void processR(int n);
	double weight_function(int x, int y);
	int distribution_p();
	void calculate_p();
	void init_generalized_processR(double a);
	void generalized_processR(int n);
	//расчет мннк
	double func_compare(double x);
	double calculate_std_deviation();
	int init_func();
	//вывод
	int get_count();
	const vector<int>  & get_diag_str();
	const vector<int>  & get_diag_col();
	const vector<int>  & get_angular_point();
	const vector<int>  & get_angular_complements();
	~Diagram2() {};
};
#pragma once
#include <vector>
#include "Standarddeviation.h"
#include "Diagram3.h"
#include <string>
#include <map>
using namespace std;
class Diagram2 //класс двумерной диаграммы Юнга
{
protected:
	vector<int> str; //столбцы
	vector<int> col; //строки
	int count;
	vector<int> corners_x; //координаты угловых точек
	vector<int> corners_y;
	vector<int> sockets_x; //координаты угловых дополнений
	vector<int> sockets_y;
public:
	friend class StandardDeviation;
	friend class Diagram3;
	Diagram2();//создает диграмму
	Diagram2(vector<int> & s, bool f);//добавление существующей диаграмы 0-строки, 1 -столбец
	Diagram2(char * name_file);//добавление диграммы из файла (столюцы)
	Diagram2(string & name_file);//добавление диграммы из файла (столюцы)
	~Diagram2() {}
protected:
	void calculate_value();
	void recalculate(int x, int y); //пересчет свойств при добавлении точки
	void recalculate(int x, int y, map<std::pair<int, int>, int>& mem_sock); //пересчет свойств при добавлении точки
	int search_element(vector<int> & v, int x, bool f);//возвращает индекс числа в векторе (отсортированный массив)
	int insert_element(vector<int> & v, int x, bool f);//возвращает индекс числа в векторе для вставки
	void add_point_corners(int x, int y, int i); // вставка в массив угловых точек, позиция одинакова
	void add_point_sockets(int x, int y, int i);// вставка в массив угловых допов. позиция в массив y больше на еденицу
	void add_point_sockets(int x, int y, int i, map<std::pair<int, int>, int>& mem_sock);// вставка в массив угловых допов. позиция в массив y больше на еденицу
	void del_point_corners(int i);// удаление в массив угловых точек, позиция одинакова
	void del_points_sockets(int i);//удаление в массив угловых допов. позиция в массив y больше на еденицу
	void del_points_sockets(int i, map<std::pair<int, int>, int>& mem_sock);//удаление в массив угловых допов. позиция в массив y больше на еденицу
	void init_map(map<std::pair<int, int>, int> mem_sock,int x,int y);
public:
	void add_vertex(int x, int y);//добавление
	void add_vertex(int x, int y, map<std::pair<int, int>, int> & mem_sock);//добавление вершины с записью удаленных и добавленных угловых дополнений
public://вывод всякий штуки
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


#include "Diagram2.h"
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
Diagram2::Diagram2() {
	//диграмма пуста
	count = 0;
	str.push_back(0);
	col.push_back(0);
	// 0 угловых точек, 1 угловое дополнение
	angular_points.push_back(0);
	angular_complements.push_back(1);
	angular_complements.push_back(1);
}

	void Diagram2::generalized_processR(int n)// обощенный процесс Ричардсона
	{
		for (int i=0; i < n;i++) {
			int k = distribution_p();
			add_vertex(sockets_x[k],sockets_y[k]);
			if(i % 100000 == 0) {
				cout << i << "\n";
			}
		}
	}
	
	void Diagram2::init_generalized_processR(double a)//вычисление весовой функции без нормировки
	{
			alpha=a;
			calculate_p();
	}
	
	void Diagram2::calculate_p()
	{
		if(sockets_p.size()!=NULL)
		{
			sockets_p.clear();
		}
		for(int i=0; i<sockets_x.size();i++)
		{
			sockets_p.push_back(weight_function(sockets_x[i],sockets_y[i]));
		}
	}
	
	
	int Diagram2::distribution_p()//вычисление распределения по весу
	{
		double weight=0;
		for(int i=0;i<sockets_p.size();i++)
		{
			weight+=sockets_p[i];
		}
		
		//генерим точку
		double q=double(rand()%10000)/10000;
		double sum=0;
		int j = 0;
		//определение промежутка куда попало
		for(j=0;j<sockets_p.size();j++)
		{
			if(q>sum && q<(sum+sockets_p[j]/weight))
			{
				break;
			}
			sum+=sockets_p[j] / weight;
		}
		return j;
	}
	double Diagram2::weight_function(int x, int y)//вычисление весовой функции без нормировки
	{
		return pow(double(x*x+y*y),alpha/2.0);
	}





Diagram2::Diagram2(vector<int> & s, bool f) {
	if (s[0] == 0)
	{// нам пришла пустая диграмма
		Diagram2();
	}
	alpha=0;
	if (f) //на вход поданы строки
	{
		//ищем сумму и множество столбцов
			for(int i=0;i<s[0];i++) //s[0] показывает сколько столбцов
			{
				int k = 0;
				while (s[k] >= i+1)
				{
					k++;
					if (k == s.size())
					{
						break;
					}
				} 
				col.push_back(k);
				count += k;
				
			}
			for (int i = 0; i < s.size(); i++) {
				str.push_back(s[i]);
			}
		
	}else
	{
		for (int i = 0; i<s[0]; i++) //s[0] показывает сколько строк
		{
			int k = 0;
			while (s[k] >= i + 1)
			{
				k++;
				if (k == s.size())
				{
					break;
				}
			}
			str.push_back(k);
			count += s[i];
		}
		for (int i = 0; i < s.size(); i++) {
			col.push_back(s[i]);
		}
	}
	calculate_value();
	calculate_p();
}

void Diagram2::calculate_value() {
	if (count == 0)
	{
		return;
	}


	// проверяем вырожденные случаи  для угловых точек
	if (str.size()==1 || col.size()==1)
	{
		angular_points.push_back(str[0]);
		angular_points.push_back(col[0]);
		corners_x.push_back(str[0]);
		corners_y.push_back(col[0]);
	}else {

		// идем с двух сторон
		int k = 0;
		int j = col.size() - 1;

		while(j>=0 && k<str.size() )
		{
			//находим скочки
			while (k<str.size()-1 && str[k] <= str[k + 1])
			{
				k++;
			}

			while (j > 0 && col[j] >= col[j - 1])
			{
				j--;
			}

			angular_points.push_back(str[k]);//коорднината x
			angular_points.push_back(col[j]);//y
			corners_x.push_back(str[k]);
			corners_y.push_back(col[j]);
			k++;
			j--;
		}
	}
	//вычисляем углоовое дополнение
	// первая иттерация
	angular_complements.push_back(angular_points[0]+1);
	angular_complements.push_back(1);

	sockets_x.push_back(corners_x[0]+1);
	sockets_y.push_back(1);
	//основная иттерация
	for (int i = 2; i < angular_points.size(); i+=2)
	{
		angular_complements.push_back(angular_points[i] +1);
		angular_complements.push_back(angular_points[i-1] + 1);
	}
	for (int i = 1; i < corners_x.size(); i++)
	{
		sockets_x.push_back(corners_x[i] + 1);
		sockets_y.push_back(corners_y[i-1] + 1);
	}
	//последняя иттерация
	angular_complements.push_back(1);
	angular_complements.push_back(angular_points[angular_points.size()-1]+1);
	sockets_x.push_back(1);
	sockets_y.push_back(corners_y[corners_y.size()-1]+1);
}

void Diagram2::recalculate(int x, int y) {
	// пересчет угловых точек
	//удаление точек содержащие данные координаты
	int ix = search_element(corners_x, x);
	if (ix != -1)
	{
		//удаляем угловое дополнения для этой точки
		sockets_x.erase(sockets_x.begin() + ix );
		sockets_y.erase(sockets_y.begin() + ix+1);
		corners_x.erase(corners_x.begin() + ix);
		corners_y.erase(corners_y.begin() + ix);

	}
	int iy = search_element(corners_y, y);
	if (iy != -1)
	{
		sockets_x.erase(sockets_x.begin() + iy);
		sockets_y.erase(sockets_y.begin() + iy+1);
		corners_x.erase(corners_x.begin() + iy);
		corners_y.erase(corners_y.begin() + iy);
	}

	//добавление новой точки
	if (ix == -1 && iy == -1)
	{
		//поиск позиции
		int ix1 = insert_element(corners_x, x);
		if (ix1 != -1)
		{
			corners_x.insert(corners_x.begin() + ix1, x);
			corners_y.insert(corners_y.begin() + ix1, y);
		}else {
			std::cout << "Error: insert_element\n";
		}
	}else if (iy != -1)
	{
		//делаем вставку по iy
		corners_x.insert(corners_x.begin() + iy, x);
		corners_y.insert(corners_y.begin() + iy, y);
	}else {
		//делаем вставку по ix
		corners_x.insert(corners_x.begin() + ix, x);
		corners_y.insert(corners_y.begin() + ix, y);
	}
	// вставляем угловое дополнение
	int ix1 = insert_element(sockets_x, x + 1);
	int iy1 = insert_element(sockets_y, y + 1);
	//поиск не даст правильного ответа, если не сможет определить порядок сортировки
	if (sockets_y.size() == 1 && sockets_y[0] < y)
	{
		iy1=1;
	}

	if (sockets_x.size() == 1 && sockets_x[0] > x)
	{
		ix1 = 1;
	}

	sockets_x.insert(sockets_x.begin() + ix1, x+1);
	sockets_y.insert(sockets_y.begin() + iy1, y+1);
}

void Diagram2::add_vertex(int x, int y)
{
	if (x == 1)
	{
		str.push_back(1);
	}
	else
	{
		str[y - 1]++;
	}

	if (y == 1)
	{
		col.push_back(1);
	}
	else
	{
		col[x - 1]++;
	}
	count++;
	recalculate(x,y);
	calculate_p();
}

void Diagram2::processR(int n=1) {
	for (int i=0; i < n;i++) {
		int k = rand() % (sockets_x.size());
		add_vertex(sockets_x[k],sockets_y[k]);
		if(i % 100000 == 0) {
			cout << i << "\n";
		}
	}
}

int Diagram2::search_element(vector<int> & v, int x) {
	//значем, что массив отсортирован
	//вектор пуст
	if (v.size() == 0) {
		return -1;
	}
	//если равно последнему значению (цикл не работает)
	if (v[v.size() - 1] == x)
	{
		return v.size() - 1;
	}

	//узнаем, как он отсортирован
	int x1 = 0;
	int x2 = 0;
	int x22 = -1;
	int x3 = 0;
	if (v[0] < v[v.size() - 1]) //по убыванию
	{
		x1 = 0;
		x3 = v.size() - 1;
	}
	else if (v[0] > v[v.size() - 1]) { //по возрастанию
		x1 = v.size() - 1;
		x3 = 0;
	}
	else {// всего один элемент в векторе возвращаем его нулевой индекс
		if (v[0] == x) {
			return 0;
		}
		else {
			return -1;
		}
	}


	//алгоритм бинарного поиска
	x2 = (x1 + x3) / 2;
	while (x2!=x22){
		if (v[x2] == x) {
			return x2;
		}
		if (v[x2] > x) {
			x3 = x2;
		}
		else {
			x1 = x2;
		}
		x22 = x2;
		x2 = (x1 + x3) / 2;
	} 
	return -1;
}

int Diagram2::insert_element(vector<int> & v, int x) {
	//значем, что массив отсортирован
	//узнаем, как он отсортирован
	if (v.size() == 0) {
		return 0;
	}
	

	int x1 = 0;
	int x2 = 0;
	int x22 = 0;
	int x3 = 0;
	if (v[0] < v[v.size() - 1]) //по убыванию
	{
		x1 = 0;
		x3 = v.size() - 1;

		if (v[x3] < x) { //если максимальное число меньше заданного
			return x3+1;
		}
		else if (v[x1] > x) //если заданное число меньше наименьшего
		{
			return x1;
		}
	}
	else if (v[0] > v[v.size() - 1]) { //по возрастанию
		x1 = v.size() - 1;
		x3 = 0;

		if (v[x3] < x) { //если максимальное число меньше заданного
			return x3;
		}
		else if (v[x1] > x) //если заданное число меньше наименьшего
		{
			return x1+1;
		}
	}
	else {// всего один элемент в векторе и мы не знаем как он отсортирован
		return 0;
	}



	//алгоритм бинарного поиска
	x2 = (x1 + x3) / 2;
	while (x2 != x22) {
		if (v[x2] == x) {
			return -1;
		}
		if (v[x2] > x) {
			x3 = x2;
		}
		else {
			x1 = x2;
		}
		x22 = x2;
		x2 = (x1 + x3) / 2;
	}


	//если данное число не входит в интервал 
	return (x3>x1) ? x3 : x1; 
}

int Diagram2::get_count() {
	return count;
}
const vector<int> & Diagram2::get_diag_str() {
	return str;
}
const vector<int> & Diagram2::get_diag_col() {
	return col;
}
const vector<int> & Diagram2::get_angular_point(){
	for (int i = 0;i < corners_x.size();i++) {
		std::cout << "( " << corners_x[i] << ", " << corners_y[i] << ")";
	}
	return angular_points;
}
const vector<int> & Diagram2::get_angular_complements(){
	for (int i = 0;i < sockets_x.size();i++) {
		std::cout << "( " << sockets_x[i] << ", " << sockets_y[i] << ")";
	}
	return angular_complements;
}
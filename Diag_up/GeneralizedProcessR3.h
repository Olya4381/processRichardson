#pragma once
#include "Diagram3.h"
class GeneralizedProcessR3 :
	public Diagram3
{
private:
	double alpha;
	double weight;
	map<std::pair<int, int>, double> sockets_p;//
	/*Структура map(x,y)=weight_function*/
private:
	std::pair<int,int> distribution_p(int rn);
	void init_gener_process(double a); //инициализация нового процесса
	void calculate_p(); //первоначальное вычиление весов
	double weight_function(int x, int y, int z);//весовая функция
	//переопределяемые методы
	void add_vertex(int x, int y, int z);//добавление вершины
	void add_point_sockets1(int x, int y, int z); /*добавлеие угловой доп в мэп*/
	void del_point_sockets(int x, int y, int z); /*удаление угл точки в мэп*/
public:
	void generalized_processR3(int n, double alh); //обобщенный процесс Ричардсона
	void processR(int n = 1);//процесс Ричардсона
	GeneralizedProcessR3() :Diagram3() {};
	~GeneralizedProcessR3() {};
};


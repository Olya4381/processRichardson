#include "Diagram3.h"
#include <new>
#include <fstream>
Diagram3::Diagram3()
{
	//создаем диграмму размерности 1
	level.push_back(new class Diagram2());
	
	//calculate_sockets();
	init_sockets();
}

Diagram3::~Diagram3()
{
	for (int i = 0; i < level.size(); i++)
	{
		delete level[i];
	}
}
void Diagram3::init_sockets()
{
	for (int i = 0; i < level.size(); i++)
	{
		for (int j = 0;j < level[i]->sockets_x.size();j++)
		{
			add_point_sockets1(level[i]->sockets_x[j], level[i]->sockets_y[j], i + 1);
		}
	}
	add_point_sockets1(1, 1, level.size()+1);
}

void Diagram3::calculate_sockets() {
	//буфер
	sockets_x.clear();
	sockets_y.clear();
	sockets_z.clear();
	vector<int> com_x;//массивы отсортированы так же
	vector<int> com_y;
	int tmp_x = 0;
	int tmp_y = 0;
	//инициализируем начальное состояние
	int lev = 0;
	for (int i = 0; i < level[lev]->sockets_x.size(); i++)
	{
		add_point_sockets(level[lev]->sockets_x[i], level[lev]->sockets_y[i], lev+1);
		com_x.push_back(sockets_x[i]);
		com_y.push_back(sockets_y[i]);
	}
	//для оставшихся уровней
	for (int i = 1; i < level.size(); i++)
	{
		int k = 0;//индекс для com
		//для угловых дополнений текущего уровня
		for (int j = 0; j < level[i]->sockets_x.size(); j++)
		{
			tmp_x = level[i]->sockets_x[j];
			tmp_y = level[i]->sockets_y[j];
			while (com_x[k] > tmp_x)
			{
				k++;
			}
			//если x нашелся


			if (com_x[k] == tmp_x)
			{
				//сравниваем y
				if (com_y[k] != tmp_y)
				{
					//то добаляем точку и заменяет значение y
					add_point_sockets(tmp_x, tmp_y, i + 1);
					com_y[k] = tmp_y;
				}
			}
			else {
				//значит меньше ( инициализация  заполняет массив x  от минимального к максимальному)
				//значит точка 100% будет меньше или равна
				//точки не существует, добавляем ее
				add_point_sockets(tmp_x, tmp_y, i + 1);
				com_x.insert(com_x.begin() + k, tmp_x);
				com_y.insert(com_y.begin() + k, tmp_x);
			}
		}
	}
	//на помледний уровень 
	add_point_sockets(1, 1, level.size()+1);
}

void Diagram3::add_point_sockets(int x, int y, int z) {
	sockets_x.push_back(x);
	sockets_y.push_back(y);
	sockets_z.push_back(z);
}

void Diagram3::add_point_sockets1(int x, int y, int z)
{
	sockets[std::make_pair(x,y)].push(z*-1);
}

void Diagram3::del_point_sockets(int x, int y, int z)
{
	if (sockets[std::make_pair(x, y)].top() == z*-1) //требуемая точка находить на вершине очереди
	{
		sockets[std::make_pair(x, y)].pop();
		if(sockets[std::make_pair(x, y)].empty())
		{
			sockets.erase(std::make_pair(x, y));
		}
	}
	else//если не находиться
	{
		int min = sockets[std::make_pair(x, y)].top();//вытаскиваем все до требуемого значения
		do {
			sockets[std::make_pair(x, y)].pop();
		} while (min = sockets[std::make_pair(x, y)].top() > z*-1);

		while (min == z*-1)//заносим все обратно
		{
			sockets[std::make_pair(x, y)].push(min);
			min--;
		}

	}
}

void Diagram3::add_vertex(int x, int y, int z) {
	// вырожденный случай по level
	if (z > level.size())
	{
		level.push_back(new class Diagram2());
		del_point_sockets(1, 1, z);
		add_point_sockets1(1, 2, z);
		add_point_sockets1(2, 1, z);
		add_point_sockets1(1, 1, z+1);
	}
	else
	{
		mem_sock.clear();

		level[z - 1]->add_vertex(x, y,mem_sock);

		for (auto& item : mem_sock)
		{
			if (item.second > 0)
			{
				add_point_sockets1(item.first.first, item.first.second, z);
			}else if(item.second < 0)
			{
				del_point_sockets(item.first.first, item.first.second, z);
			}
		}


		/*for (int i = 0;i < del_sock.size();i += 2)
		{
			del_point_sockets(del_sock[i], del_sock[i + 1], z);
		}
		for (int i = 0;i < add_sock.size();i += 2)
		{
			add_point_sockets1(add_sock[i], add_sock[i + 1], z);
		}*/
	}
	//calculate_sockets();
}

void Diagram3::clear()
{
	for (int i = level.size() - 1;i > 0;i--)
	{
		delete level[i];
	}
	level[0]->clear();
}

void Diagram3::print_level() {
	for (int i = 0; i < level.size(); i++)
	{
		std::cout << i + 1 << ": ";
		level[i]->print_diag_col_s();
	}
}

void Diagram3::print_sockets() {
    /*std::cout << "sockets vec:\n";
	for (int i = 0; i < sockets_x.size(); i++)
	{
		std::cout << sockets_x[i] << '\t';
	}
	std::cout << "\n";
	for (int i = 0; i < sockets_x.size(); i++)
	{
		std::cout << sockets_y[i] << '\t';
	}
	std::cout << "\n";
	for (int i = 0; i < sockets_x.size(); i++)
	{
		std::cout << sockets_z[i] << '\t';
	}
	std::cout << "\n";*/

	std::cout << "sockets map:\n";
	for (auto& item : sockets)
	{
		cout << item.first.first << ' ' << item.first.second << " : " << item.second.top()*-1 << endl; //Вывод ключей и значений
	}
	std::cout << "\n";


}

//запись в файл
void Diagram3::print_in_file_col(char * file_name)
{
	if (file_name == NULL)
	{
		std::cout << "Error: file is NULL";
		return;
	}
	ofstream fout;
	fout.open(file_name);

	if (!fout.is_open()) {
		std::cout << "Error: file can't open\n";
		return;
	}

	for (auto item : level)
	{
		for (int i = 0; i < item->col.size(); i++)
		{
			fout << item->col[i] << " ";
		}
		if (item != level.back())
		{
			fout << " , ";
		}
	}
	fout.close();
	std::cout << "Write in file" << "done\n";

}

void Diagram3::print_in_file_col(string & file_name)
{
	if (file_name.empty())
	{
		std::cout << "Error: file is NULL";
		return;
	}

	ofstream fout;
	fout.open(file_name);

	if (!fout.is_open()) {
		std::cout << "Error: file can't open\n";
		return;
	}

	for (auto item : level)
	{
		for (int i = 0; i < item->col.size(); i++)
		{
			fout << item->col[i] << " ";
		}
		if (item != level.back())
		{
			fout << " , ";
		}
	}
	fout.close();
	std::cout << "Write in file" << "done\n";

}


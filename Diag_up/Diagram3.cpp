#include "Diagram3.h"
#include <new>

Diagram3::Diagram3()
{
	//������� �������� ����������� 1
	level.push_back(new class Diagram2());

	calculate_sockets();
}


Diagram3::~Diagram3()
{
	for (int i = 0; i < level.size(); i++)
	{
		delete level[i];
	}
}

void Diagram3::calculate_sockets() {
	//�����
	sockets_x.clear();
	sockets_y.clear();
	sockets_z.clear();
	vector<int> com_x;//������� ������������� ��� ��
	vector<int> com_y;
	int tmp_x = 0;
	int tmp_y = 0;
	//�������������� ��������� ���������
	int lev = 0;
	for (int i = 0; i < level[lev]->sockets_x.size(); i++)
	{
		add_point_sockets(level[lev]->sockets_x[i], level[lev]->sockets_y[i], lev+1);
		com_x.push_back(sockets_x[i]);
		com_y.push_back(sockets_y[i]);
	}
	//��� ���������� �������
	for (int i = 1; i < level.size(); i++)
	{
		int k = 0;//������ ��� com
		//��� ������� ���������� �������� ������
		for (int j = 0; j < level[i]->sockets_x.size(); j++)
		{
			tmp_x = level[i]->sockets_x[j];
			tmp_y = level[i]->sockets_y[j];
			while (com_x[k] > tmp_x)
			{
				k++;
			}
			//���� x �������

			if (com_x[k] == tmp_x)
			{
				//���������� y
				if (com_y[k] != tmp_y)
				{
					//�� �������� ����� � �������� �������� y
					add_point_sockets(tmp_x, tmp_y, i + 1);
					com_y[k] = tmp_y;
				}
			}
			else {
				//������ ������ ( �������������  ��������� ������ x  �� ������������ � �������������)
				//������ ����� 100% ����� ������ ��� �����
				//����� �� ����������, ��������� ��
				add_point_sockets(tmp_x, tmp_y, i + 1);
				com_x.insert(com_x.begin() + k, tmp_x);
				com_y.insert(com_y.begin() + k, tmp_x);
			}
		}
	}
	//�� ��������� ������� 
	add_point_sockets(1, 1, level.size()+1);
}

void Diagram3::add_point_sockets(int x, int y, int z) {
	sockets_x.push_back(x);
	sockets_y.push_back(y);
	sockets_z.push_back(z);
}

void Diagram3::add_vertex(int x, int y, int z) {
	// ����������� ������ �� level
	if (z > level.size())
	{
		level.push_back(new class Diagram2());
	}
	else
	{
		level[z - 1]->add_vertex(x, y);
	}
	calculate_sockets();
}

void Diagram3::print_level() {
	for (int i = 0; i < level.size(); i++)
	{
		std::cout << i + 1 << ": ";
		level[i]->print_diag_col_s();
	}
}

void Diagram3::print_sockets() {
	std::cout << "sockets:\n";
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
	std::cout << "\n";
}
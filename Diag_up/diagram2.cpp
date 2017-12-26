#include "diagram2.h"
#include <iostream>
#include <fstream>

Diagram2::Diagram2() {
	//�������� �������� ���� �������
	count = 1;
	str.push_back(1);
	col.push_back(1);
	// 0 ������� �����, 1 ������� ����������
	calculate_value();
}
Diagram2::Diagram2(vector<int> & s, bool f) {
	if (s[0] == 1)
	{// ��� ������ �������� �� ������ ��������
		Diagram2();
	} 

	if (f){ //�� ���� ������ ������
		//���� ����� � ��������� ��������
		for (int i = 0; i<s[0]; i++) //s[0] ���������� ������� ��������
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
			col.push_back(k);
			count += k;

		}
		for (int i = 0; i < s.size(); i++) {
			str.push_back(s[i]);
		}

	}else
	{
		for (int i = 0; i<s[0]; i++) //s[0] ���������� ������� �����
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
			count += k;
		}
		for (int i = 0; i < s.size(); i++) {
			col.push_back(s[i]);
		}
	}
	calculate_value();
}

Diagram2::Diagram2(char * name_file)//���������� �������� �� �����
{
	//������ ����
	count = 0;
	ifstream fin;
	fin.open(name_file);
	if (!fin.is_open()) {
		std::cout << "Error: file don't open\n";
		return;
	}
	//��������� �������
	int tmp;
	while (fin >> tmp)
	{
		col.push_back(tmp);
	}
	//������� ������
	for (int i = 0; i<col[0]; i++) //s[0] ���������� ������� �����
	{
		int k = 0;
		while (col[k] >= i + 1)
		{
			k++;
			if (k == col.size())
			{
				break;
			}
		}
		str.push_back(k);
		count += k;
	}
	//��������� ��������������

	calculate_value();

	fin.close();
}

Diagram2::Diagram2(string & name_file)//���������� �������� �� �����
{
	//������ ����
	count = 0;
	ifstream fin;
	fin.open(name_file);
	if (!fin.is_open()) {
		std::cout << "Error: file don't open\n";
		return;
	}
	//��������� �������
	int tmp;
	while (fin >> tmp)
	{
		col.push_back(tmp);
	}
	//������� ������
	for (int i = 0; i<col[0]; i++) //s[0] ���������� ������� �����
	{
		int k = 0;
		while (col[k] >= i + 1)
		{
			k++;
			if (k == col.size())
			{
				break;
			}
		}
		str.push_back(k);
		count += k;
	}


	//��������� ��������������
	calculate_value();
	fin.close();
}


void Diagram2::calculate_value() {
	if (corners_x.size()!=0){
		corners_x.clear();
		corners_y.clear();
		sockets_x.clear();
		sockets_y.clear();
		return;
	}

	// ��������� ����������� ������  ��� ������� �����
	if (str.size() == 1 || col.size() == 1){
		corners_x.push_back(str[0]);
		corners_y.push_back(col[0]);
	}
	else {
		// ���� � ���� ������
		int k = 0;
		int j = col.size() - 1;

		while (j >= 0 && k<str.size()){
			//������� ������
			while (k<str.size() - 1 && str[k] <= str[k + 1]){
				k++;
			}

			while (j > 0 && col[j] >= col[j - 1]){
				j--;
			}
			corners_x.push_back(str[k]);
			corners_y.push_back(col[j]);
			k++;
			j--;
		}
	}
	//��������� �������� ����������
	// ������ ���������

	sockets_x.push_back(corners_x[0] + 1);
	sockets_y.push_back(1);
	//�������� ���������
	for (int i = 1; i < corners_x.size(); i++){
		sockets_x.push_back(corners_x[i] + 1);
		sockets_y.push_back(corners_y[i - 1] + 1);
	}
	//��������� ���������
	sockets_x.push_back(1);
	sockets_y.push_back(corners_y[corners_y.size() - 1] + 1);
}
void Diagram2::recalculate(int x, int y) {
	// �������� ������� �����
	//�������� ����� ���������� ������ ����������
	int ix = search_element(corners_x, x,false);
	if (ix != -1)
	{
		//������� ������� ���������� ��� ���� �����
		del_points_sockets(ix);
		del_point_corners(ix);

	}
	int iy = search_element(corners_y, y,true);
	if (iy != -1)
	{
		del_points_sockets(iy);
		del_point_corners(iy);
	}

	//���������� ����� ������� �����
	if (ix == -1 && iy == -1)
	{
		//����� �������
		int ix1 = insert_element(corners_x, x,false);
		add_point_corners(x, y, ix1);
	}else if (iy != -1)
	{
		//������ ������� �� iy
		add_point_corners(x, y, iy);
	}else {
		//������ ������� �� ix
		add_point_corners(x, y, ix);
	}
	// ��������� ������� ����������
	int ix1 = insert_element(sockets_x, x + 1,false);
	//����� �� ���� ����������� ������, ���� �� ������ ���������� ������� ����������
	add_point_sockets(x + 1, y + 1, ix1);
}
int Diagram2::search_element(vector<int> & v, int x,bool f) {
	//������, ��� ������ ������������
	//������ ����
	if (v.size() == 0) {
		return -1;
	}
	//���� ����� ���������� �������� (���� �� ��������)
	if (v[v.size() - 1] == x)
	{
		return v.size() - 1;
	}

	//������, ��� �� ������������
	int x1 = 0;
	int x2 = 0;
	int x22 = -1;
	int x3 = 0;

	if (f) //�� �����������
	{
		x1 = 0;
		x3 = v.size() - 1;
	}
	else//�� ��������
	{
		x1 = v.size() - 1;
		x3 = 0;
	}
	//�������� ��������� ������
	x2 = (x1 + x3) / 2;
	while (x2 != x22) {
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
int Diagram2::insert_element(vector<int> & v, int x,bool f) {

	if (v.size() == 0) {
		return 0;
	}

	int x1 = 0;
	int x2 = 0;
	int x22 = -1;
	int x3 = 0;

	if (f) //�����������
	{
		x1 = 0;
		x3 = v.size() - 1;
		//��������  �� ����� �� �� ����������
		if(v[x3] < x)
		{
			return x3 + 1;
		}
	}else //��������
	{
		x1 = v.size() - 1;
		x3 = 0;
		if (v[x1] > x)
		{
			return x1 + 1;
		}
	}

	//�������� ��������� ������
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

	//���� ������ ����� �� ������ � �������� 
	return (x3>x1) ? x3 : x1;
}
void Diagram2::add_vertex(int x, int y)
{
	if (x == 1){
		str.push_back(1);
	}else{
		str[y - 1]++;
	}

	if (y == 1){
		col.push_back(1);
	}else{
		col[x - 1]++;
	}
	count++;
	recalculate(x, y);
}
void Diagram2::add_point_corners(int x, int y, int i) {
	corners_x.insert(corners_x.begin() + i, x);
	corners_y.insert(corners_y.begin() + i, y);
}
void Diagram2::add_point_sockets(int x, int y, int i) {
	sockets_x.insert(sockets_x.begin() + i, x);
	sockets_y.insert(sockets_y.begin() + i + 1, y);
}

void Diagram2::del_point_corners(int i) {
	corners_x.erase(corners_x.begin() + i);
	corners_y.erase(corners_y.begin() + i);
}
void Diagram2::del_points_sockets(int i) {
	sockets_x.erase(sockets_x.begin() + i);
	sockets_y.erase(sockets_y.begin() + i + 1);
}

void Diagram2::clear() {
	col.clear();
	str.clear();
	sockets_x.clear();
	corners_x.clear();
	sockets_y.clear();
	corners_y.clear();
	count = 1;
	str.push_back(1);
	col.push_back(1);
	calculate_value();
}

//������ � ����
void Diagram2::print_in_file_col(char * file_name)
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

	for (int i = 0; i < col.size(); i++)
	{
		fout << col[i] << " ";
	}
	fout.close();
	std::cout << "Write in file" << "done\n";

}

void Diagram2::print_in_file_col(string & file_name)
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

	for (int i = 0; i < col.size(); i++)
	{
		fout << col[i] << " ";
	}
	fout.close();
	std::cout << "Write in file" << "done\n";

}


//����� �� ������ ������
void Diagram2::print_count() {
	std::cout << "Size: " << count << '\n';
}
void Diagram2::print_diag_str() {
	std::cout << "String:{ ";
	for (int i = 0; i < str.size(); i++)
	{
		std::cout << str[i] << ", ";
	}
	std::cout << "}\n";
}
void Diagram2::print_diag_col() {
	std::cout << "Column:{ ";
	for (int i = 0; i < col.size(); i++)
	{
		std::cout << col[i] << ", ";
	}
	std::cout << "}\n";
}
void Diagram2::print_corners() {
	std::cout << "Corners: ";
	for (int i = 0; i < corners_x.size(); i++)
	{
		std::cout << "(" << corners_x[i] << " , " << corners_y[i] << ") ";
	}
	std::cout << "\n";
}
void Diagram2::print_sockets() {
	std::cout << "Sockets: ";
	for (int i = 0; i < sockets_x.size(); i++)
	{
		std::cout << "(" << sockets_x[i] << " , " << sockets_y[i] << ") ";
	}
	std::cout << "\n";
}
void Diagram2::print_picture() {
	std::cout << "Picture: \n";
	for (int i = str.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < str[i]; j++)
		{
			std::cout << ".  ";
		}
		std::cout << "\n";
	}
}

void Diagram2::print_diag_col_s() {
		for (int i = 0; i < col.size(); i++)
		{
			std::cout << col[i] << " ";
		}
		std::cout << "\n";
}
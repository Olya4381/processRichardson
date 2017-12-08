#include <iostream>
#include <vector>
#include "Diagram2.h"
#include <string>
#include <fstream>
void print_inf(Diagram2 * d);
void print_in_file(const vector<int> & vec, char* file_name=NULL);
int main(void)
{
	
	std::vector<int> str;
	str.push_back(1);

	Diagram2* d=new Diagram2(str,true);
	//d->init_generalized_processR(0.5);
	//d->generalized_processR(100000);
	//print_in_file(d->get_diag_col());
	
	//для альфа==0.5
	ofstream fout;
	fout.open("alpha.txt");
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
	}

	for (double a = 0; a <= 1.0; a += 0.05)
	{
		std::cout << a << "\n";
		d->init_generalized_processR(a);
		d->generalized_processR(10000);

		fout << a << "\t" << d->calculate_std_deviation() << "\n";
		//print_in_file(d->get_diag_col());
		d->clear_diag();
	}
	fout.close();
	delete d;
	return 0;
}

void print_inf(Diagram2 * d)
{
	std::cout << "Size: " << d->get_count() << '\n';
	const vector<int> s1 = d->get_diag_str();
	std::cout << "String:{ ";
	for (int i = 0; i < s1.size(); i++)
	{
		std::cout << s1[i] << ", ";
	}
	std::cout << "}\n";

	const vector<int> s2 = d->get_diag_col();
	std::cout << "Column:{ ";
	for (int i = 0; i < s2.size(); i++)
	{
		std::cout << s2[i] << ", ";
	}
	std::cout << "}\n";
	std::cout << "Picture: \n";
	for (int i = s1.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < s1[i]; j++)
		{
			std::cout << ".  ";
		}
		std::cout << "\n";
	}
	std::cout << "Corners:{ ";
	const vector<int> s3 = d->get_angular_point();
	//for (int i = 0; i < s3.size(); i += 2)
	//{
	//	std::cout << "( " << s3[i] << " , " << s3[i + 1] << ") , ";
	//}
	std::cout << "}\n";
	std::cout << "Sockets:{ ";
	const vector<int> s4 = d->get_angular_complements();
	//for (int i = 0; i < s4.size(); i += 2)
	//{
	//	std::cout << "( " << s4[i] << " , " << s4[i + 1] << ") , ";
	//}
	std::cout << "}\n................................................\n";
}

void print_in_file(const vector<int> & vec,char* file_name) {
	ofstream fout;
	if (file_name) {
		fout.open(file_name);
	}
	else {
		fout.open("out.txt");
	}
	if (!fout.is_open()) {
		std::cout << "Error: file don't open\n";
		return;
	}

	for (int i = 0; i < vec.size();i++)
	{
		fout << vec[i] << " ";
	}
	fout.close();
	std::cout << "Write in file" << "done\n";
}
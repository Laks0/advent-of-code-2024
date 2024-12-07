#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool es_posible(long int objetivo, vector<int>& terminos, int i) {
	if (i == 0) return objetivo == terminos[0];
	int n = terminos[i];
	if (objetivo % n != 0) return es_posible(objetivo-n, terminos, i-1);
	return es_posible(objetivo/n, terminos, i-1) || es_posible(objetivo-n, terminos, i-1);
}

bool es_posible_concat(long int objetivo, vector<int>& terminos, int i) {
	if (i == 0) return objetivo == terminos[0];
	int n = terminos[i];
	int digitos_n = log10(n);
	int digitos_obj = log10(objetivo);
	int base = pow(10, digitos_n+1);
	bool puede_concatenar = digitos_obj > digitos_n && objetivo % base == n;
	bool por_concat = puede_concatenar && es_posible_concat(objetivo/base, terminos, i-1);
	if (objetivo % n != 0) return por_concat || es_posible_concat(objetivo-n, terminos, i-1);
	return por_concat || es_posible_concat(objetivo/n, terminos, i-1) || es_posible_concat(objetivo-n, terminos, i-1);
}

long int parte1(vector<long int>& objetivos, vector<vector<int>>& terminos) {
	long int res = 0;
	for (int i = 0; i < objetivos.size(); i++)
		if (es_posible(objetivos[i], terminos[i], terminos[i].size()-1)) res+=objetivos[i];
	return res;
}

long int parte2(vector<long int>& objetivos, vector<vector<int>>& terminos) {
	long int res = 0;
	for (int i = 0; i < objetivos.size(); i++)
		if (es_posible_concat(objetivos[i], terminos[i], terminos[i].size()-1)) res+=objetivos[i];
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<long int> objetivos;
	vector<vector<int>> terminos;

	string line;
	while (getline(input, line)) {
		int i = line.find(": ");
		objetivos.push_back(stol(line.substr(0,i)));

		stringstream ss(line.substr(i+2));
		vector<int> op;
		string n;
		while (getline(ss,n,' ')) op.push_back(stoi(n));
		terminos.push_back(op);
	}

	cout << "Parte 1: " << parte1(objetivos, terminos) << endl;
	cout << "Parte 2: " << parte2(objetivos, terminos) << endl;
}

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

map<pair<long int, int>, long int> mem;

long int piedras_que_deja(long int p, int pasos) {
	if (pasos <= 0) return 1;

	pair<long int, int> estado(p, pasos);
	if (mem.count(estado) == 1) return mem.at(estado);

	int digitos = log10(p) + 1;
	long int res;
	if (p == 0) {
		res = piedras_que_deja(1, pasos-1);
	}
	else if (digitos % 2 == 0) {
		long int potencia = pow(10, digitos/2);
		res = piedras_que_deja(p%potencia, pasos-1) + piedras_que_deja(p/potencia, pasos-1);
	}
	else res = piedras_que_deja(p*2024, pasos-1);

	mem.insert(make_pair(estado, res));
	return res;
}

long int parte1(vector<int>& piedras) {
	long int res = 0;
	for (int p : piedras) res += piedras_que_deja(p, 25);
	return res;
}

long int parte2(vector<int>& piedras) {
	long int res = 0;
	for (int p : piedras) res += piedras_que_deja(p, 75);
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<int> piedras;

	regex numero("\\d+");
	string line;
	getline(input, line);
	sregex_token_iterator it(line.begin(), line.end(), numero);
	sregex_token_iterator end;
	while (it != end) {
		piedras.push_back(stoi(*it));
		++it;
	}

	cout << "Parte 1: " << parte1(piedras) << endl;
	cout << "Parte 2: " << parte2(piedras) << endl;
}

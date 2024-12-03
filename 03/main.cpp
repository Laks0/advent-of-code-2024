#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

// Toma un string de la forma 'mul(a,b)'
int resultado_operacion(string op) {
	regex oper("\\d{1,3}");
	auto opIterator = sregex_iterator(op.begin(), op.end(), oper);
	int a = stoi(opIterator->str());
	++opIterator;
	int b = stoi(opIterator->str());
	return a*b;
}

int parte1(vector<string>& programa) {
	int res = 0;

	regex inst("mul\\(\\d{1,3},\\d{1,3}\\)");
	for (string line : programa) {
		auto begin = sregex_iterator(line.begin(), line.end(), inst);
		auto end = sregex_iterator();
		for (sregex_iterator i = begin; i != end; ++i) {
			res += resultado_operacion(i->str());
		}
	}

	return res;
}

int parte2(vector<string>& programa) {
	int res = 0;

	regex inst("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");
	regex oper("\\d{1,3}");
	bool active = true;
	for (string line : programa) {
		auto begin = sregex_iterator(line.begin(), line.end(), inst);
		auto end = sregex_iterator();
		for (sregex_iterator i = begin; i != end; ++i) {
			string match = i->str();
			if (match=="do()") {
				active = true;
				continue;
			}
			if (match=="don't()") {
				active = false;
				continue;
			}
			if (!active) continue;
			res += resultado_operacion(match);
		}
	}

	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	string line;
	vector<string> programa;
	while (getline(input, line)) {
		programa.push_back(line);
	}

	cout << "Parte 1: " << parte1(programa) << endl;
	cout << "Parte 2: " << parte2(programa) << endl;
}

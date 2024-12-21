#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using estado = map<string, long int>;

estado derivar(estado actual, char c) {
	estado nuevo;
	for (pair<string, long int> entrada : actual) {
		string k = entrada.first; long int i = entrada.second;
		if (k[0] != c) continue;
		string d = k;
		if (d.size() > 0) d = d.substr(1);
		if (nuevo.count(d) == 0) {nuevo.emplace(d, i); continue;}
		nuevo[d] += i;
	}
	return nuevo;
}

void transiciones_vacias(estado& actual, vector<string>& palabras) {
	if (actual.count("") == 0) return;
	long int i = actual[""];
	for (string p : palabras) {
		if (actual.count(p) == 0) actual.emplace(p, i);
		else actual[p] += i;
	}
	actual.erase("");
}

long int formas_de_armar(string pattern, vector<string>& palabras) {
	estado s;
	s.emplace("", 1);
	for (char &c : pattern) {
		transiciones_vacias(s, palabras);
		s = derivar(s, c);
	}
	if (s.count("") == 0) return 0;
	return s[""];
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<string> patterns;
	vector<string> palabras;
	int i = 0;
	string line;
	while (getline(input, line)) {
		if (i == 0) {
			line.erase(remove(line.begin(), line.end(), ' '), line.end());
			stringstream ss(line);
			string p;
			while (getline(ss, p, ',')) palabras.push_back(p);
			i++;
			continue;
		}
		if (i == 1) {i++;continue;}
		patterns.push_back(line);
	}

	long int parte1 = 0;
	long int parte2 = 0;
	for (string p : patterns) {
		long int i = formas_de_armar(p, palabras);
		if (i != 0) parte1++;
		parte2 += i;
	}

	cout << "Parte 1: " << parte1 << endl;
	cout << "Parte 2: " << parte2 << endl;
}

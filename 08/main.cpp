#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool en_rango(int x, int y, int ancho, int alto) {
	return x >= 0 && y >= 0 && x < ancho && y < alto;
}

int parte1(map<char, vector<pair<int, int>>>& antenas, int alto, int ancho, vector<char>& frecuencias) {
	vector<vector<bool>> antinodo(ancho, vector<bool>(alto, false));
	for (char c : frecuencias) {
		for (pair<int, int> a : antenas[c]) {
			for (pair<int, int> b : antenas[c]) {
				if (a == b) continue;
				int dx = a.first - b.first;
				int dy = a.second - b.second;
				if (en_rango(a.first+dx, a.second+dy, ancho, alto)) antinodo[a.first+dx][a.second+dy] = true;
				if (en_rango(b.first-dx, b.second-dy, ancho, alto)) antinodo[b.first-dx][b.second-dy] = true;
			}
		}
	}

	int res = 0;
	for (auto f : antinodo)
		for (auto x : f)
			if (x) res++;
	return res;
}

int parte2(map<char, vector<pair<int, int>>>& antenas, int alto, int ancho, vector<char>& frecuencias) {
	vector<vector<bool>> antinodo(ancho, vector<bool>(alto, false));
	for (char c : frecuencias) {
		for (pair<int, int> a : antenas[c]) {
			for (pair<int, int> b : antenas[c]) {
				if (a == b) continue;
				int dx = a.first - b.first;
				int dy = a.second - b.second;
				pair<int, int> pos = a;
				while (en_rango(pos.first, pos.second, ancho, alto)) {
					antinodo[pos.first][pos.second] = true;
					pos.first += dx;
					pos.second += dy;
				}
				pos = b;
				while (en_rango(pos.first, pos.second, ancho, alto)) {
					antinodo[pos.first][pos.second] = true;
					pos.first -= dx;
					pos.second -= dy;
				}
			}
		}
	}

	int res = 0;
	for (auto f : antinodo)
		for (auto x : f)
			if (x) res++;
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<char> frecuencias;
	map<char, vector<pair<int, int>>> antenas;
	int ancho = 0;
	int alto = 0;
	string line;
	while (getline(input, line)) {
		ancho = line.length();
		for (int x = 0; x < ancho; x++) {
			char c = line[x];
			if (c == '.') continue;
			if (antenas.count(c) == 0) {
				antenas.insert(make_pair(c, vector<pair<int, int>>()));
				frecuencias.push_back(c);
			}
			antenas[c].push_back(make_pair(x, alto));
		}
		alto++;
	}

	cout << "Parte 1: " << parte1(antenas, alto, ancho, frecuencias) << endl;
	cout << "Parte 2: " << parte2(antenas, alto, ancho, frecuencias) << endl;
}

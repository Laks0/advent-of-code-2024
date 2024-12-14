#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
using robot = tuple<int,int,int,int>;

pair<int, int> posicion(robot r, int ancho, int alto, int pasos) {
	pair<int, int> res(get<0>(r) + get<2>(r) * pasos, get<1>(r) + get<3>(r) * pasos);
	res.first += ancho * pasos;
	res.second += alto * pasos;
	res.first %= ancho;
	res.second %= alto;
	return res;
}

int parte1(vector<robot>& robots, int ancho, int alto) {
	int cuadrantes[2][2] = {0};
	int medio_ancho = ancho/2; int medio_alto = alto/2;
	for (robot r : robots) {
		pair<int, int> pos = posicion(r, ancho, alto, 100);
		if (pos.first == medio_ancho || pos.second == medio_alto) continue;
		cuadrantes[pos.first>medio_ancho][pos.second>medio_alto]++;
	}
	return cuadrantes[0][0] * cuadrantes[1][0] * cuadrantes[1][1] * cuadrantes[0][1];
}

void imprimir_mapas(vector<robot>& robots, int ancho, int alto, int cantidad) {
	for (int i = 100 ; i < cantidad; i++) {
		cout << i << endl;
		vector<vector<bool>> mapa(alto, vector<bool>(ancho, false));
		for (robot r : robots) {
			pair<int, int> pos = posicion(r, ancho, alto, i);
			mapa[pos.second][pos.first] = true;
		}
		for (vector<bool> x : mapa) {
			for (bool y : x) cout << (y ? '#' : '.');
			cout << endl;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<robot> robots;
	string line;
	while (getline(input, line)) {
		int px; int py; int vx; int vy;
		sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
		robots.emplace_back(px,py,vx,vy);
	}

	cout << "Parte 1 " << parte1(robots, 101, 103) << endl;
	imprimir_mapas(robots, 101, 103, 10000);
}

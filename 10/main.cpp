#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define EN_RANGO(x, y, w, h) (x >= 0 && y >= 0 && x < w && y < h)
using pos = pair<int, int>;
using subgrafo = map<pos, vector<pos>>;

// BFS
int cantidad_de_alcanzables(pos inicial, const vector<vector<int>>& mapa, subgrafo& arbol_bfs) {
	int alto = mapa.size();
	int ancho = mapa[0].size();
	int alcanzados = 0;
	vector<vector<bool>> visto(alto, vector<bool>(ancho, false));
	queue<pos> frontera;
	frontera.push(inicial);

	while (!frontera.empty()) {
		pos v = frontera.front();
		int vy = v.second;
		int vx = v.first;
		frontera.pop();

		if (visto[vy][vx]) continue;
		visto[vy][vx] = true;

		int vval = mapa[vy][vx];
		if (vval == 9) {alcanzados++; continue;}
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (dx != 0 && dy != 0) continue;
				int wx = vx+dx;
				int wy = vy+dy;
				if (EN_RANGO(wx, wy, ancho, alto) && (!visto[wy][wx]) && mapa[wy][wx] == vval+1) {
					pos w = make_pair(wx, wy);
					frontera.push(w);
					if (arbol_bfs.count(v) == 0) arbol_bfs.insert(make_pair(v, vector<pos>(1,w)));
					else arbol_bfs[v].push_back(w);
				}
			}
		}
	}

	return alcanzados;
}

int caminos_distintos(pos desde, vector<vector<int>>& mapa, subgrafo& arbol) {
	int x = desde.first;
	int y = desde.second;
	if (mapa[y][x] == 9) return 1;
	if (arbol.count(desde) == 0) return 0;
	int res = 0;
	for (pos hijo : arbol.at(desde)) {
		res += caminos_distintos(hijo, mapa, arbol);
	}
	return res;
}

int parte1(vector<vector<int>>& mapa) {
	int alto = mapa.size();
	int ancho = mapa[0].size();
	int res = 0;
	for (int y = 0; y < alto; y++) {
		for (int x = 0; x < ancho; x++) {
			if (mapa[y][x] != 0) continue;
			subgrafo arbol;
			res += cantidad_de_alcanzables(make_pair(x, y), mapa, arbol);
		}
	}
	return res;
}

int parte2(vector<vector<int>>& mapa) {
	int alto = mapa.size();
	int ancho = mapa[0].size();
	int res = 0;
	for (int y = 0; y < alto; y++) {
		for (int x = 0; x < ancho; x++) {
			if (mapa[y][x] != 0) continue;
			subgrafo arbol;
			cantidad_de_alcanzables(make_pair(x, y), mapa, arbol);
			res += caminos_distintos(make_pair(x, y), mapa, arbol);
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

	vector<vector<int>> mapa;
	string line;
	while (getline(input, line)) {
		vector<int> fila;
		for (char &c : line) fila.push_back(c - '0');
		mapa.push_back(fila);
	}

	cout << "Parte 1: " << parte1(mapa) << endl;
	cout << "Parte 2: " << parte2(mapa) << endl;
}

#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
// dist, x, y, dir
using dist_nodo = tuple<int, int, int, int>;
using vec_vertices = vector<vector<vector<int>>>;
#define EN_RANGO(x,y,w,h) (x >= 0 && y >= 0 && x < w && y < h)
#define DX(dir) (dir == 0 ? 1 : (dir == 2 ? -1 : 0))
#define DY(dir) (dir == 3 ? 1 : (dir == 1 ? -1 : 0))

// Dijkstra en 4 capas
vec_vertices camino_minimo(int x, int y, int dir_inicial, vector<vector<char>>& mapa, bool transpuesto) {
	int ancho = mapa[0].size(); int alto = mapa.size();
	vector<vector<vector<bool>>> visto(alto, vector<vector<bool>>(ancho, vector<bool>(4, false)));
	vec_vertices dist(alto, vector<vector<int>>(ancho, vector<int>(4, INT_MAX)));
	priority_queue<dist_nodo, vector<dist_nodo>, greater<>> q;
	q.emplace(0, x, y, dir_inicial);

	while (!q.empty()) {
		dist_nodo v = q.top();
		q.pop();
		int x = get<1>(v); int y = get<2>(v); int dir = get<3>(v);
		if (visto[y][x][dir]) continue;
		visto[y][x][dir] = true;
		dist[y][x][dir] = get<0>(v);

		for (int i = 0; i < 4; i++) {
			int nuevo_x = x; int nuevo_y = y; int nueva_dir = i;
			if (transpuesto) {
				nuevo_x -= DX(dir);
				nuevo_y -= DY(dir);
			}
			else {
				nuevo_x += DX(nueva_dir);
				nuevo_y += DY(nueva_dir);
			}

			if ((!EN_RANGO(nuevo_x, nuevo_y, ancho, alto)) || mapa[nuevo_y][nuevo_x] == '#') continue;
			int nueva_dist = get<0>(v) + (nueva_dir == dir ? 0 : 1000) + 1;
			q.emplace(nueva_dist, nuevo_x, nuevo_y, nueva_dir);
		}
	}

	return dist;
}

int parte1(vector<vector<char>>& mapa) {
	int s_x = 0; int s_y = 0;
	int e_x = 0; int e_y = 0;
	for (int y = 0; y < mapa.size(); y++) {
		for (int x = 0; x < mapa[0].size(); x++) {
			if (mapa[y][x] == 'S') {s_x = x; s_y = y;}
			if (mapa[y][x] == 'E') {e_x = x; e_y = y;}
		}
	}

	vec_vertices dist = camino_minimo(s_x, s_y, 0, mapa, false);
	int res = INT_MAX;
	for (int i = 0; i < 4; i++) res = min(res, dist[e_y][e_x][i]);
	return res;
}

int parte2(vector<vector<char>>& mapa) {
	int s_x = 0; int s_y = 0;
	int e_x = 0; int e_y = 0;
	for (int y = 0; y < mapa.size(); y++) {
		for (int x = 0; x < mapa[0].size(); x++) {
			if (mapa[y][x] == 'S') {s_x = x; s_y = y;}
			if (mapa[y][x] == 'E') {e_x = x; e_y = y;}
		}
	}

	int res = 0;
	vec_vertices distancias_a_E[4];
	for (int i = 0; i < 4; i++) distancias_a_E[i] = camino_minimo(e_x, e_y, i, mapa, true);
	vec_vertices distancias_desde_S = camino_minimo(s_x, s_y, 0, mapa, false);
	int distancia_total_camino = INT_MAX;
	for (int i = 0; i < 4; i++)
		distancia_total_camino = min(distancia_total_camino, distancias_desde_S[e_y][e_x][i]);

	for (int y = 0; y < mapa.size(); y++) {
		for (int x = 0; x < mapa[0].size(); x++) {
			for (int dir = 0; dir < 4; dir++) {
				int desde_S = distancias_desde_S[y][x][dir];
				if (desde_S == INT_MAX) continue;
				int mejor_usando_nodo = INT_MAX;
				for (int i = 0; i < 4; i++) {
					int hasta_E = distancias_a_E[i][y][x][dir];
					if (hasta_E == INT_MAX) continue;
					mejor_usando_nodo = min(mejor_usando_nodo, desde_S + distancias_a_E[i][y][x][dir]);
				}

				if (mejor_usando_nodo == distancia_total_camino) {
					res++;
					break;
				}
			}
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

	vector<vector<char>> mapa;
	string line;
	while (getline(input, line))
		mapa.push_back(vector<char>(line.begin(), line.end()));

	cout << "Parte 1: " << parte1(mapa) << endl;
	cout << "Parte 2: " << parte2(mapa) << endl;
}

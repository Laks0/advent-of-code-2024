#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
#define EN_RANGO(x, y, w, h) (x >= 0 && y >= 0 && x < w && y < h)

bool hay_vistos_en_mismo_lado(pair<int, int> pos, int dx, int dy, int step, vector<vector<char>>& mapa, vector<vector<bool>>& visto) {
	int ancho = mapa[0].size(); int alto = mapa.size();
	int x = pos.first; int y = pos.second;
	// Nos movemos en la dirección en la que no estaba la frontera
	int search_dx = ((dx == 0) ? 1 : 0) * step;
	int search_dy = ((dy == 0) ? 1 : 0) * step;
	int alt_x = x + search_dx;
	int alt_y = y + search_dy;

	while (EN_RANGO(alt_x, alt_y, ancho, alto)) {
		// Me fui de la componente
		if (mapa[alt_y][alt_x] != mapa[y][x]) break;
		// Sigo en la componente pero terminó el lado
		if (EN_RANGO(alt_x+dx, alt_y+dy, ancho, alto) && mapa[alt_y+dy][alt_x+dx] == mapa[alt_y][alt_x])
			break;

		if (visto[alt_y][alt_x]) return true;
		alt_x += search_dx;
		alt_y += search_dy;
	}

	return false;
}

// BFS
tuple<int, int, int> area_perimetro_lados(pair<int, int> inicial, vector<vector<char>>& mapa, vector<vector<bool>>& visto) {
	queue<pair<int, int>> frontera;
	frontera.push(inicial);
	int area = 0;
	int perimetro = 0;
	int lados = 0;

	while (!frontera.empty()) {
		pair<int, int> v = frontera.front();
		frontera.pop();
		int vx = v.first; int vy = v.second;

		if (visto[vy][vx]) continue;
		visto[vy][vx] = true;
		area++;

		for (int dx = -1; dx <= 1; dx++) {for (int dy=-1; dy <= 1; dy++) {
			if (dy != 0 && dx != 0) continue;
			int wx = vx + dx; int wy = vy + dy;
			if (!EN_RANGO(wx, wy, mapa[0].size(), mapa.size()) || mapa[wy][wx] != mapa[vy][vx]) {
				perimetro++;

				if ((!hay_vistos_en_mismo_lado(v, dx, dy, 1, mapa, visto)) && (!hay_vistos_en_mismo_lado(v, dx, dy, -1, mapa, visto)))
					lados++;

				continue;
			}

			frontera.push(make_pair(wx,wy));
		}}
	}

	return make_tuple(area, perimetro, lados);
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


	int parte1 = 0;
	int parte2 = 0;
	vector<vector<bool>> visto(mapa.size(), vector<bool>(mapa[0].size(), false));

	for (int x = 0; x < mapa[0].size(); x++) {
		for (int y = 0; y < mapa.size(); y++) {
			if (visto[y][x]) continue;
			tuple<int, int, int> datos = area_perimetro_lados(make_pair(x, y), mapa, visto);
			parte1 += get<0>(datos) * get<1>(datos);
			parte2 += get<0>(datos) * get<2>(datos);
		}
	}

	cout << "Parte 1: " << parte1 << endl;
	cout << "Parte 2: " << parte2 << endl;
}

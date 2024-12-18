#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define EN_RANGO(x,y,w,h) (x >= 0 && y >= 0 && x < w && y < h)
#define DX(dir) (dir == 0 ? 1 : (dir == 2 ? -1 : 0))
#define DY(dir) (dir == 3 ? 1 : (dir == 1 ? -1 : 0))

// BFS
int distancia(vector<vector<bool>>& pared) {
	int ancho = pared.size();
	vector<vector<int>> dist(ancho, vector<int>(ancho, -1));
	queue<pair<int, int>> frontera;
	frontera.emplace(0,0);
	dist[0][0] = 0;

	while (!frontera.empty()) {
		pair<int, int> v = frontera.front();
		frontera.pop();

		int vx = v.first; int vy = v.second;

		for (int dir = 0; dir < 4; dir++) {
			int nuevo_x = vx + DX(dir);
			int nuevo_y = vy + DY(dir);
			if (!EN_RANGO(nuevo_x, nuevo_y, ancho, ancho) || pared[nuevo_y][nuevo_x]) continue;
			if (dist[nuevo_y][nuevo_x] != -1) continue;

			dist[nuevo_y][nuevo_x] = dist[vy][vx] + 1;
			frontera.emplace(nuevo_x, nuevo_y);
		}
	}

	return dist[ancho-1][ancho-1];
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	int ancho = 71;
	int bytes = 1024;
	vector<vector<bool>> pared(ancho, vector<bool>(ancho, false));
	int i = 1;
	string line;
	while (getline(input, line)) {
		int x; int y;
		sscanf(line.c_str(), "%d,%d", &x, &y);
		pared[y][x] = true;

		int dist = distancia(pared);
		if (i == bytes)
			cout << "Parte 1: " << dist << endl;

		if (dist == -1) {
			cout << "Parte 2: " << x << "," << y << endl;
			break;
		}

		i++;
	}
}

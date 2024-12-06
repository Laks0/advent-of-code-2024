#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool es_ciclo(vector<vector<bool>>& obstaculos, pair<int, int> pos, vector<vector<vector<bool>>>& visto) {
	int ancho = obstaculos[0].size(); int alto = obstaculos.size();
	int dir = 1; // 0 = E, 1 = N, 2 = O, 3 = S. Restar 1 son 90° a la derecha
	while (true) {
		if (visto[pos.second][pos.first][dir]) return true;
		visto[pos.second][pos.first][dir] = true;
		pair<int, int> new_pos = pos;
		switch (dir) {
			case 0:
				new_pos.first += 1;
				break;
			case 1:
				new_pos.second -= 1;
				break;
			case 2:
				new_pos.first -= 1;
				break;
			case 3:
				new_pos.second += 1;
				break;
		}

		if (new_pos.first < 0 || new_pos.second < 0 || new_pos.first >= ancho || new_pos.second >= alto)
			break;
		if (obstaculos[new_pos.second][new_pos.first]) dir = (dir+3) % 4;
		else pos = new_pos;
	}

	return false;
}

int parte1(vector<vector<bool>>& obstaculos, pair<int, int> pos) {
	vector<vector<vector<bool>>> visto(obstaculos.size(), vector<vector<bool>>(obstaculos[0].size(), vector<bool>(4, false)));
	es_ciclo(obstaculos, pos, visto);

	int res = 0;
	for (vector<vector<bool>> fila : visto)
		for (auto c : fila)
			for (int i = 0; i < 4; i++) if (c[i]) {res++; break;}
	return res;
}

// Lentísimo jeje
int parte2(vector<vector<bool>>& obstaculos, pair<int, int> pos) {
	vector<vector<vector<bool>>> camino_original(obstaculos.size(), vector<vector<bool>>(obstaculos[0].size(), vector<bool>(4, false)));
	es_ciclo(obstaculos, pos, camino_original);

	int res = 0;
	for (int y = 0; y < obstaculos.size(); y++) {
		for (int x = 0; x < obstaculos[0].size(); x++) {
			bool en_camino_original = false;
			for (int i = 0; i < 4; i++) en_camino_original |= camino_original[y][x][i];
			if (!en_camino_original) continue;
			if (x == pos.first && y == pos.second) continue;

			vector<vector<vector<bool>>> visto(obstaculos.size(), vector<vector<bool>>(obstaculos[0].size(), vector<bool>(4, false)));
			obstaculos[y][x] = true;
			if (es_ciclo(obstaculos, pos, visto)) res++;
			obstaculos[y][x] = false;
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

	pair<int, int> pos;
	vector<vector<bool>> obstaculos;
	string line;
	int y = 0;
	while (getline(input, line)) {
		vector<bool> fila;
		int x = 0;
		for (char& c : line) {
			fila.push_back(c == '#');
			if (c == '^') pos = make_pair(x, y);
			x++;
		}
		obstaculos.push_back(fila);
		y++;
	}

	cout << "Parte 1: " << parte1(obstaculos, pos) << endl;
	cout << "Parte 2: " << parte2(obstaculos, pos) << endl;
}

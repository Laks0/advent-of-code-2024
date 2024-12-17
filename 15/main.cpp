#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define EN_RANGO(x,y,w,h) (x >= 0 && y >= 0 && x < w && y < h)

bool se_puede_mover(int x, int y, int dx, int dy, vector<vector<char>>& mapa) {
	int alto = mapa.size(); int ancho = mapa[0].size();
	while (EN_RANGO(x, y, ancho, alto)) {
		char objeto = mapa[y][x];
		if (objeto == '#') return false;
		if (objeto == '.') return true;

		if (dy != 0 && objeto == '[' && !se_puede_mover(x+1, y+dy, dx, dy, mapa)) return false;
		if (dy != 0 && objeto == ']' && !se_puede_mover(x-1, y+dy, dx, dy, mapa)) return false;

		x += dx; y += dy;
	}
	return false;
}

void mover_elemento(int x, int y, int dx, int dy, vector<vector<char>>& mapa, vector<vector<bool>>& movido) {
	if (movido[y][x]) return;
	movido[y][x] = true;

	char objeto = mapa[y][x];
	if (objeto == '.') return;

	mover_elemento(x+dx, y+dy, dx, dy, mapa, movido);
	if (dy != 0 && (objeto == '[' || objeto == ']')) {
		int otro_x = objeto == ']' ? x-1 : x+1;
		mover_elemento(otro_x, y, dx, dy, mapa, movido);
	}

	mapa[y+dy][x+dx] = mapa[y][x];
	mapa[y][x] = '.';
}

void seguir_secuencia(vector<vector<char>>& mapa, vector<char>& movimientos) {
	int x = 0; int y = 0;
	for (int i = 0; i < mapa.size(); i++) {
		for (int j = 0; j < mapa[0].size(); j++) {
			if (mapa[i][j] == '@') {
				x = j; y = i;
				break;
			}
		}
		if (x != 0) break;
	}

	for (char &m : movimientos) {
		int dx = 0; int dy = 0;
		switch (m) {
			case '<':
				dx = -1; break;
			case '>':
				dx = 1; break;
			case 'v':
				dy = 1; break;
			case '^':
				dy = -1; break;
		}

		if (se_puede_mover(x, y, dx, dy, mapa)){
			vector<vector<bool>> movido(mapa.size(), vector<bool>(mapa[0].size(), false));
			mover_elemento(x, y, dx, dy, mapa, movido);
			x += dx; y += dy;
		}
	}
}

int gps_final(vector<vector<char>>& mapa, vector<char>& movimientos) {
	seguir_secuencia(mapa, movimientos);
	int res = 0;
	for (int y = 0; y < mapa.size(); y++) {
		for (int x = 0; x < mapa[0].size(); x++) {
			if (mapa[y][x] == 'O' || mapa[y][x] == '[') res += y * 100 + x;
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

	vector<vector<char>> mapa_simple;
	vector<vector<char>> mapa_doble;
	vector<char> movimientos;
	bool viendo_mapa = true;
	string line;
	while (getline(input, line)) {
		if (line == "") {viendo_mapa = false; continue;}

		if (viendo_mapa) {
			mapa_simple.push_back(vector<char>(line.begin(), line.end()));
			
			vector<char> fila_doble;
			for (char &c : line) { switch (c) {
				case '.':
					fila_doble.push_back('.');
					fila_doble.push_back('.');
					break;
				case '#':
					fila_doble.push_back('#');
					fila_doble.push_back('#');
					break;
				case 'O':
					fila_doble.push_back('[');
					fila_doble.push_back(']');
					break;
				case '@':
					fila_doble.push_back('@');
					fila_doble.push_back('.');
					break;
			}}
			mapa_doble.push_back(fila_doble);
			continue;
		}

		for (char &c : line) movimientos.push_back(c);
	}

	cout << "Parte 1: " << gps_final(mapa_simple, movimientos) << endl;
	cout << "Parte 2: " << gps_final(mapa_doble, movimientos) << endl;
}

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

using namespace std;

vector<string> direcciones(vector<vector<char>>& mapa) {
	vector<string> direcciones;
	// Filas
	for (auto f : mapa) direcciones.push_back(string(f.begin(), f.end()));
	// Columnas
	for (int x = 0; x < mapa[0].size(); x++) {
		string col = "";
		for (int y = 0; y < mapa.size(); y++) col.push_back(mapa[y][x]);
		direcciones.push_back(col);
	}
	// Diagonales
	for (int y = 0; y < mapa.size(); y++) {
		string positiva_de_fila = "";
		string positiva_de_columna = "";
		string negativa_de_fila = "";
		string negativa_de_columna = "";
		int i = 0;
		while (y+i < mapa.size() && y+i < mapa[0].size()) {
			positiva_de_fila.push_back(mapa[y+i][i]);
			positiva_de_columna.push_back(mapa[i][y+i]);
			negativa_de_fila.push_back(mapa[y+i][mapa.size()-i-1]);
			negativa_de_columna.push_back(mapa[i][mapa.size()-i-1-y]);
			i++;
		}
		direcciones.push_back(positiva_de_fila);
		if (y != 0) direcciones.push_back(positiva_de_columna);
		direcciones.push_back(negativa_de_fila);
		if (y != 0) direcciones.push_back(negativa_de_columna);
	}
	return direcciones;
}

int parte1(vector<vector<char>>& mapa) {
	int res = 0;
	vector<string> dirs = direcciones(mapa);
	regex adelante("XMAS");
	regex atras("SAMX");
	for (string dir : dirs) {
		res += distance(sregex_iterator(dir.begin(), dir.end(), adelante), sregex_iterator());
		res += distance(sregex_iterator(dir.begin(), dir.end(), atras), sregex_iterator());
	}
	return res;
}

int parte2(vector<vector<char>>& mapa) {
	int res = 0;
	for (int y = 0; y < mapa.size(); y++) {
		for (int x = 0; x < mapa[0].size(); x++) {
			if (mapa[y][x] != 'A') continue;
			if (y-1 < 0 || y+1 >= mapa.size() || x-1 < 0 || x+1 >= mapa[0].size()) continue;
			string positiva = "";
			string negativa = "";
			positiva = positiva + mapa[y-1][x-1] + mapa[y+1][x+1];
			negativa = negativa + mapa[y-1][x+1] + mapa[y+1][x-1];
			if ((positiva == "MS" || positiva == "SM") && (negativa == "MS" || negativa == "SM")) res++;
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
	while (getline(input, line)) mapa.push_back(vector<char>(line.begin(), line.end()));

	cout << "Parte 1: " << parte1(mapa) << endl;
	cout << "Parte 2: " << parte2(mapa) << endl;
}

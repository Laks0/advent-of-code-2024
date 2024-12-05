#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool es_topologico(vector<vector<int>>& aristas, vector<int>& orden) {
	vector<bool> visto(100, false);
	bool res = true;
	for (int n : orden) {
		visto[n] = true;
		for (int v : aristas[n]) res = res && !visto[v];
		if (!res) break;
	}
	return res;
}

void reordenar(vector<vector<int>>& aristas, vector<int>& orden) {
	for (int i = 0; i < orden.size(); i++) {
		int u = orden[i];
		for (int j = 0; j < i; j++) {
			if (find(aristas[u].begin(), aristas[u].end(), orden[j]) != aristas[u].end()) {
				orden[i] = orden[j];
				orden[j] = u;
				break;
			}
		}
	}
}

int parte1(vector<vector<int>>& aristas, vector<vector<int>>& ordenes) {
	int res = 0;
	for (vector<int> orden : ordenes)
		if (es_topologico(aristas, orden)) res += orden[(int) orden.size()/2];
	return res;
}

int parte2(vector<vector<int>>& aristas, vector<vector<int>>& ordenes) {
	int res = 0;
	for (vector<int> orden : ordenes) {
		if (es_topologico(aristas, orden)) continue;
		while (!es_topologico(aristas, orden)) reordenar(aristas, orden);
		res += orden[(int) orden.size()/2];
	}
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;
	
	vector<vector<int>> aristas(100, vector<int>());
	vector<vector<int>> ordenes;

	bool parseando_aristas = true;
	string line;
	while (getline(input, line)) {
		if (line == "") {
			parseando_aristas = false;
			continue;
		}

		if (parseando_aristas) {
			int a = stoi(line.substr(0,2));
			int b = stoi(line.substr(3,2));
			aristas[a].push_back(b);
			continue;
		}

		vector<int> orden;
		stringstream ss(line);
		string n;
		while(getline(ss,n,',')) orden.push_back(stoi(n));
		ordenes.push_back(orden);
	}

	cout << "Parte 1: " << parte1(aristas, ordenes) << endl;
	cout << "Parte 2: " << parte2(aristas, ordenes) << endl;
}

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

bool mantiene_seguridad(int actual, int siguiente, bool increasing) {
	return actual != siguiente && actual < siguiente == increasing && abs(actual - siguiente) <= 3;
}

bool nivel_seguro(const vector<int>& nivel) {
	bool increasing = nivel[0] < nivel[1];
	bool safe = true;
	for (int i = 0; i < nivel.size() - 1; i++) {
		if (mantiene_seguridad(nivel[i], nivel[i+1], increasing)) continue;

		safe = false;
		break;
	}

	return safe;
}

int parte_a(const vector<vector<int>>& mapa) {
	int res = 0;

	for (vector<int> nivel : mapa)
		if (nivel_seguro(nivel)) res++;

	return res;
}

int parte_b(const vector<vector<int>>& mapa) {
	int res = 0;

	for (vector<int> nivel : mapa) {
		bool algun_seguro = false;
		for (int eliminado = 0; eliminado < nivel.size(); eliminado++) {
			vector<int> nuevo_nivel = nivel;
			nuevo_nivel.erase(nuevo_nivel.begin() + eliminado);
			if (nivel_seguro(nuevo_nivel)) {
				res++;
				algun_seguro = true;
				break;
			}
		}
		if (!algun_seguro && nivel_seguro(nivel)) res++;
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
		regex del(" ");
		sregex_token_iterator it(line.begin(), line.end(), del, -1);
		sregex_token_iterator end;

		vector<int> nivel;
		while (it != end) {
			nivel.push_back(stoi(*it));
			++it;
		}
		mapa.push_back(nivel);
	}

	cout << "Parte a: " << parte_a(mapa) << endl;
	cout << "Parte b: " << parte_b(mapa) << endl;
}

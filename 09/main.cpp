#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// La suma de todos los números entre a y b
long long suma_entre(int a, int b) {
	return (b - a + 1) * (a + b) / 2;
}

long long parte1(vector<int> layout) {
	if (layout.size() % 2 == 0) layout.pop_back();

	long long res = 0;
	long long pos = 0;
	for (int i = 0; i < layout.size(); i++) {
		// Las posiciones pares son archivos
		if (i%2 == 0) {
			int id = i/2;
			res += id * suma_entre(pos, pos+layout[i]-1);
			pos += layout[i];
			continue;
		}
		// Espacio vacío
		int a_llenar = layout[i];
		while (a_llenar > 0 && i < layout.size()) {
			int j = layout.size()-1;
			int ult = layout[j];
			if (a_llenar < ult) {
				layout[j] -= a_llenar;
				res += suma_entre(pos, pos+a_llenar-1) * (j/2);
				pos += a_llenar;
				break;
			}

			res += suma_entre(pos, pos+ult-1) * (j/2);
			pos += ult;
			a_llenar -= ult;
			layout.pop_back();
			layout.pop_back();
		}
	}
	return res;
}

long long parte2(vector<int> layout) {
	if (layout.size() % 2 == 0) layout.pop_back();

	vector<int> offset(layout.size(), 0);
	long long res = 0;
	for (int i = layout.size()-1; i >= 0; i-=2) {
		long long pos = 0;
		for (int j = 0; j < i; j++) {
			if (j%2 == 0 || layout[j] < layout[i]) {
				pos += layout[j] + offset[j];
				continue;
			}

			pos += offset[j];
			res += (i/2) * suma_entre(pos, pos + layout[i]-1);
			offset[j] += layout[i];
			layout[j] -= layout[i];
			layout[i] = 0;
		}
		res += (i/2) * suma_entre(pos, pos + layout[i]-1);
	}
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	vector<int> layout;
	string line;
	while (getline(input, line)) {
		for (char &c : line) layout.push_back(c - '0');
	}

	cout << "Parte 1: " << parte1(layout) << endl;
	cout << "Parte 2: " << parte2(layout) << endl;
}

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	// Para el a
	priority_queue<int> heap_1;
	priority_queue<int> heap_2;
	// Para el b
	map<int, int> frecuencias;
	vector<int> primera_lista;

	string line;
	while(getline(input, line)) {
		int split = line.find(' ');
		int a = stoi(line);
		int b = stoi(line.substr(split));
		heap_1.push(a);
		heap_2.push(b);

		primera_lista.push_back(a);
		if (frecuencias.count(b) == 0) frecuencias.insert({b, 1});
		else frecuencias[b]++;
	}

	int res_a = 0;
	while (!heap_1.empty()) {
		res_a += abs(heap_1.top() - heap_2.top());
		heap_1.pop();
		heap_2.pop();
	}

	cout << "Parte a: " << res_a << endl;

	int res_b = 0;
	for (int a : primera_lista) res_b += a * frecuencias[a];

	cout << "Parte b: " << res_b << endl;
}

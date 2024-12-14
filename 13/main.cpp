#include <climits>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

long int minimos_tokens(pair<int, int> a, pair<int, int> b, pair<long int, long int> goal, long int max_tokens) {
	long int det = a.first * b.second - a.second * b.first;
	if (det == 0) return -1;
	long int tokens_a_por_det = b.second * goal.first - b.first * goal.second;
	long int tokens_b_por_det = -a.second * goal.first + a.first * goal.second;
	if (tokens_a_por_det % det != 0 || tokens_b_por_det % det != 0)
		return -1;

	long int tokens_a = tokens_a_por_det / det;
	long int tokens_b = tokens_b_por_det / det;

	if (tokens_a < 0 || tokens_b < 0) return -1;
	if (tokens_a > max_tokens || tokens_b > max_tokens) return -1;
	return (tokens_a*3)+tokens_b;
}

long int parte1(vector<pair<int, int>>& maquinas) {
	long int res = 0;
	for (int i = 0; i < maquinas.size(); i+=3) {
		long int minimos = minimos_tokens(maquinas[i], maquinas[i+1], maquinas[i+2], 100);
		if (minimos != -1) res += minimos;
	}
	return res;
}

long int parte2(vector<pair<int, int>>& maquinas) {
	long int res = 0;
	for (int i = 0; i < maquinas.size(); i+=3) {
		pair<long int, long int> goal(maquinas[i+2].first + 10000000000000, maquinas[i+2].second + 10000000000000);
		long int minimos = minimos_tokens(maquinas[i], maquinas[i+1], goal, LONG_LONG_MAX);
		if (minimos != -1) res += minimos;
	}
	return res;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	// Cada 3 es una máquina
	vector<pair<int, int>> maquinas;

	regex numero("\\d+");
	string line;
	while (getline(input, line)) {
		if (line == "") continue;

		sregex_token_iterator it(line.begin(), line.end(), numero);
		sregex_token_iterator end;
		int a = stoi(*it);
		int b = stoi(*(++it));
		maquinas.push_back(make_pair(a, b));
	}

	cout << "Parte 1: " << parte1(maquinas) << endl;
	cout << "Parte 2: " << parte2(maquinas) << endl;
}

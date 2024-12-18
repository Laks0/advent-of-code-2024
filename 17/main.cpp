#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

unsigned long int combo(unsigned long int operand, unsigned long int a, unsigned long int b, unsigned long int c) {
	if (operand == 4) return a;
	if (operand == 5) return b;
	if (operand == 6) return c;
	return operand;
}

vector<unsigned long int> output(unsigned long int a, unsigned long int b, unsigned long int c, vector<unsigned long int>& programa) {
	unsigned long int pc = 0;
	vector<unsigned long int> res;

	while (pc < programa.size()) {
		unsigned long int opcode = programa[pc];
		unsigned long int operand = programa[pc+1];

		switch (opcode) {
			case 0: // adv
				a >>= combo(operand, a, b, c);
				break;
			case 1: // bxl
				b ^= operand;
				break;
			case 2: // bst
				b = combo(operand, a, b, c) % 8;
				break;
			case 3: // jnz
				if (a != 0) pc = operand - 2;
				break;
			case 4: // bxc
				b ^= c;
				break;
			case 5: // out
				res.push_back(combo(operand, a, b, c) % 8);
				break;
			case 6: // bdv
				b = a >> combo(operand, a, b, c);
				break;
			case 7: // cdv
				c = a >> combo(operand, a, b, c);
				break;
		}
		pc += 2;
	}

	return res;
}

unsigned long int buscar_digito(vector<unsigned long int>& objetivo, unsigned long int digito, unsigned long int anterior, vector<unsigned long int>& programa) {
	if (digito == -1) return 0;
	for (unsigned long int i = 0; i < 8; i++) {
		unsigned long int a = (anterior << 3) + i;
		if (output(a, 0, 0, programa)[0] == objetivo[digito]) {
			unsigned long int rec = buscar_digito(objetivo, digito-1, a, programa);
			if (rec != -1) return (i << 3*(digito)) + rec;
		}
	}
	return -1;
}

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	ifstream input(filename);

	if (!input.is_open()) return 1;

	unsigned long int a; unsigned long int b; unsigned long int c; vector<unsigned long int> programa;

	unsigned long int i = 0;
	string line;
	while (getline(input, line)) {
		unsigned long int data = line.find(": ")+2;

		if (i == 0) a = stoi(line.substr(data));
		if (i == 1) b = stoi(line.substr(data));
		if (i == 2) c = stoi(line.substr(data));

		if (i == 4) {
			stringstream ss(line.substr(data));
			for (unsigned long int n; ss >> n;) {
				programa.push_back(n);
				if (ss.peek() == ',') ss.ignore();
			}
		}
		i++;
	}

	cout << "Parte 1: ";
	for (unsigned long int c : output(a, b, c, programa)) cout << c << ",";
	cout << endl;

	vector<unsigned long int> sin_salto(programa);
	sin_salto.pop_back();
	sin_salto.pop_back();

	cout << "Parte 2: " << buscar_digito(programa, programa.size()-1, 0, sin_salto) << endl;
}

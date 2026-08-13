#include <functional>
#include <iostream>
#include <numeric>
using namespace std;

#include "../lib/include/Game.h"

void should(string actual, string expected, string tag) {
	if (actual != expected)
		throw "[" + tag + "] Expected \n  " + expected + "\ngot\n  " + actual;
}

void should(int a, int e, string tag) {
	should(to_string(a), to_string(e), tag);
}

void test(string name, function<void()> func) {
	try {
		func();
		cout << ".";
	} catch (const string& e) {
		cout << endl << "X " << name << ": " << e << endl;
	}
}

string pm(vector<Move> moves) {
	return accumulate(
			moves.begin(), moves.end(), string(),
			[](const string& s, Move m) { return s + "," + Game::print(m); });
}
#include <functional>
#include <iostream>
#include <numeric>
using namespace std;

#include "../lib/include/Game.h"

bool asserted = false;

void should(string actual, string expected, string tag) {
	asserted = true;
	if (actual != expected)
		throw "[" + tag + "] Expected \n  " + expected + "\ngot\n  " + actual;
}

void should(int a, int e, string tag) {
	should(to_string(a), to_string(e), tag);
}

void test(string name, function<void()> func) {
	asserted = false;
	try {
		func();
		cout << (asserted ? "." : "?");
	} catch (const string& e) {
		cout << endl << "X " << name << ": " << e << endl;
	}
}

// string pm(vector<Move> moves) {
// 	return accumulate(
// 			moves.begin(), moves.end(), string(),
// 			[](const string& s, Move m) { return s + "," + Game::print(m); });
// }
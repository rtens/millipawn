#include <chrono>
#include <iostream>
#include <map>
using namespace std;

#include "../lib/include/Game.h"

// From https://chessprogramming.org/Perft_Results

map<vector<string>, vector<int>> tests = {
		{{"Initial position", Game::STARTPOS},
		 {20, 400, 8902, 197281, 4865609, 119060324}},
		{{"Position 2",
			"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "},
		 {48, 2039, 97862, 4085603, 193690690}},
		{{"Position 3", "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"},
		 {14, 191, 2812, 43238, 674624}},
		{{"Position 4",
			"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq -"},
		 {6, 264, 9467, 422333, 15833292}},
		{{"Position 5", "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ -"},
		 {44, 1486, 62379, 2103487, 89941194}},
};

int countPositions(Game g, int depth) {
	if (!depth) {
		return g.moves().size();
	}

	int sum = 0;
	for (Move m : g.moves()) {
		g.make(m);
		sum += countPositions(g, depth - 1);
		g.undo();
	}

	return sum;
}

int main() {
	for (auto test : tests) {
		cout << endl << test.first[0] << endl;
		Game g;
		g.start(test.first[1]);

		for (int i = 0; i < test.second.size(); i++) {
			auto expected = test.second[i];

			std::chrono::steady_clock::time_point begin =
					std::chrono::steady_clock::now();
			int positions = countPositions(g, i);
			std::chrono::steady_clock::time_point end =
					std::chrono::steady_clock::now();
			auto time =
					std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
							.count();

			if (expected == positions) {
				cout << "  " << (i + 1) << ": " << positions << " (" << time << " ms) "
						 << endl;

			} else {
				cout << "X " << (i + 1) << ": " << positions << " != " << expected
						 << endl;
				break;
			}
		}
	}
}

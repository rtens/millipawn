#include <functional>
#include <iostream>
using namespace std;

#include "../lib/include/Game.h"

void should(string actual, string expected, string tag = "Failed");

void should(int a, int e, string tag = "Failed");

void test(string name, function<void()> func);

string pm(vector<Move> moves);
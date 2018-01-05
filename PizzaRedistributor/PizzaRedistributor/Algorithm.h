#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Pizza.h"
using namespace std;

class Algorithm {

public:
	int pizzasNumber;
	vector<vector<Pizza>> tabooList;

	Algorithm(int pizza_cnt);
	vector<vector<Pizza>> GenerateNeighbourhood(vector<Pizza> current);
	vector<vector<Pizza>> GenerateTabooNeighbourhood(vector<Pizza> current);
	vector<Pizza> GenerateFirst();
	vector<Pizza> PickBest(vector<vector<Pizza>> neighbourhood);
	void UpdateTaboo();

};

#endif
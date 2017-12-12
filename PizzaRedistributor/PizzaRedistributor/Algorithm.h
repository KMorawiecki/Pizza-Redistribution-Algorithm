#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include <string>
#include <vector>
#include "Pizza.h"
using namespace std;

class Algorithm {

public:
	int pizzasNumber;

	Algorithm();
	vector<vector<Pizza>> tabooList;
	vector<vector<Pizza>> GenerateNeighbourhood(vector<Pizza> current);
	vector<vector<Pizza>> GenerateTabooNeighbourhood(vector<Pizza> current);
	vector<Pizza> GenerateFirst();
	vector<Pizza> PickBest();
	void UpgradeTaboo();

};

#endif
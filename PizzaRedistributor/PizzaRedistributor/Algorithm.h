#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include "Pizza.h"
using namespace std;

class Algorithm {

public:
	int pizzasNumber;
	vector<pair<int, pair<int, pair<ingredient, ingredient>>>> tabooList; // czas na liscie, numer pizzy, skladnik wymieniony, skladnik dodany

	Algorithm(int pizza_cnt);
	vector<vector<Pizza>> GenerateNeighbourhood(vector<Pizza> current, int param, bool notTaboo);
	vector<Pizza> GenerateFirst(vector<vector<ingredient>> wantedIng, vector<vector<ingredient>> bannedIng);
	vector<Pizza> PickBest(vector<vector<Pizza>> neighbourhood);
	void UpdateTaboo(vector<Pizza> first, vector<Pizza> second);
	void zapis(fstream & plik, float asp);
	float sum_asp(vector<Pizza> pizze);
};

#endif
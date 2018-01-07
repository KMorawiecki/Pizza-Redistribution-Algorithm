#include <iostream>
#include <string>
#include<vector>
#include <cstdlib>
#include <ctime>
#include "Pizza.h"
#include "Algorithm.h"
using namespace std;

int main()
{

	srand(time(NULL));
	int k;
	cout << "Podaj ilosc klientow" << endl;
	cin >> k;
	cout << "Podaj skladniki nieporzadane" << endl;
	cout << "Podaj skladniki porzadane" << endl;
	//TODO: zrobic wektor porzadanych i nieporzadanych
	int minPizz = k;
	int maxPizz = k + floor(k / 2);
	int iterMax = 200;
	
	Algorithm alg(minPizz);
	vector<Pizza> first;
	for (int i = 0; i < minPizz; i++)
	{
		vector<ingredient> ing;
		vector<ingredient> pusty;
		ing.push_back(ser);
		ing.push_back(pieczarki);
		ing.push_back(szynka);
		ing.push_back(ananas);
		Pizza pizza(1, ing, pusty, pusty);
		first.push_back(pizza);
	}
	//vector<Pizza> first = alg.GenerateFirst();
	for (int i = 0; i < first.size(); i++)
		cout << first[i];
	vector<vector<Pizza>> nei = alg.GenerateNeighbourhood(first, true);
	for (int i = 0; i < nei.size(); i++)
	{
		cout << endl << endl;
		for (int j = 0; j < nei[i].size(); j++)
			cout << nei[i][j] << endl;
	}
	//UWAGA! na ten moment w s¹siedztwie "nei" nie ma elementu "first" tak¿e on nie zostanie wybrany na pewno
	vector<Pizza> opt = alg.PickBest(nei);
	cout << endl << "A przed Panstwem NAJoptymalniejszy zestaw swiata" << endl;
	for (int l = 0; l < opt.size(); l++)
		cout << opt[l];

	/*for (int i = minPizz; i < maxPizz; i++)
	{
		int iter = 0;
		Algorithm alg(i);
		vector<Pizza> s0;
		for (int j = 0; j < i; j++)
		{
			vector<ingredient> ing;
			vector<ingredient> pusty;
			ing.push_back(ser);
			ing.push_back(pieczarki);
			ing.push_back(szynka);
			ing.push_back(ananas);
			Pizza pizza(1, ing, pusty, pusty);
			s0.push_back(pizza);
		}
		//vector<Pizza> s0 = alg.GenerateFirst();
		vector<Pizza> best = s0;
		int bestAsp = 0;
		//TODO: przypisac wlasciwy bestAsp
		vector<Pizza> tabu;
		while (iter < iterMax)
		{
			vector<Pizza> bestCandidate;
			vector<vector<Pizza>> neighbourhood = alg.GenerateNeighbourhood(s0, true);
			int lowestAsp = 1000;
			for (int j = 0; j < neighbourhood.size(); j++)
			{
				int asp = 0;
				for (int k = 0; k < neighbourhood[j].size(); k++)
					asp += neighbourhood[j][k].Aspiration();
				if (asp < lowestAsp)
				{
					lowestAsp = asp;
					bestCandidate = neighbourhood[j];
				}
			}

			vector<Pizza> bestTabooCandidate;
			vector<vector<Pizza>> tabooNeighbourhood = alg.GenerateNeighbourhood(s0, false);
			int lowestTabooAsp = 1000;
			for (int j = 0; j < tabooNeighbourhood.size(); j++)
			{
				int asp = 0;
				for (int k = 0; k < tabooNeighbourhood[j].size(); k++)
					asp += tabooNeighbourhood[j][k].Aspiration();
				if (asp < lowestAsp)
				{
					lowestTabooAsp = asp;
					bestTabooCandidate = tabooNeighbourhood[j];
				}
			}

			if (lowestAsp < lowestTabooAsp)
			{
				s0 = bestCandidate;
				if (lowestAsp < bestAsp)
					best = bestCandidate;
			}
			else
			{
				if (lowestTabooAsp < bestAsp) {
					best = bestTabooCandidate;
					s0 = bestTabooCandidate;
				}
				else
					s0 = bestCandidate;
			}
			alg.UpdateTaboo();
			i++;
		}
	}*/
	system("PAUSE");
}


#include <iostream>
#include <string>
#include<vector>
#include <cstdlib>
#include <ctime>
#include "Pizza.h"
#include "Algorithm.h"
#include "mapmaker.h"
using namespace std;

int main()
{
	static const string keys[] = {"ser","pieczarki","szynka","rukola","ananas","sos","boczek","salami","kurczak","cebula","papryka"};
	static const ingredient values[] = {ser,pieczarki,szynka,rukola,ananas,sos,boczek,salami,kurczak,cebula,papryka};
	static map<string, ingredient> table(make_map(keys, values));

	srand(time(NULL));
	int k;
	vector<vector<ingredient>> wanted;		//wektor porzadanych dla poszczegolnych klientow
	vector<vector<ingredient>> unwanted;
	string ingr;

	cout << "Podaj ilosc klientow:" << endl;
	cin >> k;
	int client = 1;

	while (client < k + 1)
	{
		vector<ingredient> tempWanted;
		vector<ingredient> tempUnwanted;
		cout << "Podaj skladniki nieporzadane dla " << client << " klienta: (q = wyjscie)" << endl;
		cin >> ingr;
		while (ingr != "q")
		{
			tempUnwanted.push_back(table.find(ingr)->second);
			cin >> ingr;
		}

		cout << "Podaj skladniki porzadane dla " << client << " klienta: (q = wyjscie)" << endl;
		cin >> ingr;
		while (ingr != "q")
		{
			tempWanted.push_back(table.find(ingr)->second);
			cin >> ingr;
		}
		wanted.push_back(tempWanted);
		unwanted.push_back(tempUnwanted);
		client++;
	}
	cout << endl;

	int minPizz = k;
	int maxPizz = k + floor(k / 2);
	int iterMax = 200;
	int i = minPizz;

	//for (int i = minPizz; i < maxPizz; i++)
	//{
		int iter = 0;
		Algorithm alg(i);
		vector<Pizza> s0 = alg.GenerateFirst(wanted[0], unwanted[0]); //TODO: jakos rozroznic pizze dla poszczegolnych klientow
		vector<Pizza> best = s0;
		int bestAsp = 0;
		//TODO: przypisac wlasciwy bestAsp

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
				
				alg.UpdateTaboo(s0, bestCandidate);
				s0 = bestCandidate;		
				if (lowestAsp < bestAsp)
					best = bestCandidate;

			}
			else
			{
				if (lowestTabooAsp < bestAsp) {
					alg.UpdateTaboo(s0, bestTabooCandidate);
					best = bestTabooCandidate;
					s0 = bestTabooCandidate;
				}
				else
				{
					alg.UpdateTaboo(s0, bestCandidate);
					s0 = bestCandidate;
				}
			}
			iter++;
		}
		for(int p = 0; p < best.size(); p++)
			cout << "Ilosc pizz: " << i << " " << best[p];
	//}
	system("PAUSE");
}


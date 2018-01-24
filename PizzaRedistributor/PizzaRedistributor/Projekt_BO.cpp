#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Pizza.h"
#include "Algorithm.h"
#include "mapmaker.h"
using namespace std;

static const string keys[] = { "ser","pieczarki","szynka","rukola","ananas","sos","boczek","salami","kurczak","cebula","papryka" };
static const ingredient values[] = { ser,pieczarki,szynka,rukola,ananas,sos,boczek,salami,kurczak,cebula,papryka };
static map<string, ingredient> table(make_map(keys, values));

int main()
{
	int searchParameter = 3;

	srand(time(NULL));
	int minPizz;
	vector<vector<ingredient>> wanted;		//wektor porzadanych dla poszczegolnych klientow
	vector<vector<ingredient>> unwanted;
	string ingr;

	fstream outplik;
	outplik.open("pliczek.txt", ios::in | ios::out);
	cout << "Podaj ilosc klientow:" << endl;
	cin >> minPizz;
	int client = 1;
	while (client < minPizz + 1)
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
	
	/*
	minPizz = 1;
	vector<ingredient> unwan = { rukola, ananas };
	unwanted.push_back(unwan);
	vector<ingredient> wan = { boczek, cebula, szynka };
	wanted.push_back(wan);
	*/

	int iterMax = 200;
	int iter = 0;
	Algorithm alg(minPizz);
	vector<Pizza> s0 = alg.GenerateFirst(wanted, unwanted);
	vector<Pizza> best = s0;
	float bestAsp = 1000;
	int i = minPizz;

	while (iter < iterMax)
	{
		vector<Pizza> bestCandidate;
		vector<vector<Pizza>> neighbourhood = alg.GenerateNeighbourhood(s0, true);
		float lowestAsp = 1000;
		for (int j = 0; j < neighbourhood.size(); j++)
		{
			float asp = 0;
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
		float lowestTabooAsp = 1000;
		for (int j = 0; j < tabooNeighbourhood.size(); j++)
		{
			float asp = 0;
			for (int k = 0; k < tabooNeighbourhood[j].size(); k++)
				asp = asp + tabooNeighbourhood[j][k].Aspiration();

			if (asp < lowestTabooAsp)
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
			{
				best = bestCandidate;
				bestAsp = lowestAsp;
			}
		}
		else
		{
			if (lowestTabooAsp < bestAsp) 
			{
				alg.UpdateTaboo(s0, bestTabooCandidate);
				best = bestTabooCandidate;
				s0 = bestTabooCandidate;
				bestAsp = lowestTabooAsp;
			}
			else
			{
				alg.UpdateTaboo(s0, bestCandidate);
				s0 = bestCandidate;
			}
		}
		iter++;
		alg.zapis(outplik, s0[0].Aspiration());
	}
	for(int p = 0; p < best.size(); p++)
		cout << best[p];
	system("PAUSE");
}


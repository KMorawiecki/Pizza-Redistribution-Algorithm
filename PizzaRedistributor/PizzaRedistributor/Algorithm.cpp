#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include "Pizza.h"
#include "Algorithm.h"
using namespace std;

Algorithm::Algorithm(int pc) : pizzasNumber(pc)
{
	vector<pair<int, pair<int, pair<ingredient, ingredient>>>> tList;
	tabooList = tList;
}

vector<vector<Pizza>> Algorithm::GenerateNeighbourhood(vector<Pizza> cur, int sparam, bool notTaboo)
{
	vector<vector<Pizza>> nei;
	int parameter = 0;
	bool badIng = false;
	bool notTabooTemp;

	for (int i = 0; i < cur.size(); i++)
	{
		for (int k = 1; k < INGSIZE; k++)
		{
			notTabooTemp = notTaboo;
			ingredient newing = ingredient(k);
			for (int j = 0; j < cur[i].ing.size(); j++)
				if (cur[i].ing[j] == newing)
					badIng = true;
			if (badIng == false)
				for(int j = 0; j < cur[i].ing.size(); j++)
				{
					for (int t = 0; t < tabooList.size(); t++)
						if (tabooList[t].second.first == i)
							if (tabooList[t].second.second.first == cur[i].ing[j])
								if (tabooList[t].second.second.second == newing)
									notTabooTemp = !notTabooTemp;
					if (notTabooTemp == true)
					{
						vector<Pizza> element = cur;
						element[i].ing.erase(element[i].ing.begin() + j);
						element[i].ing.push_back(newing);
						element[i].price = element[i].countPrice();
						element[i].kcal = element[i].countCalories();
						if (element[i].CheckForCalories())
						{
							parameter++;
							if (parameter == sparam)
							{
								nei.push_back(element);
								parameter = 0;
							}
						}
					}
				}
			else
				badIng = false;
		}
		if (cur[i].ing.size() != 3)
			for (int k = 0; k < cur[i].ing.size(); k++)
			{
				notTabooTemp = notTaboo;
				for (int t = 0; t < tabooList.size(); t++)
					if (tabooList[t].second.first == i)
						if (tabooList[t].second.second.first == cur[i].ing[k])
							if (tabooList[t].second.second.second == nic)
								notTabooTemp = !notTabooTemp;
				if (notTabooTemp == true)
				{
					vector<Pizza> element = cur;
					element[i].ing.erase(element[i].ing.begin() + k);
					element[i].price = element[i].countPrice();
					element[i].kcal = element[i].countCalories();
					if (element[i].CheckForCalories())
					{
						parameter++;
						if (parameter == sparam)
						{
							nei.push_back(element);
							parameter = 0;
						}
					}
				}
			}
		if (cur[i].ing.size() != 7)
			for (int k = 1; k < INGSIZE; k++)
			{
				notTabooTemp = notTaboo;
				ingredient newing = ingredient(k);
				for (int j = 0; j < cur[i].ing.size(); j++)
					if (cur[i].ing[j] == newing)
						badIng = true;
				if (badIng == false)
				{
					for (int t = 0; t < tabooList.size(); t++)
						if (tabooList[t].second.first == i)
							if (tabooList[t].second.second.first == nic)
								if (tabooList[t].second.second.second == newing)
									notTabooTemp = !notTabooTemp;
					if (notTaboo == true)
					{
						vector<Pizza> element = cur;
						element[i].ing.push_back(newing);
						element[i].price = element[i].countPrice();
						element[i].kcal = element[i].countCalories();
						if (element[i].CheckForCalories())
						{
							parameter++;
							if (parameter == sparam)
							{
								nei.push_back(element);
								parameter = 0;
							}
						}
					}
				}
				else
					badIng = false;
			}
	}
	return nei;
}

vector<Pizza> Algorithm :: GenerateFirst(vector<vector<ingredient>> wantedIng, vector<vector<ingredient>> bannedIng)
{
	vector<Pizza> ret;
	for (int i = 0; i < this->pizzasNumber; i++)
	{
		int ingNumber = (rand() % 5) + 3;    //losujemy liczbe skladnikow z przedzial 3 do 7
		vector<ingredient> vectorING;
		vector<int> used;
		bool usedB = false;
		used.push_back(0);
			do
			{
				usedB = false;
				int whichING = (rand() % 17) + 1;
				for (int k = 0; k < used.size(); k++)
				{
					if (whichING == used[k])
					{
						usedB = true;
					}
				}
				if (usedB == false)
				{
					vectorING.push_back(ingredient(whichING));
					used.push_back(ingredient(whichING));
				}
			}
			while (vectorING.size()<ingNumber);
			
		Pizza current(1, vectorING, bannedIng[i], wantedIng[i]);
		ret.push_back(current);
	}
	return ret;
}

vector<Pizza> Algorithm::PickBest(vector<vector<Pizza>> neighbourhood)
{
	vector<Pizza> ret = neighbourhood[0];
	vector<float> suma;
	float suma_akt;
	suma.push_back(0);
	for (int k = 0; k < neighbourhood[0].size(); k++) //obliczenie dla pierwszego elementu
	{
		suma[0] +=neighbourhood[0][k].Aspiration();
	}
	suma_akt = suma[0];
    for (int i = 1; i < neighbourhood.size(); i++) 
	{
		suma.push_back(0);							//dodanie kolejnego elementu w wektorze sum aspiracji
		for (int j = 0; j < neighbourhood[i].size(); j++)
		{
			suma[i] +=neighbourhood[i][j].Aspiration();  
		}
		if (suma[i] < suma_akt)
		{
			ret = neighbourhood[i];
			suma_akt = suma[i];
		}
	}
	return ret; 
}

void Algorithm::UpdateTaboo(vector<Pizza> first, vector<Pizza> second)
{
	vector<pair<int, pair<int, pair<ingredient, ingredient>>>>::iterator iter = tabooList.begin();
	while(iter != tabooList.end())
	{
		iter->first -= 1;
		if (iter->first == 0)
			iter = tabooList.erase(iter);
		else
			iter++;
	}

	for (int i = 0; i < first.size(); i++)
	{
		vector<ingredient> fing = first[i].ing;
		vector<ingredient> sing = second[i].ing;
		int findex;
		int sindex;
		bool repeatingIng;
		bool similarity = true;

		if(fing.size() >= sing.size())
			for(int f = 0; f < fing.size(); f++)
			{
				repeatingIng = false;
				for (int s = 0; s < sing.size(); s++)
					if (fing[f] == sing[s])
						repeatingIng = true;
				if (repeatingIng == false)
				{
					findex = f;
					similarity = false;
					break;
				}
				else
					repeatingIng = true;
			}

		if (fing.size() <= sing.size())
			for (int s = 0; s < sing.size(); s++)
			{
				repeatingIng = false;
				for (int f = 0; f < fing.size(); f++)
					if (fing[f] == sing[s])
						repeatingIng = true;
				if (repeatingIng == false)
				{
					sindex = s;
					similarity = false;
					break;
				}
				else
					repeatingIng = true;
			}

		if (!similarity)
		{
			if (fing.size() < sing.size())
				tabooList.push_back(make_pair(60, make_pair(i, make_pair(nic, sing[sindex]))));
			else if (fing.size() > sing.size())
				tabooList.push_back(make_pair(60, make_pair(i, make_pair(fing[findex], nic))));
			else
				tabooList.push_back(make_pair(60, make_pair(i, make_pair(fing[findex], sing[sindex]))));
		}
	}			
}

void Algorithm::zapis(fstream &plik, float asp)
{
	if (plik.good() == true)
	{
		plik << asp <<endl;
	}
	else cout << "Problem z otworzeniem pliku do zapisu" << endl;

}

float Algorithm::sum_asp(vector<Pizza> pizze)
{
	float suma = 0.0;
	for (int i = 0; i < pizze.size(); i++)
	{
		suma += pizze[i].Aspiration();
	}
	return suma;
}

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "Pizza.h"
#include "Algorithm.h"
using namespace std;

Algorithm::Algorithm(int pc) : pizzasNumber(pc)
{

}

vector<vector<Pizza>> Algorithm::GenerateNeighbourhood(vector<Pizza> cur)
{
	vector<vector<Pizza>> nei;
	bool badIng = false;

	for (int i = 0; i < cur.size(); i++)
	{
		for (int k = 0; k < INGSIZE; k++)
		{
			ingredient newing = ingredient(k);
			for (int j = 0; j < cur[i].ing.size(); j++)
				if (cur[i].ing[j] == newing)
					badIng = true;
			if (badIng == false)
				for(int j = 0; j < cur[i].ing.size(); j++)
				{
					vector<Pizza> element = cur;
					element[i].ing.erase(element[i].ing.begin() + j);
					element[i].ing.push_back(newing);
					nei.push_back(element);
				}
			else
				badIng = false;
		}
		if (cur[i].ing.size() != 3)
			for (int k = 0; k < cur[i].ing.size(); k++)
			{
				vector<Pizza> element = cur;
				element[i].ing.erase(element[i].ing.begin() + k);
				nei.push_back(element);
			}
		if (cur[i].ing.size() != 7)
			for (int k = 0; k < INGSIZE; k++)
			{
				ingredient newing = ingredient(k);
				for (int j = 0; j < cur[i].ing.size(); j++)
					if (cur[i].ing[j] == newing)
						badIng = true;
				if (badIng == false)
				{
					vector<Pizza> element = cur;
					element[i].ing.push_back(newing);
					nei.push_back(element);
				}
				else
					badIng = false;
			}
	}

	return nei;
}

vector<Pizza> Algorithm :: GenerateFirst()
{
	vector<Pizza> ret;
	bool usedB = false;
	for (int i = 0; i < this->pizzasNumber; i++)
	{
		int ingNumber = (rand() % 5) + 3;    //losujemy liczbe skladnikow z przedzial 3 do 7
		vector<ingredient> vectorING;
		vector<int> used;
		for (int j = 0; j < ingNumber; j++)
		{
			int whichING = (rand() % 11);
			for (int k = 0; k <= used.size(); k++)
			{
				if (whichING == used[k])
				{
					usedB = true;
				}
			}

			if (usedB == true) 
			{
				usedB = false;
				j--;
			}
			else
			{
				vectorING.push_back(ingredient(whichING));
				used.push_back(whichING);
			}
		}
		vector<ingredient> emptyvec;
		Pizza current(1, vectorING, emptyvec, emptyvec);
		ret.push_back(current);
	}
	return ret;
}

vector<Pizza> Algorithm::PickBest(vector<vector<Pizza>> neighbourhood)
{
	vector<Pizza> ret = neighbourhood[0];
	vector<float> suma;
	suma.push_back(0);
	for (int k = 0; k < neighbourhood[0].size(); k++) //obliczenie dla pierwszego elementu
	{
		suma[0] +=neighbourhood[0][k].Aspiration();
	}

    for (int i = 1; i < neighbourhood.size(); i++) 
	{
		suma.push_back(0);							//dodanie kolejnego elementu w wektorze sum aspiracji
		for (int j = 0; j < neighbourhood[i].size(); j++)
		{
			suma[i] +=neighbourhood[i][j].Aspiration();  
		}
		//cout << "Aspiracja zestawu:" << suma[i] << endl;
		if (suma[i] > suma[i - 1])
			ret = neighbourhood[i];
	}
	return ret; 
}
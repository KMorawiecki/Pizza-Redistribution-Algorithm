#include <iostream>
#include <string>
#include <vector>
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
					element[i].ing.erase(element[i].ing.begin() + j - 1);
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
				element[i].ing.erase(element[i].ing.begin() + k - 1);
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

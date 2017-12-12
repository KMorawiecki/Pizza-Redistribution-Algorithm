#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "Pizza.h"
#include "Algorithm.h"
using namespace std;

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


	}
}


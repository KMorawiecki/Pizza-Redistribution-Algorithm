#ifndef Pizza_h
#define Pizza_h

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum ingredient
{
	ser, 
	pieczarki, 
	szynka
};

class Pizza
{
public:
	int size;
	int kcal;
	float price;
	vector<ingredient> ing;
	vector<ingredient> bannedIng;
	vector<ingredient> wantedIng;

	Pizza(int s, vector<ingredient> i, vector<ingredient> b, vector<ingredient> w);
	int countCalories();
	int countPrice();
	int IngValue();
	float Aspiration();
};

#endif
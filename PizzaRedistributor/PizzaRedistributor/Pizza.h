#ifndef Pizza_h
#define Pizza_h

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

enum ingredient
{
	nic,
	ser,
	pieczarki,
	szynka,
	rukola,
	ananas,
	sos,
	boczek,
	salami,
	kurczak,
	cebula,
	papryka,
	INGSIZE = 12
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

	Pizza(int s, vector<ingredient> i, vector<ingredient> b, vector<ingredient> w); //s = size
	int countCalories();
	int countPrice();
	int IngValue();
	float Aspiration();
	friend ostream& operator<< (ostream& stream, const Pizza& pizza);
};

#endif
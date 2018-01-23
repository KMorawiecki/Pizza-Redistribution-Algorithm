#include <iostream>
#include <cstdlib>
#include <ctime>
#include<map>
#include "mapmaker.h"
#include "Pizza.h"
using namespace std;

static const string keys[] = { "ser","pieczarki","szynka","rukola","ananas","sos","boczek","salami","kurczak","cebula","papryka" };
static const ingredient values[] = { ser,pieczarki,szynka,rukola,ananas,sos,boczek,salami,kurczak,cebula,papryka };
static map<string, ingredient> table(make_map(keys, values));

Pizza::Pizza(int s, vector<ingredient> i, vector<ingredient> b, vector<ingredient> w) : size(s), ing(i), bannedIng(b), wantedIng(w)
{
	this->kcal = countCalories();
	this->price = countPrice();
}

int Pizza::IngValue()
{
	int value = 0;
	int punish = 5;
	int reward = 3;

	for (int i = 0; i < this->ing.size(); i++)
	{
		for (int j = 0; j < this->bannedIng.size(); j++)
		{
			if (ing[i] == bannedIng[j])
			{
				value += punish;
				break;
			}
		}
		for (int k = 0; k < this->wantedIng.size(); k++)
		{
			if (ing[i] == wantedIng[k])
			{
				value -= reward;
				break;
			}
		}
	}
	return value;
}


float Pizza::Aspiration()
{
	float mod = 0.5;
	float value = mod * (this->price) + this->IngValue();
	return value;
}

int Pizza::countCalories()
{
	int cal = 0;
	for (int i = 0; i < this->ing.size(); i++)
	{
		switch (ing[i])
		{
			case ser:
				cal += 10;
				break;
			case pieczarki:
				cal += 8;
				break;
			case szynka:
				cal += 8;
				break;
			case rukola:
				cal += 6;
				break;
			case ananas:
				cal += 7;
				break;
			case sos:
				cal += 10;
				break;
			case boczek:
				cal += 10;
				break;
			case salami:
				cal += 10;
				break;
			case kurczak:
				cal += 10;
				break;
			case cebula:
				cal += 8;
				break; 
			case papryka:
					cal += 8;
					break;
			default:
				break;
		}
	}

	return cal;
}

int Pizza::countPrice()
{
	int p = 0;
	for (int i = 0; i < this->ing.size(); i++)
	{
		switch (ing[i])
		{
		case ser:
			p += 10;
			break;
		case pieczarki:
			p += 6;
			break;
		case szynka:
			p += 8;
			break;
		case rukola:
			p += 7;
			break;
		case ananas:
			p += 5;
			break; 
		case sos:
			p += 3;
			break;
		case boczek:
			p += 9;
			break;
		case salami:
			p += 8;
			break;
		case kurczak:
			p += 10;
			break;
		case cebula:
			p += 4;
			break;
		case papryka:
			p += 4;
			break;
		default:
			break;
		}
	}
	p *= size;

	return p;
}

ostream& operator << (ostream& stream, const Pizza& pizza)
{
	Pizza secpiz = pizza;
	map<string, ingredient>::iterator iter = table.begin();
	stream << endl << "Skladniki:" << endl;
	for (int i = 0; i < pizza.ing.size(); i++)
		for (iter; iter != table.end(); ++iter)
			if (iter->second == pizza.ing[i])
			{
				stream << iter->first << ", ";
				iter = table.begin();
				break;
			}
	stream << "Aspiration: " << secpiz.Aspiration() << " Price: " << secpiz.price;
	return stream;
}
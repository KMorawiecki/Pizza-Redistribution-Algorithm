#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
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
	int value = 1;
	int punish = 5;
	int reward = 3;

	for (int i = 0; i < this->ing.size(); i++)
	{
		for (int j = 0; j < this->bannedIng.size(); j++)
		{
			if (this->ing[i] == bannedIng[j])
			{
				value += punish;
				break;
			}
		}
		for (int k = 0; k < this->wantedIng.size(); k++)
		{
			if (this->ing[i] == wantedIng[k])
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
	float mod = 0.7;
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
				cal += 100;
				break;
			case pieczarki:
				cal += 80;
				break;
			case szynka:
				cal += 300;
				break;
			case rukola:
				cal += 60;
				break;
			case ananas:
				cal += 75;
				break;
			case sos:
				cal += 30;
				break;
			case boczek:
				cal += 400;
				break;
			case salami:
				cal += 350;
				break;
			case kurczak:
				cal += 300;
				break;
			case cebula:
				cal += 100;
				break; 
			case papryka:
				cal += 90;
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
			p += 12;
			break;
		case pieczarki:
			p += 6;
			break;
		case szynka:
			p += 15;
			break;
		case rukola:
			p += 7;
			break;
		case ananas:
			p += 10;
			break; 
		case sos:
			p += 5;
			break;
		case boczek:
			p += 17;
			break;
		case salami:
			p += 11;
			break;
		case kurczak:
			p += 16;
			break;
		case cebula:
			p += 8;
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

bool Pizza::CheckForCalories()
{
	if (kcal < 1000)
		return false;
	return true;
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
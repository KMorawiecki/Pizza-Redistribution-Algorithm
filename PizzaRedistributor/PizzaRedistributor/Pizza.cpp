#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include "mapmaker.h"
#include "Pizza.h"
using namespace std;

static const string keys[] = { "ser","pieczarki","szynka","rukola","ananas","sos","boczek","salami","kurczak","cebula","papryka","tunczyk","pomidor","feta","szpinak","kielbasa" };
static const ingredient values[] = { ser,pieczarki,szynka,rukola,ananas,sos,boczek,salami,kurczak,cebula,papryka,tunczyk,pomidor,feta,szpinak,kielbasa};
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
				cal += 400;
				break;
			case pieczarki:
				cal += 130;
				break;
			case szynka:
				cal += 300;
				break;
			case rukola:
				cal += 80;
				break;
			case ananas:
				cal += 105;
				break;
			case sos:
				cal += 330;
				break;
			case boczek:
				cal += 500;
				break;
			case salami:
				cal += 350;
				break;
			case kurczak:
				cal += 300;
				break;
			case cebula:
				cal += 150;
				break; 
			case papryka:
				cal += 180;
				break;
			case tunczyk:
				cal += 250;
				break;
			case pomidor:
				cal += 170;
				break;
			case feta:
				cal += 230;
				break;
			case szpinak:
				cal += 130;
				break;
			case kielbasa:
				cal += 380;
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
			p += 16;
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
			p += 16;
			break;
		case kurczak:
			p += 16;
			break;
		case cebula:
			p += 8;
			break;
		case papryka:
			p += 7;
			break;
		case tunczyk:
			p += 17;
			break;
		case feta:
			p += 11;
			break;
		case pomidor:
			p += 6;
			break;
		case kielbasa:
			p += 8;
			break;
		case szpinak:
			p += 8;
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
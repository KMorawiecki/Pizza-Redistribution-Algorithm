#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Pizza.h"
using namespace std;

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
	float value = mod*(this->price) + this->IngValue();
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
				cal += 5;
				break;
			case szynka:
				cal += 12;
				break;
			case rukola:
				cal += 12;
				break;
			case ananas:
				cal += 12;
				break;
			case sos:
				cal += 12;
				break;
			case boczek:
				cal += 12;
				break;
			case salami:
				cal += 12;
				break;
			case kurczak:
				cal += 12;
				break;
			case cebula:
				cal += 12;
				break; 
			case papryka:
					cal += 12;
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
			p += 13;
			break;
		case pieczarki:
			p += 10;
			break;
		case szynka:
			p += 8;
			break;
		case rukola:
			p += 8;
			break;
		case ananas:
			p += 8;
			break; 
		case sos:
			p += 8;
			break;
		case boczek:
			p += 8;
			break;
		case salami:
			p += 8;
			break;
		case kurczak:
			p += 8;
			break;
		case cebula:
			p += 8;
			break;
		case papryka:
			p += 8;
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
	stream << endl << "Skladniki:" << endl;
	for (int i = 0; i < pizza.ing.size(); i++)
		stream << pizza.ing[i] << ", ";
	return stream;
}
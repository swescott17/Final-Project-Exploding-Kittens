#include "card.h"
using namespace std;

card::card(string m)
{
	type = m;
}

string card::getType()
{
	return type;
}
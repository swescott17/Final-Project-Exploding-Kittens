#ifndef _card_h_
#define _card_h_

#include <iostream>
#include <string>
using namespace std;

class card
{
private:
	string type;
public:
	card(string type); //constructor
	string getType(); //getter

};

#endif
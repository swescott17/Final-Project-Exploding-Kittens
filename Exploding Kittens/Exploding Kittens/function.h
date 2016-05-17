#ifndef _H_FUNCTIONS_
#define _H_FUNCTIONS_

#include "card.h"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
void shuffleDeck(vector<T>& pile) //seperate function to shuffle the deck
{
	int numbercard = pile.size(); //gets the size of the pile at this point
	srand(time(NULL));  //starts a random number generator based on time
	for (int i = 0; i < numbercard; i++) //shuffles the cards by using the vector function swap
	{
		int n = i + rand() % (numbercard - i);
		swap(pile[i], pile[n]);
	}
}

template<typename T, typename K>
int linearSearch(vector<T> list, K key, int choice, int arraySize) //enter an array of any type and an "item" of the same type to search in the array
{
	for (int i = 0; i < arraySize; i++)
	{

		if (key == list[i].getTpye() && i = !choice)
		{
			return i; //returns which number in the array the item was found
		}
	}
	return -1; //returns that nothing was found
}



#endif 
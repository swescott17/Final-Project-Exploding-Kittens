#ifndef PLAYER_H_
#define PLAYER_H_

#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include "card.h"
using std::string;
using std::vector;

class Player
{
private:
	int numberOfCards; //number of cards that a player has
	string name; //name of player
	vector<card> hand; //pointer to array of cards currently held by player
	bool dead;
public:
	Player(); //default constructor
	Player(string name, vector<card> & pile); //constructor
	card getCard(int x); //get a card from a player's hand, delete from player's hand
	void endTurn(bool & attack, bool & skip, vector<card> & pile, bool playedSkip, bool playedAttack, int & livingPlayers); //draw from pile, draw 2 if attacked
	void showHand(); //display cards in hand of player
	void lookUp(int num); //looks up a card in the players hand
	void attack(bool & attack); //force another player to take 2 turns
	void skip(bool & skip); //don't take a turn at all
	card favor(Player& p); //force another player to give you a card
	void shuffle(vector<card> pile); //mix up the cards in the draw pile
	void seeFuture(vector<card> pile); //look 3 cards into the draw pile
	card pair(Player p); //take a random card from anoter player
	void nope(int & nope, Player*, int numPlayers); //stops another player's action
	string getName() { return name; }; //return name of player
	bool getDead(); //returns if the player is dead
	int linearSearchPair(string key, int choice); //searches a player's hand for a pair
	void addHand(card& f); //adds a card to a player's hand, for use in pair protocol
	void removeHand(int s); //removes an extra card in the case of pair
};

#endif

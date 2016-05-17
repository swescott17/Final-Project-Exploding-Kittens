#include "player.h"
#include "card.h"
#include "function.h"

Player::Player() //default constructor for the player class
{
	name = "playername"; //intialize hands, intialize number of cards to 5 (1 defuse and 4 ordinary cards)
	numberOfCards = 5;
	hand.push_back(card("Defuse"));
	dead = false;
}

Player::Player(string playername, vector<card> & pile) //constructor for the player class
{
	name = playername; //intialize hands, intialize number of cards to 5 (1 defuse and 4 ordinary cards)
	numberOfCards = 5;
	hand.push_back(card("Defuse"));
	for (int i = 1; i < numberOfCards; i++)
	{
		hand.push_back(pile.back()); //draws 4 more cards into player's hand
		pile.pop_back(); //erases the cards that were drawn from the pile
	}
	dead = false;
}

card Player::getCard(int x) //gets a card from a player's hand, delete from player's hand
{
	card returnCard = hand[x]; //card to be returned
	hand.erase(hand.begin() + x); //delete played card from player's hand
	return returnCard;
}

void Player::endTurn(bool & attack, bool & skip, vector<card> & pile, bool playedSkip, bool playedAttack, int & livingPlayers)
{
	srand(time(NULL));  //starts a random number generator based on time
	int turns; //# of times player must draw, determined by attack
	if (attack == true && playedAttack == false) //declares integer used to force player to take correct number of turns
	{
		turns = 2;
		attack = false; //reset main attack flag
	}
	else if (skip == true && playedSkip == false) //declares integer used to force player to take correct number of turns
		turns = 0;
	else
		turns = 1;

	while (turns != 0)
	{
		hand.push_back(pile.back()); //ADD TOP CARD FROM DECK
		card drawnCard = pile.back();
		pile.pop_back(); //delete card from top of deck
		cout << endl << "You drew: " << drawnCard.getType() << endl; //output card drawn by player
		if (hand.back().getType() == "Exploding Kitten") //check if player drew an exploding kitten
		{
			hand.pop_back(); //remove the exploding kitten from the player's hand, as you're not supposed to hold exploding kittens
			bool hasDefuse = false; //declare flag for whether or not player has defuse card for kitten
			int defuseLocation; //stores location of nope card in player's hand
			for (int p = 0; p < hand.size(); p++)
			{
				if (hand[p].getType() == "Defuse")
				{
					hasDefuse = true; //set flag to true if player has nope card
					defuseLocation = p;
				}
			}
			if (hasDefuse == true)
			{
				hand.erase(hand.begin() + defuseLocation); //delete defuse card
				cout << "\nExploding Kitten successfully defused, you live... for now.\n";
				pile.insert(pile.begin() + (rand() % pile.size()), card("Exploding Kitten"));
			}

			else
			{
				dead = true; //kills the player if they don't have a defuse
				livingPlayers--; //decrement number of players still in game
				cout << "\nBOOOOOOOOM. You have no defuse card, so the Exploding Kitten killed you.\nYou're out of the game.\n";
			}
		}
		turns--; //ends loop if player has taken appropriate number of turns
	}

}


void Player::attack(bool & attack) //force the next player to take 2 cards instead of 1
{
	attack = true;
}

void Player::shuffle(vector<card> pile) //shuffles the vector called pile (the deck)
{
	int numbercard = pile.size(); //gets the size of the pile at this point
	srand(time(NULL));  //starts a random number generator based on time
	for (int i = 0; i < numbercard; i++) //shuffles the cards by using the vector function swap
	{
		int n = i + rand() % (numbercard - i);
		swap(pile[i], pile[n]);
	}
}

void Player::lookUp(int num) //looks up a card in the players hand
{
	string name = hand[num].getType(); //gets the card type to compare to


	if (name == "Attack")
	{
		cout << "When played, the player to your left will take two turns instead of one. This will force them to draw two cards instead of one." << endl;

	}
	if (name == "See the Future")
	{
		cout << "Look at the top 3 cards in the deck. Don't show them to the other players and replace them in the same order when done." << endl;

	}
	if (name == "Nope")
	{
		cout << "Nope negates the last action card that was played. Oddly enough, it does not negate exploding kittens or defuse cards." << endl;

	}
	if (name == "Shuffle")
	{
		cout << "Shuffles the draw pile." << endl;

	}
	if (name == "Favor")
	{
		cout << "Choose one player to give you a card of their choice." << endl;
	}
	if (name == "Skip")
	{
		cout << "The skip card will cause you to end your turn without drawing a card. After you play this card, your turn is over." << endl;

	}
	if (name == "Tacocat" || name == "Cattermelon" || name == "Hairy Potato Cat" || name == "Rainbow-Ralphing Cat" || name == "Beard Cat")
	{
		cout << "A funny image of a cat is on this card. If you have another cat card, you could pair them up and play them like an action card. Playing a pair allows you to steal another player's card from their hand without looking." << endl;

	}
	if (name == "Defuse")
	{
		cout << "You can successfully defuse an exploding kitten." << endl;

	}
	else
	{
		cout << "Error. No such card." << endl;

	}
}

void Player::showHand() //display cards in a player's hand
{
	for (int i = 0; i < hand.size(); i++)
	{
		cout << i << ". " << hand[i].getType() << endl;
	}
}

card Player::favor(Player& p)
{
	cout << endl << p.getName() << ", hand over a card.\n"; //prompts selected player to hand over a card
	p.showHand();
	int choice = 0; //used to store player's choice
	cin >> choice; //store player's choice
	while (choice > p.hand.size())
	{
		cin >> choice;
	}

	card returncard = p.hand[choice]; //card to be returned
	p.removeHand(choice);

	cout << endl;
	return returncard;
}

void Player::seeFuture(vector <card> pile) //player looks at the top three cards of the pile (the deck)
{
	card j1 = pile.back();
	card j2 = pile[pile.size() - 2];
	card j3 = pile[pile.size() - 3];
	cout << "Other players should turn away!" << endl;
	cout << "Card on top: " << j1.getType() << "." << endl; //first card
	cout << "Second card: " << j2.getType() << "." << endl; //second card
	cout << "Third card: " << j3.getType() << "." << endl; //third card
}

void Player::skip(bool & skip)
{
	skip = true;
}

card Player::pair(Player p)
{
	cout << p.name << ", takes a card from a selected player" << endl;
	p.showHand();
	int choice = 0; //card selected from player will be stored in this variable.
	cin >> choice;
	if (choice > p.hand.size())
	{
		while (choice > p.hand.size())
		{
			cout << "No card exists." << endl;
			cin >> choice; //store player's choice.
		}
	}
	card returnCard = p.hand[choice];
	p.getCard(choice);
	cout << endl;
	return returnCard;//returns choosen pair card
}

void Player::nope(int & nope, Player* Players, int numPlayers) //stops another player's action
{
	bool hasNope = false; //flag to test if player has nope card to play
	int nopeLocation; //stores location of nope card in player's hand
	for (int p = 0; p < hand.size(); p++)
	{
		if (hand[p].getType() == "Nope")
		{
			hasNope = true; //set flag to true if player has nope card
			nopeLocation = p;
		}
	}

	if (hasNope == true)
	{
		hand.erase(hand.begin() + nopeLocation); //removes nope from player's hand
		nope++; //increments nope integer in main function
	}

	else
	{
		cout << "\nToo bad, you don't have a nope card.";
		return;
	}

	cout << "Anybody gonna nope that nope? y/n: "; //prompt players to play nope cards
	char noper;
	cin >> noper; //accept nopes

	if (noper == 'y')
	{
		int nopePlayer; //stores name of player who played nope
		cout << "\nAlright, who noped that? Input your number."; //prompts player to own up to nope
		for (int z = 0; z < numPlayers; z++) //output list of players
		{
			cout << z << ". " << Players[z].getName();
		}
		cin >> nopePlayer; //input player who noped
		Players[nopePlayer].nope(nope, Players, numPlayers); //run appropriate player's nope function
	}
}

int Player::linearSearchPair(string key, int choice) //enter an array of any type and an "item" of the same type to search in the array
{

	int arraySize = hand.size();
	int j;
	for (int i = 0; i < arraySize; i++)
	{
		if (key == hand[i].getType())
		{
			j = i; //returns which number in the array the item was found
		}
	}
	if (j != arraySize + 2)
	{
		return j; //returns that nothing was found
	}
	else
	{
		return -1;
	}
}

bool Player::getDead() //returns whether or not a player has died
{
	return dead;
}

void Player::addHand(card& f) //adds a card to a player's hand, for use in pair protocol
{
	card h = card(f.getType());

	hand.push_back(h);

}

void Player::removeHand(int s) //removes an extra card in the case of pair
{
	vector<card> newhand;

	for (int i = 0; i < hand.size(); i++)
	{
		if (i != s)
		{
			newhand.push_back(hand[i]);
		}
	}

	hand.clear();
	for (int k = 0; k < newhand.size(); k++)
	{
		hand.push_back(newhand[k]);
	}
}
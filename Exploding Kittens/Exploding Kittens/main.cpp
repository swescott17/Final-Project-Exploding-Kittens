#include "player.h"
#include "card.h"
#include "function.h"
#include<fstream>
using namespace std;
/* This program is a simulation of The Oatmeal's "Exploding Kittens," and follows the original rules as posted
at: http://www.explodingkittens.com/how */
int main()
{
	cout << "Enter today's date as mm/dd/yy : "; //prompt user to enter date for file storage purposes
	string date;
	cin >> date; //store date input by user
	date.append(".txt"); //append .txt to input date in order to name data file
	ofstream fout; //create output stream
	fout.open(date); //create text document organized by input date for storing game results
	vector<card> pile; //pile of face-down cards to draw from

					   //strings used to maintain type consistency in some data comparisons
	string attack = "Attack";
	string skip = "Skip";
	string favor = "Favor";
	string pair = "Pair";
	string nope = "Nope";
	string future = "See the Future";
	string shuffle = "Shuffle";
	string name = "Tacocat";
	string cattermelon = "Cattermelon";
	string harycat = "Hairy Potato Cat";
	string rainbowcat = "Rainbow-Ralphing Cat";
	string beardcat = "Beard Cat";

	for (int n = 0; n < 4; n++) //generate cards in deck that are not player count dependent
	{
		pile.push_back(card("Attack"));
		pile.push_back(card("Skip"));
		pile.push_back(card("Favor"));
		pile.push_back(card("Shuffle"));
		pile.push_back(card("Tacocat"));
		pile.push_back(card("Cattermelon"));
		pile.push_back(card("Hairy Potato Cat"));
		pile.push_back(card("Rainbow-Ralphing Cat"));
		pile.push_back(card("Beard Cat"));
	}

	for (int n = 0; n < 5; n++) //generate cards in deck that are not player count dependent
	{
		pile.push_back(card("Nope"));
		pile.push_back(card("See the Future"));
	}

	int numPlayers = 0; //number of people playing
	cout << "It's time for Exploding Kittens!\nEnter number of players: "; //prompt user to input number of players for card generation

	cin >> numPlayers; //store input number of players

	for (int n = 0; n < 6 - numPlayers; n++) //generate defuse cards in draw pile
	{
		pile.push_back(card("Defuse"));
	}

	shuffleDeck(pile);//use non-member shuffle function to shuffle generated deck

	Player* Players; //pointer to players
	Players = new Player[numPlayers]; //allocate memory for players

	for (int n = 0; n < numPlayers; n++) //create players
	{
		string name;
		cout << "Enter name for P" << n << ": ";
		cin >> name;
		Players[n] = Player(name, pile);
	}


	for (int n = 0; n < numPlayers - 1; n++) //generate exploding kitten cards in draw pile
	{
		pile.push_back(card("Exploding Kitten"));
	}

	shuffleDeck(pile);//shuffle deck again using non-member function once exploding kittens have been added

	bool Attack = false; //flag used for attack card
	bool Skip = false; //flag used for skip card
	int Nope = 0; //flag used for nope card
	int livingPlayers = numPlayers; //used to exit game when all but one of the players have died

	while (livingPlayers > 1) //loops game until all but one player has died
	{
		for (int n = 0; n < numPlayers; n++)
		{
			if (livingPlayers == 1) //exit game and declare winner if all other players are dead
				continue;

			while (Players[n].getDead() == true) //check if current player is dead and skip them if so
			{
				cout << "\n" << Players[n].getName() << " is dead, so they don't play.";
				n++;
			}

			bool playedSkip = false; //flag to allow players who use skip cards to draw
			bool playedAttack = false; //allows players who played attack to draw one
			if (Skip == true) //skip current player if last player used a skip card
			{
				cout << "\nYou've been skipped, " << Players[n].getName() << "!\n";
				Skip = false; //reset skip flag to prevent skipping multiple players
				continue;
			}

			if (Attack == true) //output text informing player if they've been attacked
			{
				cout << "\nYou've been attacked, " << Players[n].getName() << "!\n";
			}

			int error = 1; //error integer
			do //if there is an error in the card played, then this will loop back
			{
				Nope = 0; //reset nope flag every turn
				cout << "Your turn, " << Players[n].getName() << ". Look away, everybody else." << endl; //Output player to take turn
				Players[n].showHand(); //Display player's hand 
				cout << "\nWould you like to draw and end your turn? y/n: "; //present option to end turn
				char ender = 'n'; //used to store player's decision to end their turn or not
				cin >> ender;
				if (ender == 'y') //exits loop if player chooses to end turn
				{
					error = 0;
					continue;
				}
				int choice;
				cout << "Which card will you play? Enter card #: "; //prompt player to input card choice
				cin >> choice;
				card playedCard = Players[n].getCard(choice); //temporarily store player's chosen card
				cout << "\nCard chosen: " << playedCard.getType() << endl; //output card chosen by player
				cout << "Anybody gonna nope that? y/n: "; //prompt players to play nope cards
				char nope;
				cin >> nope; //accept nopes

				if (nope == 'y')
				{
					int nopePlayer; //stores name of player who played nope
					cout << "\nAlright, who noped that?\n"; //prompts player to own up to nope
					for (int z = 0; z < numPlayers; z++) //output list of players
					{
						cout << z << ". " << Players[z].getName() << endl;
					}
					cout << "Input your number: ";
					cin >> nopePlayer; //input player who noped
					Players[nopePlayer].nope(Nope, Players, numPlayers); //run appropriate player's nope function
				}

				if (Nope % 2 == 0)
				{
					//The following series of if statements runs the function of the card chosen
					if (playedCard.getType() == "Attack") //protocol if attack card was chosen
					{
						Players[n].attack(Attack);
						playedAttack = true;
					}

					else if (playedCard.getType() == "Skip") //protocol if skip card  was chosen
					{
						Players[n].skip(Skip);
						playedSkip = true; //used to ensure that players using skip cards get to draw
					}

					else if (playedCard.getType() == "Favor") //protocol if favor card was chosen
					{
						cout << "Who do you want a favor from?"; //prompt player to choose favor victim
						for (int y = 0; y < numPlayers; y++) //output potential victims
						{
							if (y != n) //prevent current player from being a potential victim displayed
							{
								cout << y << ". " << Players[y].getName() << endl;
							}

						}
						int favorChoice; //used to store player's choice of favor victim
						cin >> favorChoice;
						Players[n].favor(Players[favorChoice]); //pass in chosen player to favor function
					}

					else if (playedCard.getType() == "Shuffle") //protocol if shuffle card was chosen
					{
						Players[n].shuffle(pile);
					}

					else if (playedCard.getType() == "See the Future") //protocol if see the future card was chosen
					{
						Players[n].seeFuture(pile);
					}
					else if (playedCard.getType() == name || playedCard.getType() == cattermelon || playedCard.getType() == harycat || playedCard.getType() == rainbowcat || playedCard.getType() == beardcat) //protocol if pair card was chosen
					{
						cout << endl;
						int f = Players[n].linearSearchPair(playedCard.getType(), choice); //checks if there is a pair
						if (f == -1) //if there is no pair
						{
							cout << "No such pair exists." << endl;
							cout << "Try again. It is still your turn." << endl;
						}
						else if (f != -1) //if the pair does exist the player may choose another player and card to take from them
						{
							for (int p = 0; p < numPlayers; p++)
							{
								if (p != n)
								{
									cout << p << "." << Players[p].getName() << endl;
									if (Players[p].getDead() == true)
									{
										cout << "Cannot Choose Player " << p << ". They are dead." << endl;
									}
								}
							}
							Players[n].removeHand(f); //removes the extra card from pair
							int check = 1;
							int pairChoice = 0;
							cin >> pairChoice;
							if (pairChoice == n || Players[pairChoice].getDead() == true) //card choice
							{
								do
								{
									cin >> pairChoice;
									if (pairChoice == n)
									{
										cout << "Cannot choose yourself!" << endl;
									}
									if (Players[pairChoice].getDead() == true)
									{
										cout << "Cannot choose dead players!" << endl;
									}
									else
									{
										check = 0;
									}
								} while (check == 1);
							}

							card paircard = Players[n].pair(Players[pairChoice]); //takes the card from the other player
							Players[n].addHand(paircard); //adds the new card to the player's hand
						}
					}
					else if (playedCard.getType() == favor) //favor is played
					{
						cout << endl;
						int favorchoice = numPlayers + 1;
						for (int i = 0; i < numPlayers; i++) //shows all the players that they can take a card from
						{
							if (i != n)
							{
								cout << i << ". " << Players[i].getName() << "." << endl;

							}
						}
						int check = 1;
						cout << "Enter the player number you want a favor from." << endl;
						cin >> favorchoice;
						if (favorchoice == n || Players[favorchoice].getDead() == true) //chooses a player to take a favor from
						{
							do
							{
								if (favorchoice == n)
								{
									cout << "Cannot choose yourself!" << endl; //cannot have a favor from yourself
									check = 1;
								}
								if (Players[favorchoice].getDead() == true) //cannot have a favor from a dead player
								{
									cout << "Cannot choose dead players!" << endl;
									check = 1;
								}
								if (favorchoice > numPlayers + 1)
								{
									cout << "No such player." << endl;
									check = 1;
								}
								else
								{
									if (favorchoice == n || Players[favorchoice].getDead() == true) //repeats if the player keeps choosing cards that do not work
									{
										cout << "Let's check again. Enter the player number you want a favor from." << endl;
										cin >> favorchoice;
										check = 0;
									}
								}
							} while (check != 0);
						}
						card favorcard = Players[n].favor(Players[favorchoice]); //choosen player's card given in favor
						Players[n].addHand(favorcard); //adds the card to hand
					}
				}
				else //protocol for successful nope
				{
					cout << "\nThe " << playedCard.getType() << " has been noped, so it does nothing!\n";
				}
			} while (error != 0);

			Players[n].endTurn(Attack, Skip, pile, playedSkip, playedAttack, livingPlayers); //player draws, ending turn
		}
	}


	int winner = 0; //used for storing winner following search of players, used for recording of winner in record sheet

	for (int m = 0; m < numPlayers; m++) //declare the winner of the game
	{
		if (Players[m].getDead() == false)
		{
			cout << "\n\n\nCongratulations, " << Players[m].getName() << "!\nYou survived!\nYour friends are dead, though.\n";
			winner = m;
		}
	}

	//Record winners/losers in text document
	fout << "Winner\n" << Players[winner].getName() << endl; //record who won
	fout << "\nDead Losers\n";
	for (int b = 0; b < numPlayers; b++) //record who died/lost
	{
		if (b != winner)
			fout << Players[b].getName() << endl; //add all players to list of losers except winner
	}

	/*This block of "end" code is just to prevent the program from terminating
	immediately after outputting winner.*/
	int end = 1;
	while (end != 0)
	{
		cout << endl;
		cout << "End? 0 to end: ";
		cin >> end;
	}

	return 0;
}

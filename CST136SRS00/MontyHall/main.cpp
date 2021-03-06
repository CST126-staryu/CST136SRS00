// MontyHall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LetsMakeADeal.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std; 

void help()
{
	cout <<
		"Let\'s Make a Deal - How to guide: \n"
		"Usage: MontyHall gameInstances switch|stay [total doors] [doors revealed]\n"
		"Example: MontyHall 1 stay 3 1\n"
		
		"GameInstances - How many games do you want to play?\n"
			
		"switch|stay - Would you like to keep your current door, or choose a new one after a door has been revealed....";
}

double gameInstanceVector(const int gameInstances, const LetsMakeADeal::switchOrStay choice, const int playerDoors, const int playerDoorsRevealed )
{
	// Vector of gameInstances add all objects to vector
	vector <LetsMakeADeal> gameInstanceCollection;
	for( auto count = 0; count != gameInstances; count++)
	{
		gameInstanceCollection.emplace_back(LetsMakeADeal(playerDoors, playerDoorsRevealed, choice));
	}
	
// Run game instance on each objects in vector
// Stuff result back to success rate for each object
	
	int carsWon{ 0 };
	int goatsWon{ 0 };

	for (auto& theGame : gameInstanceCollection)
	{
		auto outcome{ theGame.gameInstance() };
		if (outcome == LetsMakeADeal::outcome::car)
		{
			++carsWon; 
		}
		else
		{
			++goatsWon;
		}
	}
	
	// Total probability (cout?)
	assert(carsWon + goatsWon == gameInstances);

	return 1.0 * carsWon / gameInstanceCollection.size();
}
int main(int argc, char* argv[])
{
	int numberOfInstances {0};
	auto choice{ LetsMakeADeal::switchOrStay::unknown };
	auto playerDoors {3};
	auto playerDoorsRevealed {1};
	
// MontyHall gameInstances switch|stay [total doors] [doors revealed]
	auto showHelp{ true };

	if (argc >= 3 && argc < 6)
	{
		{
			istringstream convert{ argv[1] };
			convert >> numberOfInstances;
		}
		{
			if (string(argv[2]) == "switch"s)
			{
				choice = LetsMakeADeal::switchOrStay::change;
			}
			else if (string(argv[2]) == "stay"s)
			{
				choice = LetsMakeADeal::switchOrStay::noChange;
			}
		}
		{
			istringstream convert{ argv[3] };
			convert >> playerDoors;
		}
		{
			istringstream convert{ argv[4] };
			convert >> playerDoorsRevealed;
		}
		if (numberOfInstances >= 1 && choice != LetsMakeADeal::switchOrStay::unknown && playerDoors >= 3 && playerDoorsRevealed >= 1 && playerDoorsRevealed < playerDoors-1)
		{
			showHelp = false;
		}
	}
	if (showHelp)
	{
		help();
	}
	else
	{
		auto winRate{ gameInstanceVector(numberOfInstances,choice,playerDoors,playerDoorsRevealed) };
		cout << winRate;
		/*auto obj{ LetsMakeADeal(playerDoors, playerDoorsRevealed, choice) };
		auto game{ obj.gameInstance() };*/
	}


    return 0;
}


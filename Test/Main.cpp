#include "Class.h"
#include <iostream>
#include <string>

bool encounterStart(Monster& monster, Player& player);
void combat(Monster& monster, Player& player);

void playGame(Player& player)
{
	std::cout << "\nWelcome, " << player.getName() << ".\n\n";
	std::cout << "================================================================================\n";

	while (!player.isDead() || player.isWon())
	{
		std::cout << "You have " << player.getHealth() << " health and are carrying " << player.getGold() << " gold.\n\n";
		std::cout << "================================================================================\n";

		Monster currentMonster = Monster::getRandomMonster();
		std::cout << currentMonster.getName() << " appeared in front of you!\n";
		std::cout << "It has " << currentMonster.getHealth() << " health and " << currentMonster.getDamage() << " damage.\n\n";
		bool combatBegins{ encounterStart(currentMonster, player) };
		if (combatBegins)
		{
			combat(currentMonster, player);
		}
	}
	if (player.isWon())
	{
		std::cout << "Congratulations, you won by getting to level 20!\n";
	}
}

bool encounterStart(Monster& monster, Player& player)
{
	while (true)
	{
		std::string encounterDecision{};
		while (true)
		{
			std::cout << "What you gonna do ? (R)un or (F)ight ?:";
			std::getline(std::cin, encounterDecision);

			if (encounterDecision == "r" || encounterDecision == "f" || encounterDecision == "R" || encounterDecision == "F")
			{
				break;
			}
		}
		std::cout << "================================================================================\n";

		if (encounterDecision == "f" || encounterDecision == "F")
		{
			return true;	//combat starts
		}
		else
		{
			bool isSucceed{ static_cast<bool>(rand() % 2) };
			if (isSucceed)
			{
				std::cout << "Escape succeed!\n";
				std::cout << "================================================================================\n";
				return false;	//escape succeed
			}
			else
			{
				std::cout << "Escape failed, monster attacks you for " << monster.getDamage() << " damage.\n";
				player.reduceHealth(monster.getDamage());
				std::cout << "Your current health is: " << player.getHealth() << ".\n\n";
				if (player.isDead())
				{
					std::cout << "You are dead.\n";
					return false;	//player is dead
				}
			}
		}
	}
}

void combat(Monster& monster, Player& player)
{
	while (!player.isDead() && !monster.isDead())
	{
		std::cout << "You attack " << monster.getName() << " for " << player.getDamage() << ".\n";
		monster.reduceHealth(player.getDamage());
		std::cout << monster.getName() << " now have " << monster.getHealth() << " health.\n";
		if (monster.isDead())
		{
			std::cout << monster.getName() << " is killed!\n";
			player.levelUp();
			std::cout << "Level up! You are now at: " << player.getLevel() << " level.\n";
			std::cout << "You recieve " << monster.getGold() << " gold. Now you have: ";
			player.addGold(monster.getGold());
			std::cout << player.getGold() << " gold.\n";
			std::cout << "================================================================================\n";

			return;		//player killed monster
		}

		std::cout << monster.getName() << " attacks you for " << monster.getDamage() << " damage.\n";
		player.reduceHealth(monster.getDamage());
		std::cout << player.getName() << " is at " << player.getHealth() << " health.\n";
		if (player.isDead())
		{
			std::cout << "================================================================================\n";
			std::cout << "\t\t\tYou died.\n";
			std::cout << "================================================================================\n";

			return;		//monster killed player
		}
	}
}

bool restart()
{
	std::string userInput{};
	while (true)
	{
		std::cout << "New game? y/n: ";
		std::getline(std::cin, userInput);

		if (userInput == "y" || userInput == "Y" || userInput == "n" || userInput == "N")
		{
			break;
		}
	}

	if (userInput == "y" || userInput == "Y")
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand(static_cast<unsigned>(time(0)));

	std::cout << "Enter your name:";
	std::string name;
	std::getline(std::cin, name);
	Player player(name);

	bool isRestart{};
	do
	{
		playGame(player);

		isRestart = restart();
		player.reset();
	} while (isRestart);
}
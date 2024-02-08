
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <random>
#include "monster.h"



class Team
{
public:
	std::list<Monster> team_members;
	void add_to_team(Monster mon)
	{
		team_members.push_back(mon);
	}

	void display_team()
	{
		std::list<Monster>::iterator it;
		for (it = team_members.begin(); it != team_members.end(); ++it)
		{
			std::cout << "[" << it->element << " " << it->name << ", Health: " << it->health << ",  Attack: " << it->attack << "]";
			if (std::distance(it, team_members.end()) > 1)


			{
				std::cout << ", " << std::endl;
			}
		}
	}
};


void main()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	int character_id = 1;
	bool game_end = false;
	Team player_team;
	std::string characters[5] = { "Geralt", "Yennefer", "Triss", "Ciri", "Regis" };
	std::string elements[5] = { "Water", "Fire", "Wind", "Light", "Dark" };
	int player_choice;

	Monster dummy_mon("Dummy", 10, 100, "Dark");
	while (game_end == false)
	{
		while (true) 
		{
			std::cout << "\n==============================\n1. Summon a character" << std::endl << "2. View team" << std::endl << "Enter: " << std::endl;
			std::cin >> player_choice;
			if (player_choice == 1 || player_choice == 2 || player_choice == 3) 
			{
				break;
			}
			else 
			{
				std::cout << "Invalid input. Please enter a number between 1-3" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}
		}
		system("cls");

		if (player_choice == 1)
		{
			int RandIndex = std::uniform_int_distribution<int>(0, 4)(gen);
			int RandElem = std::uniform_int_distribution<int>(0, 4)(gen); 
			
			int character_attack = std::uniform_int_distribution<int>(10, 20)(gen); 
			int character_health = std::uniform_int_distribution<int>(90, 120)(gen);

			std::string character_name = characters[RandIndex];
			std::string character_elem = elements[RandElem];

			Monster new_character(character_name, character_attack, character_health, character_elem);
			std::cout << "Summoned " << new_character.name << std::endl;
			std::cout << "Health: " << new_character.health << std::endl;
			std::cout << "Attack: " << new_character.attack << std::endl;
			std::cout << "Element: " << new_character.element << std::endl;

			player_team.add_to_team(new_character);

		}
		else if (player_choice == 2)
		{
			player_team.display_team();
		}

		else if (player_choice == 3)
		{
			
			Monster& current_mon = player_team.team_members.front();

			std::cout << "Current mon element: " << current_mon.element << std::endl;
			std::cout << "Current mon attack: " << current_mon.attack << std::endl;


			current_mon.Attack(current_mon,dummy_mon);
			
			current_mon.Attack(current_mon, dummy_mon);
		}


	}
};
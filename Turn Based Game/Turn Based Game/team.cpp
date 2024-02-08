#include <iostream>
#include <list>
#include <string>

class Monster
{

public:
	std::string name;
	std::string element;
	int health = 100;
	int attack = 10;

	Monster(std::string n, int a, std::string e) : name(n), attack(a), element(e) {}

	void Attack(Monster other)
	{
		std::cout << health << std::endl;
		other.take_damage(attack);

	};

	void take_damage(int other_attack)
	{
		health -= other_attack;
		std::cout << health << std::endl;
		if (health <= 0)
		{
			std::cout << "Game over" << std::endl;
		}
	};
};

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
	int character_id = 1;
	bool game_end = false;
	Team player_team;
	std::string characters[5] = { "Geralt", "Yennefer", "Triss", "Ciri", "Regis" };
	std::string elements[5] = { "Water", "Fire", "Wind", "Light", "Dark" };
	int player_choice;
	while (game_end == false)
	{
		while (true) {
			std::cout << "\n==============================\n1. Summon a character" << std::endl << "2. View team" << std::endl << "Enter: " << std::endl;
			std::cin >> player_choice;
			if (player_choice == 1 || player_choice == 2) {
				break;
			}
			else {
				std::cout << "Invalid input. Please enter a number between 1-2" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}
		}
		system("cls");

		if (player_choice == 1)
		{
			int RandIndex = rand() % 5;
			int RandElem = rand() % 5;
			std::string character_name = characters[RandIndex];
			int character_attack = rand() % (21 - 10) + 10;
			std::string character_elem = elements[RandElem];

			Monster new_character(character_name, character_attack, character_elem);
			std::cout << "Summoned " << new_character.name << std::endl;
			std::cout << "Attack: " << new_character.attack << std::endl;
			std::cout << "Element: " << new_character.element << std::endl;

			player_team.add_to_team(new_character);

		}
		else if (player_choice == 2)
		{
			player_team.display_team();
		}


	}
};
#include <iostream>
#include <list>
#include <string>
#include "enemy.h"
#include <random>
#include <numeric>
#include "ability.h"

extern std::random_device rd;
extern std::mt19937 gen;

// Generate team of 5


void enemy::generate_team()
{
	std::string characters[5] = { "Geralt", "Yennefer", "Triss", "Ciri", "Regis" };
	std::string elements[5] = { "Water", "Fire", "Wind", "Light", "Dark" };
	
	while (enemy_team.team_members.size() < 5)
	{

		int RandIndex = std::uniform_int_distribution<int>(0, 4)(gen);
		int RandElem = std::uniform_int_distribution<int>(0, 4)(gen);

		int character_attack = std::uniform_int_distribution<int>(10, 20)(gen);
		int character_health = std::uniform_int_distribution<int>(90, 120)(gen);

		std::string character_name = characters[RandIndex];
		std::string character_elem = elements[RandElem];

		auto it = characterAbilities.begin();
		std::advance(it, RandIndex);

		auto ability1 = it->second.first;
		auto ability2 = it->second.second;

		Ability* ab_1 = new Ability(std::get<0>(ability1), std::get<1>(ability1), std::get<2>(ability1), std::get<3>(ability1), std::get<4>(ability1));
		Ability* ab_2 = new Ability(std::get<0>(ability2), std::get<1>(ability2), std::get<2>(ability2), std::get<3>(ability2), std::get<4>(ability2));

		Monster new_character(character_name, character_attack, character_health, character_health, character_elem, ab_1, ab_2);

		enemy_team.add_to_team(new_character);
	}
}
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <sstream>
#include <random>
#include <numeric>
#include "enemy.h"
#include "ability.h"


std::map<std::string, std::pair<Ability, Ability>> characterAbilities = {
	{"Geralt", std::make_pair(Ability("Fast Attack", 1, 1, false, 0), Ability("Strong Attack", 2, 1, false, 2))},
	{"Yennefer", std::make_pair(Ability("Telekinesis", 0.75, 3, false, 0), Ability("Transformation", 0.5, 5, false, 4))},
	{"Triss", std::make_pair(Ability("Fire Magic", 1, 1, false, 0), Ability("Illusion Magic", 1, 3, false, 3))},
	{"Ciri", std::make_pair(Ability("Elder Blood", 0.8, 2, false, 0), Ability("Swordfighting", 1.5, 2, false, 2))},
	{"Regis", std::make_pair(Ability("Blood leech", 1.25, 1, false, 0), Ability("Blood explosion", 0.75, 5, false, 4))}
};

void Ability::attack_units(Team team_to_attack)
{
	// int d_multiplyer;
	// int multiple; // Number of enemies to attack
	// bool freeze; // True if freezes enemies for one turn
	// int cooldown;
}
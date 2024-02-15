
#pragma once
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <random>

class Ability;
class Team;

class Monster
{

public:
	std::string name;
	std::string element;
	int health;
	int max_health;
	int attack;
	Ability* ability_1;
	Ability* ability_2;
	//Ability ability_1;
	//Ability ability_2;
	
	Monster(std::string n, int a, int h, int max, std::string e, Ability* ab1, Ability* ab2) : name(n), attack(a), health(h), max_health(max), element(e), ability_1(ab1), ability_2(ab2) {};

	std::map<std::string, std::map<std::string, double>> element_relations{};

	void Attack(Monster& self, Monster& other, int ability_number);

	void take_damage(Monster& self, int damage);

	void attack_other_team(Monster& attacking_monster, Team& other, int num_of_attacks, int chosen_ability);

	int ability_cooldown(Monster& self, Ability chosen_ability, int current_cooldown);
};

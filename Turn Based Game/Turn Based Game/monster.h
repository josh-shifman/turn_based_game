
#pragma once
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <random>
	
class Monster
{

public:
	std::string name;
	std::string element;
	int health;
	int attack;
	//Ability ability_1;
	//Ability ability_2;
	
	Monster(std::string n, int a, int h, std::string e) : name(n), attack(a), health(h), element(e) {};

	std::map<std::string, std::map<std::string, double>> element_relations{};

	void Attack(Monster& self, Monster& other);

	void take_damage(Monster& self, int damage);
};

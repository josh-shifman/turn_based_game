#include <iostream>
#include <list>
#include <string>
#include <map>
#include <random>
#include "monster.h"
extern std::random_device rd;
extern std::mt19937 gen;

std::map<std::string, std::map<std::string, double>> element_relations = {
		{"fire", {{"fire", 1.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 0.5}, {"dark", 2.0}}},
		{"water", {{"fire", 2.0}, {"water", 1.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 0.5}}},
		{"wind", {{"fire", 0.5}, {"water", 2.0}, {"wind", 1.0}, {"light", 0.5}, {"dark", 2.0}}},
		{"light", {{"fire", 2.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 1.0}, {"dark", 0.5}}},
		{"dark", {{"fire", 0.5}, {"water", 2.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 1.0}}}
};

void Monster::Attack(Monster& self, Monster& other)
{	
	// Critical strike chance against neutral enemy is 50%, with element advantage 75%, with element disadvantage 25%
	double effectiveness = element_relations[self.element][other.element];
	double damage = self.attack;

	std::uniform_real_distribution<double> dis(0, 1); 
	double critical_chance = 0.5;
	if (effectiveness > 1.0) {
		critical_chance = 0.75; 
	}

	if (dis(gen) < critical_chance) {
		damage *= 2; 
	}
	other.take_damage(self, damage);
		
};

void Monster::take_damage(Monster& self, int damage)
	{
		self.health -= damage;
		std::cout << "Dealt " << damage << "Damage to " << self.element << " " << self.name << ". Health remaining : " << self.health << std::endl;
	};

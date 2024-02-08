#include <iostream>
#include <list>
#include <string>
	
class Monster
{

public:
	std::string name;
	std::string element;
	int health;
	int attack;
	
	Monster(std::string n, int a, int h, std::string e) : name(n), attack(a), health(h), element(e) {}

	void Attack(Monster other) {};

	void take_damage(int other_attack){};
};
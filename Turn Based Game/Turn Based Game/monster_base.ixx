export module monster_base;

#include <iostream>
#include <list>
#include <string>

class __declspec(dllexport) Monster
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
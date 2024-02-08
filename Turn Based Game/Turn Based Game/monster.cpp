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
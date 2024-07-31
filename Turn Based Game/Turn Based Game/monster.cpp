#include <iostream>
#include <list>
#include <string>
#include <map>
#include <random>
#include "monster.h"
#include "ability.h"
#include "team.h"
extern std::random_device rd;
extern std::mt19937 gen;

std::map<std::string, std::map<std::string, double>> element_relations = {
		{"fire", {{"fire", 1.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 0.5}, {"dark", 2.0}}},
		{"water", {{"fire", 2.0}, {"water", 1.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 0.5}}},
		{"wind", {{"fire", 0.5}, {"water", 2.0}, {"wind", 1.0}, {"light", 0.5}, {"dark", 2.0}}},
		{"light", {{"fire", 2.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 1.0}, {"dark", 0.5}}},
		{"dark", {{"fire", 0.5}, {"water", 2.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 1.0}}}
};


bool Monster::operator==(const Monster& other) const {
	// Compare attributes of the two Monster objects
	return name == other.name && health == other.health;
}

void Monster::Attack(Monster& self, Monster& other, int ability_number, Team& team)
{
	// Critical strike chance against neutral enemy is 50%, with element advantage 75%, with element disadvantage 25%
	Ability chosen_ability{};
	if (ability_number == 1)
	{
		chosen_ability = *ability_1;
	}
	else
	{
		chosen_ability = *ability_2;
	}

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
	//damage = damage * selected_ability.d_multiplyer;
	damage = damage * chosen_ability.d_multiplyer;

	std::cout << chosen_ability.attack_name;
	other.take_damage(other, damage, team);
		
};

void Monster::take_damage(Monster& self, int damage, Team& team)
	{
		self.health -= damage;
		int hp = self.health;
		std::string elem = self.element;
		std::string mon_name = self.name;

		if (self.health < 0)
		{
			self.health = 0;
			hp = 0;
			kill_monster(self, team);
		}
		std::cout << " dealt " << damage << " Damage to " << elem << " " << mon_name << ". Health remaining : " << hp << std::endl;
	};

void Monster::attack_other_team(Monster& attacking_monster, Team& other, int num_of_attacks, int ability_number)
{
	Ability* chosen_ability = nullptr;

	if (ability_number == 1)
	{
		chosen_ability = ability_1;
	}
	else
	{
		chosen_ability = ability_2;
	}
	if (chosen_ability->cooldown > 0)
	{
		std::cout << "Error, ability on cooldown";
		return;
	}
	else
	{
		ability_cooldown(attacking_monster, chosen_ability);
	}

	if (num_of_attacks == 5)
	{
		for (Monster& teammate : other.team_members)
		{
			attacking_monster.Attack(attacking_monster, teammate, ability_number, other);
		}
	}
	else
	{
		std::list<Monster*> selected_teammates;
		std::list<Monster*> remaining_teammates;

		for (Monster& monster : other.team_members) {
			remaining_teammates.push_back(&monster);
		}

		// Select random indexes from the remaining_teammates list and add the corresponding pointers to selected_teammates
		while (selected_teammates.size() < num_of_attacks && !remaining_teammates.empty()) {
			std::uniform_int_distribution<int> dist(0, remaining_teammates.size() - 1);
			int index = dist(rd);

			auto it = remaining_teammates.begin();
			std::advance(it, index);

			selected_teammates.push_back(*it);

			remaining_teammates.erase(it);
		}

		for (Monster* teammate : selected_teammates)
		{
			attacking_monster.Attack(attacking_monster, *teammate, ability_number, other);
		}
	}
}

void Monster::ability_cooldown(Monster& self, Ability* chosen_ability)
{
	{
		
		if (chosen_ability->attack_name == std::get<0>(characterAbilities[self.name].first)) {
			ability_1->cooldown = std::get<4>(characterAbilities[self.name].first);
		}
		else {
			ability_2->cooldown = std::get<4>(characterAbilities[self.name].second);
		}
	}
}

void Monster::kill_monster(Monster& self, Team& team)
{
	team.team_members.erase(std::find(team.team_members.begin(), team.team_members.end(), self));
}

void Monster::level_up(Monster& self)
{
	self.level += 1;
	self.attack *= 1.1;
	self.health *= 1.1;
	self.max_health *= 1.1;

}

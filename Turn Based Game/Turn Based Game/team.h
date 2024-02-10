#include <iostream>
#include <list>
#include <string>
#include "monster.h"
#pragma once
class Team
{
public:
	std::list<Monster> all_monsters;
	std::list<Monster> team_members;
	void add_to_team(Monster mon);
	void swap_team(int old_mon, int new_mon);
	void display_team(bool collection_or_team);
	void attack_other_team(Team other);
};

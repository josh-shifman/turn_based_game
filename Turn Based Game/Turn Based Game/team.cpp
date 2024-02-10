#include <iostream>
#include <list>
#include <string>
#include "team.h"
#include "monster.h"

std::list<Monster> all_monsters;
std::list<Monster> team_members;

void Team::add_to_team(Monster mon)
{
	if (team_members.size() < 5)
	{
		team_members.push_back(mon);
	}
	else
	{
		all_monsters.push_back(mon);
	}

}

void Team::swap_team(int old_mon, int new_mon)
{


	auto it1 = team_members.begin();
	std::advance(it1, old_mon - 1);

	auto it2 = all_monsters.begin();
	std::advance(it2, new_mon - 1);
	
	all_monsters.push_back(*it1);
	team_members.push_back(*it2);
	team_members.erase(it1);

	all_monsters.erase(it2);
	
}

void Team::display_team(bool collection_or_team)
{
	std::list<Monster> mons_to_show{};

	if (collection_or_team == true)
	{
		int counter = 1;
		std::list<Monster>::iterator it;
		for (it = team_members.begin(); it != team_members.end(); ++it)
		{
			std::cout << counter << ". [" << it->element << " " << it->name << ", Health: " << it->health << "/ " << it->max_health << ",  Attack: " << it->attack << "]";
			counter++;
			if (std::distance(it, team_members.end()) > 1)

			{
				std::cout << ", " << std::endl;
			}
		}
	}

	else
	{
		int counter = 1;
		std::list<Monster>::iterator it;
		for (it = all_monsters.begin(); it != all_monsters.end(); ++it)
		{
			std::cout << counter << ". [" << it->element << " " << it->name << ", Health: " << it->health << "/ " << it->max_health << ",  Attack: " << it->attack << "]";
			counter++;
			if (std::distance(it, all_monsters.end()) > 1)


			{
				std::cout << ", " << std::endl;
			}
		}
	}



}


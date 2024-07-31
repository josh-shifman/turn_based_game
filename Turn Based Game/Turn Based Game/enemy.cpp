#include <iostream>
#include <list>
#include <string>
#include "enemy.h"
#include <random>
#include <numeric>
#include "ability.h"
#include "monster.h"


extern std::random_device rd;
extern std::mt19937 gen;

// Generate team of 5


void enemy::generate_team()
{
    std::string characters[5] = { "Geralt", "Yennefer", "Triss", "Ciri", "Regis" };
    std::string elements[5] = { "Water", "Fire", "Wind", "Light", "Dark" };

    while (enemy_team.team_members.size() < 5)
    {

        int RandIndex = std::uniform_int_distribution<int>(0, 4)(gen);
        int RandElem = std::uniform_int_distribution<int>(0, 4)(gen);

        int character_attack = std::uniform_int_distribution<int>(10, 20)(gen);
        int character_health = std::uniform_int_distribution<int>(90, 120)(gen);

        std::string character_name = characters[RandIndex];
        std::string character_elem = elements[RandElem];

        auto& abilities = characterAbilities[character_name];

        Ability* ab_1 = new Ability(std::get<0>(abilities.first), std::get<1>(abilities.first), std::get<2>(abilities.first), std::get<3>(abilities.first), std::get<4>(abilities.first));
        Ability* ab_2 = new Ability(std::get<0>(abilities.second), std::get<1>(abilities.second), std::get<2>(abilities.second), std::get<3>(abilities.second), std::get<4>(abilities.second));

        Monster new_character(character_name, character_attack, character_health, character_health, character_elem, ab_1, ab_2, 1);

        enemy_team.add_to_team(new_character);
    }
}
void enemy::select_move(Team& player_team)
{
    double bestScore = -std::numeric_limits<double>::infinity();
    Ability* best_ability = nullptr;
    int best_ability_number = 1;
    Monster* best_monster_to_attack = nullptr;
    Monster* best_monster_to_attack_with = nullptr;

    for (Monster& enemyMonster : enemy_team.team_members) {
        for (int abilityIndex = 0; abilityIndex < 2; ++abilityIndex) {
            Ability* ability = (abilityIndex == 0) ? enemyMonster.ability_1 : enemyMonster.ability_2;

            if (ability->cooldown > 0) {
                continue; 
            }

            for (Monster& playerMonster : player_team.team_members) {
                double score = calculateAbilityScore(enemyMonster, *ability, player_team);

                // Update the best ability if this one has a higher score
                if (score > bestScore) {
                    bestScore = score;
                    best_ability = ability;
                    best_monster_to_attack = &playerMonster;
                    best_monster_to_attack_with = &enemyMonster;
                    best_ability_number = abilityIndex + 1;
                }
            }
        }
    }

    

    if (best_ability != nullptr && best_monster_to_attack != nullptr && best_monster_to_attack_with != nullptr) {
        std::cout << "\n==============================\nEnemy attacked with: " << best_monster_to_attack_with->element << " " << best_monster_to_attack_with->name << std::endl;
        if (best_ability->multiple == 1) {
            best_monster_to_attack_with->Attack(*best_monster_to_attack_with, *best_monster_to_attack, best_ability_number, player_team);
        }
        else {
            best_monster_to_attack_with->attack_other_team(*best_monster_to_attack_with, player_team, best_ability->multiple, best_ability_number);
        }
    }
    else {
        std::cout << "No valid move selected!" << std::endl;
    }
}

double enemy::calculateAbilityScore(const Monster& enemyMonster, const Ability& ability, const Team& player_team) {
    double score = 0.0;
    std::map<std::string, std::map<std::string, double>> element_relations = {
        {"fire", {{"fire", 1.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 0.5}, {"dark", 2.0}}},
        {"water", {{"fire", 2.0}, {"water", 1.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 0.5}}},
        {"wind", {{"fire", 0.5}, {"water", 2.0}, {"wind", 1.0}, {"light", 0.5}, {"dark", 2.0}}},
        {"light", {{"fire", 2.0}, {"water", 0.5}, {"wind", 2.0}, {"light", 1.0}, {"dark", 0.5}}},
        {"dark", {{"fire", 0.5}, {"water", 2.0}, {"wind", 0.5}, {"light", 2.0}, {"dark", 1.0}}}
    };

    // Check if the ability is single-target or multi-target
    if (ability.multiple == 1) {

        double lowestHealth = std::numeric_limits<double>::max();
        Monster* targetMonster = nullptr;
        for (const Monster& playerMonster : player_team.team_members) {
            if (playerMonster.health < lowestHealth) {
                lowestHealth = playerMonster.health;
                targetMonster = const_cast<Monster*>(&playerMonster);
            }
        }

        double damage = enemyMonster.attack * ability.d_multiplyer;

        double effectiveness = element_relations[enemyMonster.element][targetMonster->element];
        damage *= effectiveness;

        score += damage;
    }
    else {
        // If the ability targets the entire team, element advantage doesn't matter
        if (ability.multiple == 5) {
            score = enemyMonster.attack * ability.d_multiplyer * 5; 
        }
        else {
            // If the ability targets a subset of the team, just assign a random score
            score = std::uniform_real_distribution<double>(0, 100)(gen); 
        }
    }

    return score;
}
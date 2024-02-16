#include <iostream>
#include <list>
#include <string>
#include <map>
#include <sstream>
#include <random>
#include <numeric>
#include "ability.h"
#include <vector>

std::map<std::string, std::pair<std::tuple<std::string, double, int, bool, int>, std::tuple<std::string, double, int, bool, int>>> characterAbilities = {
    {"Geralt", std::make_pair(std::make_tuple("Fast Attack", 1, 1, false, 0), std::make_tuple("Strong Attack", 2, 1, false, 2))},
    {"Yennefer", std::make_pair(std::make_tuple("Telekinesis", 0.75, 3, false, 0), std::make_tuple("Transformation", 0.5, 5, false, 4))},
    {"Triss", std::make_pair(std::make_tuple("Fire Magic", 1, 1, false, 0), std::make_tuple("Illusion Magic", 1, 3, false, 3))},
    {"Ciri", std::make_pair(std::make_tuple("Elder Blood", 0.8, 2, false, 0), std::make_tuple("Swordfighting", 1.5, 2, false, 2))},
    {"Regis", std::make_pair(std::make_tuple("Blood leech", 1.25, 1, false, 0), std::make_tuple("Blood explosion", 0.75, 5, false, 4))}
};


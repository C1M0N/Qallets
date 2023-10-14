//
// Created by Yukio on 13/10/2023.
//

#ifndef QALLETS_P1_DICE_H
#define QALLETS_P1_DICE_H

#include <ftxui/component/component.hpp>
#include <random>
#include <string>

ftxui::Component DndDice(std::string& display_name, std::string& temp_name);

std::string Dice(const std::string& diceCode);
int RandCIM(int randMin, int randMax);


#endif  // QALLETS_P1_DICE_H

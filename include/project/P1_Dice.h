//
// Created by Yukio on 13/10/2023.
//

#ifndef QALLETS_P1_DICE_H
#define QALLETS_P1_DICE_H

#include <ftxui/component/component.hpp>
#include <random>
#include <string>

class ConsoleToWindow_DndDice : public ftxui::ComponentBase{
 public:
  ConsoleToWindow_DndDice();

  ftxui::Element Render() override;

 private:
  std::string console_Code;
  std::string inner_Data;
  std::string hint_Text;
  ftxui::Component input_Module;
  ftxui::InputOption EnterEndType;

};

ftxui::Component DndDice();

std::string Dice(const std::string& diceCode);
int RandCIM(int randMin, int randMax);


#endif  // QALLETS_P1_DICE_H

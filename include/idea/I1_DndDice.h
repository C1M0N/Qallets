//
// Created by Yukio on 13/10/2023.
//

#ifndef QALLETS_I1_DNDDICE_H
#define QALLETS_I1_DNDDICE_H

#include <ftxui/component/component.hpp>
#include <random>
#include <string>
#include <map>

#include "../../include/tool/FtxuiTools.h"
#include "../../include/tool/Math.h"

class ConsoleToWindow_DndDice : public ftxui::ComponentBase{
 public:
  ConsoleToWindow_DndDice();

  void ConsoleProcessing();

  ftxui::Element Render() override;

 private:
  std::string console_Code;
  std::string inner_Data;
  std::string hint_Text;
  std::vector<ftxui::Element> output_Data;
  ftxui::Component input_Module;
  ftxui::InputOption EnterEndType;

  enum Command{
    UNDEFINED,
    HELP,
    EXIT
  };

  std::map<std::string,Command> command_Map ={
      {"help", HELP},
      {"exit", EXIT}
  };

};

ftxui::Component DndDice();

std::string Dice(const std::string& diceCode);


#endif  // QALLETS_I1_DNDDICE_H

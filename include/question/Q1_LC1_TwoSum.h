//
// Created by Yukio on 31/10/2023.
//

#ifndef QALLETS_Q1_LC1_TWOSUM_H
#define QALLETS_Q1_LC1_TWOSUM_H

#include <ftxui/component/component.hpp>
#include <string>
#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "../../include/tool/FtxuiTools.h"
#include "../../include/tool/Math.h"

class ctw_twosum : public ftxui::ComponentBase{
 public:
  ctw_twosum();

  void ConsoleProcessing();

  ftxui::Element Render() override;

 private:
  int process_index;
  std::string console_Code;
  std::string inner_Data;
  std::string hint_Text;
  std::string raw_Output_Data;
  std::vector<ftxui::Element> output_Data;
  ftxui::Component input_Module;
  ftxui::InputOption EnterEndType;

  std::vector<int> uniqueSumTwo;
  std::unordered_set<int> uniqueAdder;
  std::vector<int> number_Input;
  std::vector<int> sum_Two;

  enum Command{
    UNDEFINED,
    HELP,
    EXIT,
    RESET
  };

  std::map<std::string,Command> command_Map ={
      {"help", HELP},
      {"exit", EXIT},
      {"reset", RESET}
  };

};

ftxui::Component TwoSum();

#endif  // QALLETS_Q1_LC1_TWOSUM_H

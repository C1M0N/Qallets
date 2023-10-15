//
// Created by Yukio on 14/10/2023.
//

#ifndef QALLETS_P2_SNOWDIAMOND_H
#define QALLETS_P2_SNOWDIAMOND_H

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

#include "../../include/tool/FtxuiTools.h"

class ConsoleToWindow_Diamond : public ftxui::ComponentBase{
 public:
  ConsoleToWindow_Diamond();

  ftxui::Element Render() override;

 private:
  std::string console_Code;
  std::string inner_Data;
  std::string hint_Text;
  ftxui::Component input_Module;
  ftxui::InputOption EnterEndType;

};

ftxui::Component ShowDiamond();

std::string SnowFlake(const std::string& maxLength);

#endif  // QALLETS_P2_SNOWDIAMOND_H

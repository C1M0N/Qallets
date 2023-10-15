//
// Created by Yukio on 14/10/2023.
//

#ifndef QALLETS_P2_SNOWDIAMOND_H
#define QALLETS_P2_SNOWDIAMOND_H

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>


ftxui::Component ShowDiamond();
std::string SnowFlake(const std::string& maxLength);
std::vector<ftxui::Element> FtxuiMultiline(const std::string& originalText);

#endif  // QALLETS_P2_SNOWDIAMOND_H

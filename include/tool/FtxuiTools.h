//
// Created by Yukio on 15/10/2023.
//

#ifndef QALLETS_FTXUITOOLS_H
#define QALLETS_FTXUITOOLS_H

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

namespace LsKu {

class FTxT {
 public:
  static std::vector<ftxui::Element> MultiLine(const std::string& originalText);
};
}  // namespace LsKu
#endif  // QALLETS_FTXUITOOLS_H

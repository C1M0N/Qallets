//
// Created by Yukio on 15/10/2023.
//

#ifndef QALLETS_CONSOLETOWINDOW_H
#define QALLETS_CONSOLETOWINDOW_H

#include <ftxui/component/component.hpp>
#include <string>
#include <functional>
#include <utility>

using ProcessorFunc = std::function<std::string(const std::string&)>;
using RenderOptions = std::function<ftxui::Element()>;

class ConsoleToWindow : public ftxui::ComponentBase {
 public:
  ConsoleToWindow(ProcessorFunc processor, RenderOptions renderer);
  ftxui::Element Render() override;

 protected:
  std::string inner_Data;
  ftxui::Component input_Module;
  std::string hint_Text;

 private:
  std::string console_Code;
  ProcessorFunc processor_;
  RenderOptions render_options;
};

#endif  // QALLETS_CONSOLETOWINDOW_H

//
// Created by Yukio on 15/10/2023.
//

#include "../../include/tool/ConsoleToWindow.h"

ConsoleToWindow::ConsoleToWindow(ProcessorFunc processor, RenderOptions renderOptions)
    : processor_(std::move(processor)), render_options(std::move(renderOptions)) {

  ftxui::InputOption EnterEndType;
  EnterEndType.on_enter = [&] {
    inner_Data = processor_(console_Code);
    console_Code.clear();
  };
  input_Module = ftxui::Input(&console_Code, "Console", EnterEndType);
  Add(input_Module);
}

ftxui::Element ConsoleToWindow::Render() {
  return render_options();
}
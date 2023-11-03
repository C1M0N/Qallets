#include "../../include/tool/Template.h"
/*
/// 窗口运行逻辑
ctw_twosum::ctw_twosum() {
  hint_Text = "_提示文字_\n";

  /// 当用户按下Enter键时，将console_Code的值赋给inner_Data并清除console_Code和提示文字
  EnterEndType.on_enter = [&] {
    inner_Data = console_Code;
    inner_Data.pop_back();
    console_Code.clear();
    hint_Text.clear();
    ConsoleProcessing();
  };

  input_Module = Input(&console_Code, "Console", EnterEndType);  // 配置输入组件并添加到当前组件
  Add(input_Module);
}

void ctw_twosum::ConsoleProcessing() {
  if (inner_Data.substr(0, 1) == "/") {
    std::string command_String = inner_Data.substr(1);  // 删去末尾的空字符
    Command console_Command = UNDEFINED;
    output_Data.clear();

    if (command_Map.find(command_String) != command_Map.end()) {
      console_Command = command_Map[command_String];
    }
    switch (console_Command) {
      case HELP:
        output_Data.push_back(ftxui::text("_帮助文字_"));
        break;
      case EXIT:

        break;
      case UNDEFINED:
        output_Data.push_back(ftxui::text("错误：未知代码->" + command_String));
        break;
    }
  } else {
    output_Data = LsKu::FTxT::MultiLine((inner_Data)); // 输出部分
  }
  hint_Text = "again?";
}

/// 窗口渲染
ftxui::Element ctw_twosum::Render() {
  return ftxui::vbox({ftxui::vbox(output_Data) | ftxui::flex,  // 显示菱形
                      ftxui::separator(),                      // 添加分隔线
                      ftxui::text(hint_Text),                  // 在输入组件上显示提示文本
                      input_Module->Render()}) |               // 渲染输入组件
         ftxui::border |
         ftxui::flex;  // 添加边框
}

/// 提交组件
ftxui::Component TwoSum() {  // 创建一个窗口内容的函数，其中包含一个输入组件，用于让用户输入其名字
  return ftxui::Make<ctw_twosum>();  // 返回新创建的ConsoleToWindow_Dice组件
}
*/
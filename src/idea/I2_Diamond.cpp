//
// Created by Yukio on 14/10/2023.
//

#include "../../include/idea/I2_Diamond.h"

/// 窗口运行逻辑
ConsoleToWindow_Diamond::ConsoleToWindow_Diamond() {
  hint_Text = "请输入一个奇数\n";

  EnterEndType.on_enter = [&] {  /// 当用户按下Enter键时，将console_Code的值赋给inner_Data并清除console_Code和提示文字
    inner_Data = console_Code;
    inner_Data.pop_back();
    console_Code.clear();
    hint_Text.clear();
    ConsoleProcessing();
  };

  input_Module = Input(&console_Code, "Console", EnterEndType);  // 配置输入组件并添加到当前组件。
  Add(input_Module);
}

/// 内部处理逻辑
void ConsoleToWindow_Diamond::ConsoleProcessing() {
  if (inner_Data.substr(0, 1) == "/") {
    std::string command_String = inner_Data.substr(1);
    Command console_Command = UNDEFINED;
    output_Data.clear();

    if (command_Map.find(command_String) != command_Map.end()) {
      console_Command = command_Map[command_String];
    }
    switch (console_Command) {
      case HELP:
        output_Data.push_back(ftxui::text("本程序是一个根据用户输入半径，来进行雪花菱生成的应用"));
        break;
      case EXIT:

        break;
      case UNDEFINED:
        output_Data.push_back(ftxui::text("错误：未知代码->" + command_String));
        break;
    }
  } else {
    output_Data = LsKu::FTxT::MultiLine(SnowFlake(inner_Data));
  }
  hint_Text = "again?";
}

/// 窗口渲染
ftxui::Element ConsoleToWindow_Diamond::Render() {
  return ftxui::vbox({
               ftxui::vbox(output_Data) | ftxui::flex,  // 显示菱形
               ftxui::separator(),                      // 添加分隔线
               ftxui::text(hint_Text),                  // 在输入组件上显示提示文本
               input_Module->Render()                   // 渲染输入组件
           }) |
           ftxui::border | ftxui::flex;  // 添加边框
  }

/// 提交组件
ftxui::Component ShowDiamond() {  // 创建一个显示菱形的函数，其中包含一个输入组件，用于让用户输入菱形的半径。
  return ftxui::Make<ConsoleToWindow_Diamond>();  // 返回新创建的ConsoleToWindow_Diamond组件
}

/// SnowDiamond函数实现
std::string SnowFlake(const std::string& maxLength) {
  std::string spaceString;
  std::string snowflakeString = "*";

  std::string output;

  int maxLength_i = stoi(maxLength);
  int midLength = (maxLength_i - 1) / 2;  // 计算出多少次循环后应该反转过程
  for (int i = 0; i <= midLength; i++) {  /// 先求得单边空格最大值
    spaceString += " ";
  }
  for (int i = 0; i < midLength; i++) {  /// 组合成串后减空加星
    output.append(spaceString).append(snowflakeString).append(spaceString).append("\n");
    spaceString.pop_back();
    snowflakeString += "**";
  }

  output += (spaceString + snowflakeString + spaceString + "\n");  // 中间段生成

  for (int i = midLength + 1; i < maxLength_i; i++) {  /// 后半段减空加星后组合成串
    snowflakeString.pop_back();
    snowflakeString.pop_back();
    spaceString += " ";
    output.append(spaceString).append(snowflakeString).append(spaceString).append("\n");
  }

  return output;
}
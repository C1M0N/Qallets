//
// Created by Yukio on 13/10/2023.
//

#include "../../include/project/P1_Dice.h"

/// 窗口运行逻辑
ConsoleToWindow_DndDice::ConsoleToWindow_DndDice() {
  hint_Text = "请输入骰子代码\n";

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

void ConsoleToWindow_DndDice::ConsoleProcessing() {
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
    output_Data = LsKu::FTxT::MultiLine(Dice(inner_Data));
  }
  hint_Text = "again?";
}

/// 窗口渲染
ftxui::Element ConsoleToWindow_DndDice::Render() {
  return ftxui::vbox({ftxui::vbox(output_Data) | ftxui::flex,  // 显示菱形
                      ftxui::separator(),                                     // 添加分隔线
                      ftxui::text(hint_Text),                                 // 在输入组件上显示提示文本
                      input_Module->Render()}) |                              // 渲染输入组件
         ftxui::border | ftxui::flex;                                                       // 添加边框
}

/// 提交组件
ftxui::Component DndDice() {  // 创建一个窗口内容的函数，其中包含一个输入组件，用于让用户输入其名字
  return ftxui::Make<ConsoleToWindow_DndDice>();  // 返回新创建的ConsoleToWindow_Dice组件
}

/// Dice函数实现
std::string Dice(const std::string& diceCode) {
  size_t dice_pos;
  int diceAmount;
  int diceSides;
  int diceResult = 0;

  std::string finalResult;

  dice_pos = int(diceCode.find('d'));
  if (dice_pos > 0) {                                 // 检测d是否存在并且是否位置合理
    diceAmount = stoi(diceCode.substr(0, dice_pos));  // 将d前的数赋给骰子数变量
    diceSides = stoi(diceCode.substr(dice_pos + 1));  // 将d后的数赋给骰子面数变量
    for (int i = 0; i < diceAmount; i++) {  /// 用真随机数生成器生成骰子数个[1,骰子面数]随机数后求和
      int result = LsKu::Math::Rand(1, diceSides);
      diceResult += result;
    }
    finalResult = "您要的" + std::to_string(diceAmount) + "个" + std::to_string(diceSides) +
                  "面骰的计算结果为:" + std::to_string(diceResult);
  } else {
    finalResult = "ERROR";
  }
  return finalResult;
}

//
// Created by Yukio on 31/10/2023.
//

#include "../../include/question/Q1_LC1_TwoSum.h"

/// 窗口运行逻辑
ctw_twosum::ctw_twosum() {
  hint_Text = "请输入数字，中间用空格隔开\n";
  process_index = 0;
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
  int to_Vector;
  int answer1;
  int answer2;

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
      case RESET:
        process_index = 0;
        hint_Text = "请输入数字，中间用空格隔开\n";
        break;
      case EXIT:

        break;
      case UNDEFINED:
        output_Data.push_back(ftxui::text("错误：未知代码->" + command_String));
        break;
    }
  }
  else {
    std::stringstream lineToInput(inner_Data);
    switch(process_index){
      case 0:
        raw_Output_Data = "";
        uniqueAdder.clear();
        uniqueSumTwo.clear();
        number_Input.clear();
        sum_Two.clear();

        while(lineToInput >> to_Vector){
          number_Input.push_back(to_Vector);
        }

        for(int i = 0;i < number_Input.size();i++){
          for(int j = i + 1;j < number_Input.size();j++){
            sum_Two.push_back(number_Input[i] + number_Input[j]);
          }
        }

        raw_Output_Data += "你一开始输入的值为：\n";
        for(const int& n : number_Input){
          raw_Output_Data += std::to_string(n);
          raw_Output_Data += ", ";
        }
        raw_Output_Data.erase(raw_Output_Data.size() - 2);

        raw_Output_Data += "\n你所输入的数字两两相加共有";
        raw_Output_Data += std::to_string(LsKu::Math::Comb(int(number_Input.size()),2));
        raw_Output_Data += "种和。\n";

        for (int i : sum_Two){
          if (uniqueAdder.find(i) == uniqueAdder.end()){
            uniqueSumTwo.push_back(i);
            uniqueAdder.insert(i);
          }
        }

        raw_Output_Data += "分别为";
        for(const int& n : uniqueSumTwo){
          raw_Output_Data += std::to_string(n);
          raw_Output_Data += ", ";
        }
        raw_Output_Data.erase(raw_Output_Data.size() - 2);
        raw_Output_Data += "\n\n";

        output_Data = (LsKu::FTxT::MultiLine(raw_Output_Data)); // 输出部分
        hint_Text = "请从上述可能和中选择你想知道两数之和索引的和";
        process_index = 10;
        break;
      case 10:
        int sum_aim = std::stoi(inner_Data);
        std::unordered_map<int,int> sum_map;
        if (uniqueAdder.find(sum_aim) == uniqueAdder.end()){
          raw_Output_Data += "没找到，请重新输入\n";
          output_Data = (LsKu::FTxT::MultiLine(raw_Output_Data));

        }
        else{
          for(int i = 0; i < number_Input.size(); i++){
            if(sum_map.find((sum_aim - number_Input[i])) != sum_map.end()){
              answer1 = sum_map[sum_aim - number_Input[i]];
              answer2 = i;
            }
            sum_map[number_Input[i]] = i;
          }
          raw_Output_Data += "第" + std::to_string(answer1 + 1) + "个数\"" + std::to_string(number_Input[answer1]) + "\"与";
          raw_Output_Data += "第" + std::to_string(answer2 + 1) + "个数\"" + std::to_string(number_Input[answer2]) + "\"的和为";
          raw_Output_Data += std::to_string(sum_aim) + "\n";
          output_Data = (LsKu::FTxT::MultiLine(raw_Output_Data));
        }
        break;
    }
  }

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


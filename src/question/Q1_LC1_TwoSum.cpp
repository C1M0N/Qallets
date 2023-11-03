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

  /// 定义主进程函数每次运行前需初始化的变量
  int to_Vector;
  int answer1;
  int answer2;
  int sum_aim;
  std::unordered_map<int,int> sum_map;

  /// 底层指令判断
  if (inner_Data.substr(0, 1) == "/") { // 判断首字符是否是斜杠
    std::string command_String = inner_Data.substr(1);  // 删去末尾的空字符
    Command console_Command = UNDEFINED;  // 默认为报错
    output_Data.clear();

    /// 在斜杠后找到指定的几种指令后为switch判断变量赋值
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
        exit(0);
      case UNDEFINED:
        output_Data.push_back(ftxui::text("错误：未知代码->" + command_String) | ftxui::color(ccol_Red));
        break;
    }
  }

  /// 主逻辑
  else {
    std::stringstream lineToInput(inner_Data);  // 转换为字符串流以读取以空格为分隔的数字串
    switch(process_index){
      /// 0-「初始」分支
      case 0:
        /// 初始化需要每次程序reset时所需清除的成员变量
        raw_Output_Data = "";
        uniqueAdder.clear();
        uniqueSumTwo.clear();
        number_Input.clear();
        sum_Two.clear();

        /// 将inner_Data空格分割数字串转换为整数一维向量
        while(lineToInput >> to_Vector){
          number_Input.push_back(to_Vector);
        }

        /// 计算所有可能两数之和
        for(int i = 0;i < number_Input.size();i++){
          for(int j = i + 1;j < number_Input.size();j++){
            sum_Two.push_back(number_Input[i] + number_Input[j]);
          }
        }

        /// 输出全部已成功输入的数 并用逗号分隔
        output_Data.push_back(ftxui::text("你一开始输入的值为：\n"));
        for(const int& n : number_Input){
          raw_Output_Data += std::to_string(n);
          raw_Output_Data += ", ";
        }
        raw_Output_Data.erase(raw_Output_Data.size() - 2);  // 删去最后多余的逗号与空格
        output_Data.push_back(ftxui::text(raw_Output_Data) | ftxui::color(ccol_Orange));
        raw_Output_Data = "";

        /// 算出组合数并输出
        temp_Text = ftxui::hbox({
          ftxui::text("你所输入的数字两两相加共有"),
          ftxui::text(std::to_string(LsKu::Math::Comb(int(number_Input.size()),2))) | ftxui::color(ccol_Orange),
          ftxui::text("种和。")
        });
        output_Data.push_back(temp_Text);

        /// 在可能和中删去重复项 其中uniqueSumTwo按照原序 uniqueAdder从大到小排序
        for (int i : sum_Two){
          if (uniqueAdder.find(i) == uniqueAdder.end()){
            uniqueSumTwo.push_back(i);
            uniqueAdder.insert(i);
          }
        }

        /// 结果输出
        output_Data.push_back(ftxui::text("分别为:"));
        for(const int& n : uniqueSumTwo){
          raw_Output_Data += std::to_string(n);
          raw_Output_Data += ", ";
        }
        raw_Output_Data.erase(raw_Output_Data.size() - 2);
        output_Data.push_back(ftxui::text(raw_Output_Data) | ftxui::color(ccol_Orange));
        raw_Output_Data.clear();
        output_Data.push_back(ftxui::text(""));

        hint_Text = "请从上述可能和中选择你想知道两数之和索引的值";
        process_index = 10;
        break;

      /// 10-「找和」分支
      case 10:
        sum_aim = std::stoi(inner_Data);

        if (uniqueAdder.find(sum_aim) == uniqueAdder.end()){
          output_Data.push_back(ftxui::text("此数非可能和,请重新输入") | ftxui::color(ccol_Red));
        }
        else{

          /// 核心算法 O(n)时间复杂度
          for(int i = 0; i < number_Input.size(); i++){
            if(sum_map.find((sum_aim - number_Input[i])) != sum_map.end()){
              answer1 = sum_map[sum_aim - number_Input[i]];
              answer2 = i;
            }
            sum_map[number_Input[i]] = i;
          }

          /// 输出最终结果
          temp_Text = ftxui::hbox({
              ftxui::text("第"),
              ftxui::text(std::to_string(answer1 + 1)) | ftxui::color(ccol_Orange),
              ftxui::text("个数\""),
              ftxui::text(std::to_string(number_Input[answer1])) | ftxui::color(ccol_Orange),
              ftxui::text("\"与第"),
              ftxui::text(std::to_string(answer2 + 1)) | ftxui::color(ccol_Orange),
              ftxui::text("个数\""),
              ftxui::text(std::to_string(number_Input[answer2])) | ftxui::color(ccol_Orange),
              ftxui::text("\"的和为"),
              ftxui::text(std::to_string(sum_aim)) | ftxui::color(ccol_Orange)
          });
          output_Data.push_back(temp_Text);
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


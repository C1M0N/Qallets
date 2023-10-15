//
// Created by Yukio on 14/10/2023.
//

#include "../../include/project/P2_SnowDiamond.h"

ConsoleToWindow_Diamond::ConsoleToWindow_Diamond() {
  hint_Text = "Please type an odd number\n";

  EnterEndType.on_enter = [&] {  /// 当用户按下Enter键时，将console_Code的值赋给inner_Data并清除console_Code和提示文字
    inner_Data = SnowFlake(console_Code);
    console_Code.clear();
    hint_Text.clear();
  };

  input_Module = Input(&console_Code, "Console", EnterEndType);  // 配置输入组件并添加到当前组件。
  Add(input_Module);
}

ftxui::Element ConsoleToWindow_Diamond::Render() {
  return ftxui::vbox({ftxui::vbox(FtxuiMultiline(inner_Data)) | ftxui::flex,  // 显示菱形
                      ftxui::separator(),                                     // 添加分隔线
                      ftxui::text(hint_Text),                                 // 在输入组件上显示提示文本
                      input_Module->Render()}) |                              // 渲染输入组件
         ftxui::border;                                                       // 添加边框
}

ftxui::Component ShowDiamond() {  // 创建一个显示菱形的函数，其中包含一个输入组件，用于让用户输入菱形的半径。
  return ftxui::Make<ConsoleToWindow_Diamond>();  // 返回新创建的ConsoleToWindow_Diamond组件
}

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

std::vector<ftxui::Element> FtxuiMultiline(const std::string& originalText) {
  std::string process_data = originalText;  // 拷贝待处理字符串

  size_t line_breaker_pos;
  std::string line_breaker = "\n";
  std::vector<std::string> vectorize_lines;

  std::vector<ftxui::Element> ftxui_lines;  // 符合FTXUI规范的"多行文本"元素

  /// 将单个长多行字符串转化为向量字符串
  while ((line_breaker_pos = process_data.find(line_breaker)) != std::string::npos) {  // 寻找法定换行符
    vectorize_lines.push_back(process_data.substr(0, line_breaker_pos));  // 换行符前赋给向量字符串
    process_data.erase(0, line_breaker_pos + line_breaker.length());      // 删去处理完的字符串
  }
  vectorize_lines.push_back(process_data);  // 向向量字符串加入最后一个换行符后的文本

  /// 将向量字符串转化为"多行文本"元素
  ftxui_lines.reserve(vectorize_lines.size());  // 预先留出向量字符串数量的内存空间
  for (const auto& iterated_line : vectorize_lines) {
    ftxui_lines.push_back(ftxui::text(iterated_line));  // 向向量型元素内注入每个单行FTXUI文本
  }

  return ftxui_lines;
}
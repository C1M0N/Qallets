//
// Created by Yukio on 14/10/2023.
//

#include "P2_SnowDiamond.h"

ftxui::Component ShowDiamond(
    std::string& display_name,
    std::string& temp_name) {  // 创建一个显示菱形的函数，其中包含一个输入组件，用于让用户输入菱形的半径。
  class ConsoleToWindow_Diamond
      : public ftxui::ComponentBase {  // 创建一个自定义的组件ConsoleToWindow_Diamond，继承自ComponentBase。
   public:
    ConsoleToWindow_Diamond(std::string& display_name, std::string& temp_name)
        : inner_Data(display_name), console_Code(temp_name) {  // 构造函数，初始化内部组件。

      hint_Text = "Please type an odd number\n";  // 配置提示文字

      ftxui::InputOption EnterEndType;  // 配置输入选项。
      EnterEndType.on_enter =
          [&] {  /// 当用户按下Enter键时，将console_Code的值赋给inner_Data并清除console_Code和提示文字
            inner_Data = SnowFlake(console_Code);
            console_Code.clear();
            hint_Text = "";
          };

      input_Module = Input(&console_Code, "Console", EnterEndType);  // 配置输入组件并添加到当前组件。
      Add(input_Module);
    }

    ftxui::Element Render() override {
      return ftxui::vbox({vbox(FtxuiMultiline(inner_Data)) | ftxui::flex,  // 显示菱形
                          ftxui::separator(),                              // 添加分隔线
                          ftxui::text(hint_Text),                          // 在输入组件上显示提示文本
                          input_Module->Render()}) |                       // 渲染输入组件
             ftxui::border;                                                // 添加边框
    }

   private:  /// 私有变量：用于存储和显示数据
    std::string& inner_Data;
    std::string& console_Code;
    std::string hint_Text;
    ftxui::Component input_Module;  // 输入组件
  };
  return ftxui::Make<ConsoleToWindow_Diamond>(display_name, temp_name);  // 返回新创建的ConsoleToWindow_Diamond组件
}

std::string SnowFlake(const std::string& maxLength) {
  int maxLength_i = stoi(maxLength);
  int midLength = (maxLength_i - 1) / 2;  // 计算出多少次循环后应该反转过程
  std::string spaceString;
  std::string snowflakeString = "*";
  std::string output;

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
  size_t pos;
  std::string process_data = originalText;
  std::string line_breaker = "\n";
  std::vector<std::string> vectorize_lines;
  std::vector<ftxui::Element> ftxui_lines;

  while ((pos = process_data.find(line_breaker)) != std::string::npos) {
    vectorize_lines.push_back(process_data.substr(0, pos));
    process_data.erase(0, pos + line_breaker.length());
  }
  vectorize_lines.push_back(process_data);

  ftxui_lines.reserve(vectorize_lines.size());
  for (const std::string& iterated_line : vectorize_lines) {
    ftxui_lines.push_back(ftxui::text(iterated_line));
  }

  return ftxui_lines;
}
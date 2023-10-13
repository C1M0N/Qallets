#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <random>
#include <string>
#include <vector>

std::string Dice(const std::string& diceCode);
std::string SnowFlake(const std::string& maxLength);

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
      std::vector<std::string> lines;  /// 多行文字转化
      std::string delimiter = "\n";
      size_t pos;
      std::string process_data = inner_Data;
      while ((pos = process_data.find(delimiter)) != std::string::npos) {
        lines.push_back(process_data.substr(0, pos));
        process_data.erase(0, pos + delimiter.length());
      }
      lines.push_back(process_data);
      std::vector<ftxui::Element> elements;
      elements.reserve(lines.size());
      for (const std::string& line : lines) {
        elements.push_back(ftxui::text(line));
      }

      return ftxui::vbox({vbox(elements) | ftxui::flex,  // 显示菱形
                          ftxui::separator(),            // 添加分隔线
                          ftxui::text(hint_Text),        // 在输入组件上显示提示文本
                          input_Module->Render()}) |     // 渲染输入组件
             ftxui::border;                              // 添加边框
    }

   private:  /// 私有变量：用于存储和显示数据
    std::string& inner_Data;
    std::string& console_Code;
    std::string hint_Text;
    ftxui::Component input_Module;  // 输入组件
  };
  return ftxui::Make<ConsoleToWindow_Diamond>(display_name, temp_name);  // 返回新创建的ConsoleToWindow_Diamond组件
}

ftxui::Component DndDice(
    std::string& display_name,
    std::string& temp_name) {  // 创建一个窗口内容的函数，其中包含一个输入组件，用于让用户输入其名字
  class ConsoleToWindow_Dice
      : public ftxui::ComponentBase {  // 创建一个自定义的组件ConsoleToWindow_Dice，继承自ComponentBase。
   public:
    ConsoleToWindow_Dice(std::string& display_name, std::string& temp_name)
        : inner_Data(display_name), console_Code(temp_name) {  // 构造函数，初始化内部组件
      ftxui::InputOption EnterEndType;                         // 配置输入选项
      EnterEndType.on_enter = [&] {  /// 当用户按下Enter键时，将console_Code的值赋给inner_Data并清除console_Code
        inner_Data = Dice(console_Code);
        console_Code.clear();
      };
      input_module = Input(&console_Code, "Console", EnterEndType);  // 创建输入组件并添加到当前组件
      Add(input_module);
    }

    ftxui::Element Render() override {                                       // 重写Render函数，用于渲染组件
      return ftxui::vbox({ftxui::text("Hello " + inner_Data) | ftxui::flex,  // 显示当前的名字
                          ftxui::separator(),                                // 添加分隔线
                          ftxui::text("Enter your name below:"),             // 输入提示文本
                          input_module->Render()}) |                         // 渲染输入组件
             ftxui::border;                                                  // 添加边框
    }

   private:  /// 私有变量：用于存储和显示数据
    std::string& inner_Data;
    std::string& console_Code;
    ftxui::Component input_module;  // 输入组件
  };

  return ftxui::Make<ConsoleToWindow_Dice>(display_name, temp_name);  // 返回新创建的ConsoleToWindow_Dice组件
}

int main() {
  std::string display_name_114;  /// 创建两组字符串变量，分别用于Window114和Window514
  std::string temp_name_114;
  std::string display_name_514;
  std::string temp_name_514;

  auto window_content_114 = DndDice(display_name_114, temp_name_114);  /// 使用前面定义的函数为两个窗口创建内容
  auto window_content_514 = ShowDiamond(display_name_514, temp_name_514);

  auto window_114 = ftxui::Window({
      /// 定义两个窗口，并设置其位置、大小和标题
      .inner = window_content_114,
      .title = "Window114",
      .left = 20,
      .top = 10,
      .width = 40,
      .height = 20,
  });
  auto window_514 = ftxui::Window({
      .inner = window_content_514,
      .title = "Window514",
      .left = 70,
      .top = 10,
      .width = 40,
      .height = 20,
  });

  auto window_container = ftxui::Container::Stacked({
      /// 创建一个容器并将两个窗口加入其中
      window_114,
      window_514,
  });

  auto screen = ftxui::ScreenInteractive::Fullscreen();  /// 创建全屏的交互式屏幕并运行主循环
  screen.Loop(window_container);

  return EXIT_SUCCESS;
}

int RandCIM(int randMin, int randMax) {
  std::random_device rd;                                   // 用于获得真随机数的种子
  std::mt19937 gen(rd());                                  // 使用Mersenne Twister伪随机数生成器
  std::uniform_int_distribution<> dist(randMin, randMax);  // 均匀分布的随机数，范围从randMin到randMax
  return dist(gen);
}

std::string Dice(const std::string& diceCode) {
  int dLocation;
  int diceAmount;
  int diceSides;
  int diceResult = 0;
  std::string finalResult;

  dLocation = int(diceCode.find('d'));
  if (dLocation > 0) {                                 // 检测d是否存在并且是否位置合理
    diceAmount = stoi(diceCode.substr(0, dLocation));  // 将d前的数赋给骰子数变量
    diceSides = stoi(diceCode.substr(dLocation + 1));  // 将d后的数赋给骰子面数变量
    for (int i = 0; i < diceAmount; i++) {  /// 用真随机数生成器生成骰子数个[1,骰子面数]随机数后求和
      int result = RandCIM(1, diceSides);
      diceResult += result;
    }
    finalResult = "您要的" + std::to_string(diceAmount) + "个" + std::to_string(diceSides) +
                  "面骰的计算结果为: " + std::to_string(diceResult);
  } else {
    finalResult = "ERROR";
  }
  return finalResult;
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
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <random>
#include <string>

using namespace ftxui;
using namespace std;

string Dice(const string& diceCode);
string SnowFlake(const string& maxLength);

Component ShowDiamond(string& display_name, string& temp_name) {
  class ConsoleToWindow_Diamond : public ComponentBase {
   public:
    ConsoleToWindow_Diamond(string& display_name, string& temp_name)
        : inner_Data(display_name), console_Code(temp_name) {
      InputOption EnterEndType;
      Add(input_Module);
      hint_Text = "Please type an odd number\n";
      input_Module = Input(&console_Code, "Console", EnterEndType);

      EnterEndType.on_enter = [&] {
        inner_Data = SnowFlake(console_Code);
        console_Code.clear();
        hint_Text = "";
      };
    }

    Element Render() override {
      vector<std::string> lines;  // 多行文字转化⬇
      string delimiter = "\n";
      size_t pos;
      string process_data = inner_Data;
      while ((pos = process_data.find(delimiter)) != std::string::npos) {
        lines.push_back(process_data.substr(0, pos));
        process_data.erase(0, pos + delimiter.length());
      }
      lines.push_back(process_data);

      vector<Element> elements;
      elements.reserve(lines.size());
      for (const string& line : lines) {
        elements.push_back(text(line));
      }  // 多行文字转化⬆

      return vbox({vbox(elements) | flex, separator(), text(hint_Text), input_Module->Render()}) | border;
    }

   private:
    string& inner_Data;
    string& console_Code;
    string hint_Text;
    Component input_Module;
  };
  return Make<ConsoleToWindow_Diamond>(display_name, temp_name);
}

// 创建一个窗口内容的函数，其中包含一个输入组件，用于让用户输入其名字。
Component DndDice(string& display_name, string& temp_name) {
  // 创建一个自定义的组件Impl，继承自ComponentBase。
  class ConsoleToWindow_Dice : public ComponentBase {
   public:
    // 构造函数，初始化内部组件。
    ConsoleToWindow_Dice(string& display_name, string& temp_name) : inner_Data(display_name), console_Code(temp_name) {
      // 配置输入选项。
      InputOption input_option;
      // 当用户按下Enter键时，将temp_name的值赋给display_name并清除temp_name。
      input_option.on_enter = [&] {
        inner_Data = Dice(console_Code);
        console_Code.clear();
      };
      // 创建输入组件并添加到当前组件。
      input_module = Input(&console_Code, "Console", input_option);
      Add(input_module);
    }

    // 重写Render函数，用于渲染组件。
    Element Render() override {
      return vbox({// 显示当前的名字。
                   text("Hello " + inner_Data) | flex,
                   // 添加分隔线。
                   separator(),
                   // 输入提示文本。
                   text("Enter your name below:"),
                   // 渲染输入组件。
                   input_module->Render()}) |
             border;  // 添加边框。
    }

   private:
    // 私有变量：用于存储和显示名字。
    string& inner_Data;
    string& console_Code;
    // 输入组件。
    Component input_module;
  };

  // 返回新创建的Impl组件。
  return Make<ConsoleToWindow_Dice>(display_name, temp_name);
}

int main() {
  // 创建两组字符串变量，分别用于Window114和Window514。
  std::string display_name_114;
  std::string temp_name_114;
  std::string display_name_514;
  std::string temp_name_514;

  // 使用前面定义的函数为两个窗口创建内容。
  auto window_content_114 = DndDice(display_name_114, temp_name_114);
  auto window_content_514 = ShowDiamond(display_name_514, temp_name_514);

  // 定义两个窗口，并设置其位置、大小和标题。
  auto window_114 = Window({
      .inner = window_content_114,
      .title = "Window114",
      .left = 20,
      .top = 10,
      .width = 40,
      .height = 20,
  });

  auto window_514 = Window({
      .inner = window_content_514,
      .title = "Window514",
      .left = 70,
      .top = 10,
      .width = 40,
      .height = 20,
  });

  // 创建一个容器并将两个窗口加入其中。
  auto window_container = Container::Stacked({
      window_114,
      window_514,
  });

  // 创建全屏的交互式屏幕并运行主循环。
  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(window_container);

  return EXIT_SUCCESS;
}

int RandCIM(int randMin, int randMax) {
  random_device rd;                                   // 用于获得真随机数的种子
  mt19937 gen(rd());                                  // 使用Mersenne Twister算法的伪随机数生成器
  uniform_int_distribution<> dist(randMin, randMax);  // 均匀分布的随机数，范围从1到6
  return dist(gen);
}

string Dice(const string& diceCode) {
  int dLocation;
  int diceAmount;
  int diceSides;
  int diceResult = 0;
  string finalResult;

  dLocation = int(diceCode.find('d'));
  if (dLocation < 100 && dLocation > 0) {
    diceAmount = stoi(diceCode.substr(0, dLocation));
    diceSides = stoi(diceCode.substr(dLocation + 1));
    for (int i = 0; i < diceAmount; i++) {
      int result = RandCIM(1, diceSides);
      diceResult += result;
      // cout << result << "\n";
    }
    // cout << "您要的" << diceAmount << "个" << diceSides << "面骰的计算结果为:";
    finalResult = to_string(diceResult);
  } else {
    finalResult = "ERROR";
  }
  return finalResult;
}

string SnowFlake(const string& maxLength) {
  int maxLength_i = stoi(maxLength);
  int midLength = (maxLength_i - 1) / 2;
  string spaceString;
  string snowflakeString = "*";
  string output;

  for (int i = 0; i <= midLength; i++) {
    spaceString += " ";
  }
  for (int i = 0; i < midLength; i++) {
    output.append(spaceString).append(snowflakeString).append(spaceString).append("\n");
    spaceString.pop_back();
    snowflakeString += "**";
  }

  output += (spaceString + snowflakeString + spaceString + "\n");

  for (int i = midLength + 1; i < maxLength_i; i++) {
    snowflakeString.pop_back();
    snowflakeString.pop_back();
    spaceString += " ";
    output.append(spaceString).append(snowflakeString).append(spaceString).append("\n");
  }

  return output;
}
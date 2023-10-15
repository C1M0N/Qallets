//
// Created by Yukio on 13/10/2023.
//

#include "P1_Dice.h"

ftxui::Component DndDice() {  // 创建一个窗口内容的函数，其中包含一个输入组件，用于让用户输入其名字
  class ConsoleToWindow_Dice
      : public ftxui::ComponentBase {  // 创建一个自定义的组件ConsoleToWindow_Dice，继承自ComponentBase。
   public:
    ConsoleToWindow_Dice(){  // 构造函数，初始化内部组件
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
    std::string inner_Data;
    std::string console_Code;
    ftxui::Component input_module;  // 输入组件
  };

  return ftxui::Make<ConsoleToWindow_Dice>();  // 返回新创建的ConsoleToWindow_Dice组件
}

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

int RandCIM(int randMin, int randMax) {
  std::random_device rd;                                   // 用于获得真随机数的种子
  std::mt19937 gen(rd());                                  // 使用Mersenne Twister伪随机数生成器
  std::uniform_int_distribution<> dist(randMin, randMax);  // 均匀分布的随机数，范围从randMin到randMax
  return dist(gen);
}

#include <ftxui/component/screen_interactive.hpp>

#include "P1_Dice.h"
#include "P2_SnowDiamond.h"



int main() {
  std::string display_name_114;  /// 创建两组字符串变量，分别用于Window114和Window514
  std::string temp_name_114;
  std::string display_name_514;
  std::string temp_name_514;

  auto window_content_114 = DndDice();  /// 使用前面定义的函数为两个窗口创建内容
  auto window_content_514 = ShowDiamond();

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
#include "../include/main.h"

int main() {
  int mouse_x = 0;
  int mouse_y = 0;
  int question_tab_index = 0;
  int idea_tab_index = 0;
  int main_tab_index = 0;

  /// 组件转化为模块并命名
  auto Q1_lc1_test1 = DndDice();
  auto Q2_lc2_test2 = ShowDiamond();
  auto I1_dnddice = DndDice();
  auto I2_diamond = ShowDiamond();

  /// 模块分类至不同的tab内
  auto question_tab = ftxui::Container::Tab({
                                             Q1_lc1_test1,
                                             Q2_lc2_test2
                                         }, &question_tab_index);

  auto idea_tab = ftxui::Container::Tab({
                                              I1_dnddice,
                                              I2_diamond
                                          }, &idea_tab_index);

  /// 编辑程序显示名称
  std::vector<std::string> question_tab_display = {
      "测试1",
      "测试2"
  };

  std::vector<std::string> idea_tab_display = {
      "Dnd骰子",
      "字符菱形生成器"
  };

  /// 将tab的index与显示名称对应以创建可以选择的程序目录菜单
  auto question_tab_menu = ftxui::Menu(&question_tab_display, &question_tab_index);
  auto idea_tab_menu = ftxui::Menu(&idea_tab_display, &idea_tab_index);

  /// 将两个分支目录菜单并入主菜单
  auto main_tab = ftxui::Container::Tab({
                                            question_tab_menu,
                                            idea_tab_menu
                                   }, &main_tab_index);

  /// 编辑主菜单显示名称
  std::vector<std::string> main_tab_display = {
      "算法题",
      "自由实践"
  };

  /// 将主菜单的index与显示名称对应以创建带有动画的主菜单
  auto main_tab_menu = Menu(&main_tab_display, &main_tab_index, ftxui::MenuOption::HorizontalAnimated());

  /// 将主次级目录放入菜单主架构内以供鼠标区别目前停留的菜单层级
  auto menu_structure = ftxui::Container::Vertical({
      main_tab_menu,
      main_tab,
      question_tab,
      idea_tab
  });

  /// 使鼠标可以选择停留的菜单层级
  auto mouse_focus = CatchEvent(menu_structure, [&](ftxui::Event e) {
    if (e.is_mouse()) {
      mouse_x = (e.mouse().x - 1) * 2;
      mouse_y = (e.mouse().y - 1) * 4;
    }

    if (main_tab_index == 0) {
      menu_structure->SetActiveChild(question_tab);
    } else {
      menu_structure->SetActiveChild(idea_tab);
    }

    return false;
  });

  /// UI渲染架构
  auto user_interface = ftxui::Renderer(mouse_focus, [&] {
    return ftxui::hbox({
               ftxui::vbox({
                   main_tab_menu->Render(),
                   main_tab->Render()
               }),
               ftxui::separator(),
               main_tab_index == 0 ? question_tab->Render() : idea_tab->Render()
           }) |
           ftxui::border;
  });

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  screen.Loop(user_interface);

  return EXIT_SUCCESS;
}

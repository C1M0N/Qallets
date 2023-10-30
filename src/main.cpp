#include "../include/main.h"

int main() {
  int mouse_x = 0;
  int mouse_y = 0;
  int question_tab_index = 0;
  int idea_tab_index = 0;
  int main_tab_index = 0;

  auto Q1_lc1_test1 = DndDice();
  auto Q2_lc2_test2 = ShowDiamond();
  auto I1_dnddice = DndDice();
  auto I2_diamond = ShowDiamond();

  auto question_tab = ftxui::Container::Tab({
                                             Q1_lc1_test1,
                                             Q2_lc2_test2
                                         }, &question_tab_index);

  auto idea_tab = ftxui::Container::Tab({
                                              I1_dnddice,
                                              I2_diamond
                                          }, &idea_tab_index);

  std::vector<std::string> question_tab_display = {
      "测试1",
      "测试2"
  };

  std::vector<std::string> idea_tab_display = {
      "Dnd骰子",
      "字符菱形生成器"
  };

  auto question_tab_menu = ftxui::Menu(&question_tab_display, &question_tab_index);
  auto idea_tab_menu = ftxui::Menu(&idea_tab_display, &idea_tab_index);



  auto main_tab = ftxui::Container::Tab({
                                            question_tab_menu,
                                            idea_tab_menu
                                   }, &main_tab_index);

  std::vector<std::string> main_tab_display = {
      "算法题", "自由实践"
  };

  auto main_tab_menu = Menu(&main_tab_display, &main_tab_index, ftxui::MenuOption::HorizontalAnimated());



  auto menu_structure = ftxui::Container::Vertical({
      main_tab_menu,
      main_tab,
      question_tab,
      idea_tab
  });

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

#include "../include/main.h"

int main() {
  int mouse_x = 0;
  int mouse_y = 0;

  auto window_content_114 = DndDice();
  auto window_content_514 = ShowDiamond();
  auto window_content_666 = DndDice();
  auto window_content_233 = ShowDiamond();

  int inner_selected_tab = 0;
  int inner_selected_tab2 = 0;
  auto inner_tab = ftxui::Container::Tab({
                                             window_content_114,
                                             window_content_514,
                                         }, &inner_selected_tab);

  auto inner_tab2 = ftxui::Container::Tab({
                                             window_content_233,
                                             window_content_666
                                         }, &inner_selected_tab2);

  std::vector<std::string> inner_tab_titles = {
      "114",
      "514"
  };

  std::vector<std::string> inner_tab_titles2 = {
      "233",
      "666"
  };

  auto inner_tab_toggle = ftxui::Menu(&inner_tab_titles, &inner_selected_tab);

  auto inner_tab_toggle2 = ftxui::Menu(&inner_tab_titles2, &inner_selected_tab2);

  auto big_content = ftxui::Container::Vertical({
      inner_tab_toggle,
      inner_tab,
  });

  int selected_tab = 0;

  auto tab = ftxui::Container::Tab({
                                       inner_tab_toggle,  // test1的内容
                                       inner_tab_toggle2      // test2目前为空
                                   }, &selected_tab);

  std::vector<std::string> tab_horizontal = {
      "test1", "test2"
  };
  auto tab_selection = Menu(&tab_horizontal, &selected_tab, ftxui::MenuOption::HorizontalAnimated());

  auto component2 = ftxui::Container::Vertical({
      tab_selection,
      tab,
  });

  auto tab_with_mouse = CatchEvent(component2, [&](ftxui::Event e) {
    if (e.is_mouse()) {
      mouse_x = (e.mouse().x - 1) * 2;
      mouse_y = (e.mouse().y - 1) * 4;
    }
    return false;
  });

  auto component_renderer = ftxui::Renderer(tab_with_mouse, [&] {
    return ftxui::hbox({ftxui::vbox({
                            tab_selection->Render(),
                            tab->Render()
                        }),
               ftxui::separator(),
                        selected_tab == 0 ? inner_tab->Render() : inner_tab2->Render()
           }) |
           ftxui::border;
  });

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  screen.Loop(component_renderer);

  return EXIT_SUCCESS;
}

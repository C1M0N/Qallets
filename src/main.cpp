#include "../include/main.h"

int main() {
  int mouse_x = 0;
  int mouse_y = 0;


  auto window_content_114 = DndDice();  /// 使用前面定义的函数为两个窗口创建内容
  auto window_content_514 = ShowDiamond();

  int selected_tab = 2;
  auto tab = ftxui::Container::Tab(
      {
          window_content_114,
          window_content_514
      },
      &selected_tab);

  auto tab_with_mouse = CatchEvent(tab, [&](ftxui::Event e) {
    if (e.is_mouse()) {
      mouse_x = (e.mouse().x - 1) * 2;
      mouse_y = (e.mouse().y - 1) * 4;
    }
    return false;
  });

  std::vector<std::string> tab_titles = {
      "114",
      "514"
  };

  auto tab_toggle = ftxui::Menu(&tab_titles, &selected_tab);

  auto component = ftxui::Container::Horizontal({
      tab_with_mouse,
      tab_toggle,
  });

  auto component_renderer = ftxui::Renderer(component, [&] {
    return ftxui::hbox({
               tab_toggle->Render(),
               ftxui::separator(),
               tab_with_mouse->Render(),
           }) |
           ftxui::border;
  });

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  screen.Loop(component_renderer);


  return EXIT_SUCCESS;
}
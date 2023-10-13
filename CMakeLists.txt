cmake_minimum_required(VERSION 3.26)
project(Qallets)

set(CMAKE_CXX_STANDARD 23)

add_executable(Qallets main.cpp)



include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)



target_link_libraries(Qallets PRIVATE ftxui::component)
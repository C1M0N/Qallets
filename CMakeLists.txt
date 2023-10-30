cmake_minimum_required(VERSION 3.26)
project(Qallets)

set(CMAKE_CXX_STANDARD 23)

add_executable(Qallets src/main.cpp
        src/project/P1_Dice.cpp
        include/project/P1_Dice.h
        src/project/P2_SnowDiamond.cpp
        include/project/P2_SnowDiamond.h
        include/main.h
        src/tool/ConsoleToWindow.cpp
        include/tool/ConsoleToWindow.h
        src/tool/FtxuiTools.cpp
        include/tool/FtxuiTools.h
        src/tool/Math.cpp
        include/tool/Math.h
)



include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)



target_link_libraries(Qallets PRIVATE ftxui::component)
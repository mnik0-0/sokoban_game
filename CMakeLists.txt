cmake_minimum_required(VERSION 3.10)
project(game_sokoban)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

# You can set CMake prefix path here or pass it to CMake executable.
#set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "/usr/bin")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -O3")

set(SOURCES solver/state.cpp solver/state.h solver/move.cpp solver/move.h solver/solver.cpp solver/solver.h main.cpp mainwindow.cpp mainwindow.h Controller.cpp Controller.h MatrixTableView.cpp MatrixTableView.h Model.cpp Model.h solver/position.cpp solver/position.h solver/puzzle.cpp solver/puzzle.h resources.qrc solver/state_solver.cpp solver/state_solver.h)

qt6_add_big_resources(RESOURCES)
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
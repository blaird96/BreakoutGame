cmake_minimum_required(VERSION 3.23)

project(BreakoutGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

set(BREAKOUT_SFML_ROOT "" CACHE PATH "Path to the SFML root that contains include/, lib/, and bin/")

if(NOT BREAKOUT_SFML_ROOT AND DEFINED ENV{BREAKOUT_SFML_ROOT})
    set(BREAKOUT_SFML_ROOT "$ENV{BREAKOUT_SFML_ROOT}")
endif()

set(_breakout_sfml_hints
    "${BREAKOUT_SFML_ROOT}"
    "C:/msys64/ucrt64"
    "C:/SFML-3.0.2"
)

find_path(BREAKOUT_SFML_INCLUDE_DIR
    NAMES SFML/Graphics.hpp
    HINTS ${_breakout_sfml_hints}
    PATH_SUFFIXES include
    REQUIRED
)

find_library(BREAKOUT_SFML_GRAPHICS_LIB
    NAMES sfml-graphics libsfml-graphics
    HINTS ${_breakout_sfml_hints}
    PATH_SUFFIXES lib
    REQUIRED
)

find_library(BREAKOUT_SFML_WINDOW_LIB
    NAMES sfml-window libsfml-window
    HINTS ${_breakout_sfml_hints}
    PATH_SUFFIXES lib
    REQUIRED
)

find_library(BREAKOUT_SFML_SYSTEM_LIB
    NAMES sfml-system libsfml-system
    HINTS ${_breakout_sfml_hints}
    PATH_SUFFIXES lib
    REQUIRED
)

find_library(BREAKOUT_SFML_AUDIO_LIB
    NAMES sfml-audio libsfml-audio
    HINTS ${_breakout_sfml_hints}
    PATH_SUFFIXES lib
    REQUIRED
)

find_library(BREAKOUT_SQLITE_LIB
    NAMES sqlite3 libsqlite3
    HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    PATH_SUFFIXES "" lib
    REQUIRED
)

add_library(breakout_common OBJECT
    Game.cpp
    src/GameManager.cpp
)

target_include_directories(breakout_common
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${BREAKOUT_SFML_INCLUDE_DIR}"
)

add_executable(breakout_phase1
    phase1_main.cpp
    $<TARGET_OBJECTS:breakout_common>
)

target_link_libraries(breakout_phase1
    PRIVATE
        "${BREAKOUT_SFML_GRAPHICS_LIB}"
        "${BREAKOUT_SFML_WINDOW_LIB}"
        "${BREAKOUT_SFML_SYSTEM_LIB}"
        "${BREAKOUT_SFML_AUDIO_LIB}"
        "${BREAKOUT_SQLITE_LIB}"
)

set_target_properties(breakout_phase1 PROPERTIES OUTPUT_NAME main)

if(BUILD_TESTING)
    add_executable(breakout_unit_tests
        tests/TestMain.cpp
        tests/GameHelpersTests.cpp
        tests/GameManagerTests.cpp
        tests/PhysicsManagerTests.cpp
        tests/Collision2DTests.cpp
        src/GameManager.cpp
    )

    target_include_directories(breakout_unit_tests
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
            "${BREAKOUT_SFML_INCLUDE_DIR}"
    )

    target_link_libraries(breakout_unit_tests
        PRIVATE
            "${BREAKOUT_SFML_GRAPHICS_LIB}"
            "${BREAKOUT_SFML_WINDOW_LIB}"
            "${BREAKOUT_SFML_SYSTEM_LIB}"
    )

    add_test(NAME breakout_unit_tests COMMAND breakout_unit_tests)
endif()

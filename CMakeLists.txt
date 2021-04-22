cmake_minimum_required(VERSION 3.5)

project(SmartBot LANGUAGES CXX)

add_compile_definitions(WIN32)
add_compile_definitions(WINVER=0x0601)
add_compile_definitions(_WIN32_WINNT=0x0601)
add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
add_compile_definitions(_WPP_WIN32)
add_compile_definitions(_WINDOWS)
add_compile_options(/EHsc)
add_compile_options(/W3)
add_compile_options(/fp:precise)
add_compile_options(/permissive-)
add_compile_options(/FC)
add_compile_options(/Zi)
add_compile_options(/MP${NPTUNNEL_MAX_DEGREE_OF_PARALELISM})
add_compile_options(/Zf)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        process_manager.h
        wpp/process.hpp
        wpp/filesystem.h
        address_manager.h
        memory_manager.h
        helper/includes.h
        helper/defines.h
        helper/enums.h
        helper/singleton.h
        wpp/timer_chronometer.h
        action_manager.h
        core/input_manager.h
        tab_healer.cpp
        tab_healer.h
        tab_healer.ui
        tab_spell_healer.cpp
        tab_spell_healer.h
        tab_spell_healer.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartBot
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(SmartBot SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SmartBot
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartBot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_property(TARGET SmartBot PROPERTY WIN32_EXECUTABLE true)

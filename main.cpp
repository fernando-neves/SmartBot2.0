/* THIS PROJECT INCLUDES */
#include "mainwindow.h"
#include <process_manager.h>
#include <address_manager.h>

/* WPP INCLUDES */
#include <wpp/process.hpp>

/* QT INCLUDES */
#include <QApplication>

/* C++ INCLUDES */
#include <iostream>
#include <windows.h>
#include <fstream>
#include <streambuf>

void show_console()
{
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
}

void intialize_singletons()
{
    process_manager::instance();
    address_manager::instance();
}

int main(int argc, char *argv[])
{
    show_console();
    //intialize_singletons();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

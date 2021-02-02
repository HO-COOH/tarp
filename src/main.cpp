/**
 * ------------------------
 *  FILE: main.cpp
 *
 *  Author: Saiini
 * ------------------------
 * Description:
 *   Tarp is a basic C project initializer i lazily coupled up.
 *
 * Copyright (C) Sutinder S. Saini. All rights reserved.
 *
 */

#include "rang.h"
#include <iostream>
#include "ProjectGenerator.hpp"


static void create_project(char const* project_name, char const* language)
{
    std::cout << rang::fg::red << "Creating project: " << project_name << "...\n" << rang::fg::reset;

    ProjectGeneratorFactory generator{ project_name, language == nullptr ? "c" : language };

    generator.generateAll();
}


int main(int argc, char const *argv[]) try{
#ifndef _DEBUG
    if (argc >= 2) {
        create_project(argv[1], argc==3? argv[2] : nullptr);
    }
    else
        ProjectGeneratorFactory::PrintHelp();
#else
    create_project("hello", "c");
#endif
}
catch (std::exception const& e)
{
    std::cerr << "Error: " << e.what() << '\n';
}
catch (...)
{
    std::cerr << "Unknown error" << '\n';
}

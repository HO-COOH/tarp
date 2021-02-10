#include "MakefileGenerator/MakefileGenerator.hpp"

#include <iostream>
#include <string>

void MakefileGenerator::throwErrorMessage(char const* generatorName)
{
    std::cerr << "The makefile generator: \"" << generatorName << "\" is not compatible of this language!\n";
}

std::string MakefileGenerator::getMakefileType(char const* input)
{
    if (input)
        return input;
    std::cout << "Makefile type (default = \"make\"): ";
    std::string makefileType;
    std::getline(std::cin, makefileType);
    return makefileType;
}

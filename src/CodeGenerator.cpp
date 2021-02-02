#include "CodeGenerator.hpp"
#include "ProjectGenerator.hpp"
#include <fstream>

bool CGenerator::registered = ProjectGeneratorFactory::registerCodeGenerator("c", [](ProjectDirCreator const& projectDir) -> std::unique_ptr<CodeGenerator> { return std::make_unique<CGenerator>(projectDir); });

bool CppGenerator::registered = ProjectGeneratorFactory::registerCodeGenerator("cpp", [](ProjectDirCreator const& projectDir) -> std::unique_ptr<CodeGenerator> { return std::make_unique<CGenerator>(projectDir); });

void CGenerator::generate()
{
    auto const& projectDirInfo = dynamic_cast<CppProjectDirCreator const&>(projectDir);
    std::ofstream main{ projectDirInfo.getSourceDir() + "/main.c" };
    main << 
R"(#include <stdio.h>

int main(void)
{
    printf("Hello world!\n");
    return 0;
}
)";
}

std::string CGenerator::getGeneratedFilename() const
{
    return "main.c";
}

std::string CppGenerator::getGeneratedFilename() const
{
    return "main.cpp";
}

void CppGenerator::generate()
{
    auto const& projectDirInfo = dynamic_cast<CppProjectDirCreator const&>(projectDir);
    std::ofstream main{ projectDirInfo.getSourceDir() + "/main.cpp" };
    main <<
R"(#include <iostream>

int main()
{
    std::cout << "Hello world!\n";
}
)";
}

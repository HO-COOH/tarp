#include "CodeGenerator/CppGenerator.hpp"
#include "ProjectGenerator.hpp"
#include "ProjectDirCreator/CppProjectDirCreator.hpp"
#include <fstream>


bool CppGenerator::registered = ProjectGenerator::registerCodeGenerator("cpp", [](ProjectDirCreator const& projectDir) -> std::unique_ptr<CodeGenerator> { return std::make_unique<CppGenerator>(projectDir); });


std::string_view CppGenerator::getGeneratedFilename() const
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

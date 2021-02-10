#include "CodeGenerator/CGenerator.hpp"
#include "ProjectGenerator.hpp"
#include "ProjectDirCreator/CppProjectDirCreator.hpp"
#include <fstream>

bool CGenerator::registered = ProjectGenerator::registerCodeGenerator("c", [](ProjectDirCreator const& projectDir) -> std::unique_ptr<CodeGenerator> { return std::make_unique<CGenerator>(projectDir); });

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

std::string_view CGenerator::getGeneratedFilename() const
{
    return "main.c";
}

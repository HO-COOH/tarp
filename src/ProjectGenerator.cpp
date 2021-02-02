#include "ProjectGenerator.hpp"
#include "CodeGenerator.hpp"
#include "MakefileCreator.hpp"
#include <iostream>

template<typename T>
struct type_identity
{
    using type = T;
};

template<typename LanguageString, typename FactoryFunction, typename...OptionalArgs>
auto FindFunctionInMap(std::unordered_map<LanguageString, FactoryFunction>& map, typename type_identity<LanguageString>::type const& key, OptionalArgs&&... args)
{
    using PtrType = decltype(map.find(key)->second(args...));
    if (auto iter = map.find(key); iter != map.end())
        return iter->second(std::forward<OptionalArgs>(args)...);
#ifdef _DEBUG
    std::cerr << "Could find key: " << key << '\n';
#endif
    return PtrType{ nullptr };
}

ProjectGeneratorFactory::ProjectGeneratorFactory(char const* projectName, char const* language)
{
    dir = FindFunctionInMap(ProjectDirCreatorFactory(), language, projectName);
    code = FindFunctionInMap(CodeGeneratorFactory(), language, *dir);
    makefile = FindFunctionInMap(MakefileCreatorFactory(), MakefileCreator::getMakefileType(), *dir, *code);  //TODO: add proper makefile argument
    if (dir)
        dir->create();
}

void ProjectGeneratorFactory::generateCode()
{
    if(code)
        code->generate();
}

void ProjectGeneratorFactory::generateMakefile()
{
    if(makefile)
        makefile->writeMakefile();
}

void ProjectGeneratorFactory::generateAll()
{
    generateCode();
    generateMakefile();
}

void ProjectGeneratorFactory::PrintHelp()
{
    std::cout <<
R"(Usage:
    tarp <project_name> <language (default = C)> <makefile (default = make)
Language:
    C
    Cpp
Makefile:
    make
    CMake
Example:
    tarp HelloWorld
)";
}

#include "ProjectGenerator.hpp"
#include "CodeGenerator/CodeGenerator.hpp"
#include "MakefileGenerator/MakefileGenerator.hpp"
#include "Utilities/GitInit.hpp"
#include <iostream>

/**
 * @brief In C++20, this is to prevent type deduction conflict
 * @tparam T The known type to prevent from auto type deduction
 */
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

ProjectGenerator::ProjectGenerator(char const* projectName, char const* language)
{
    dir = FindFunctionInMap(ProjectDirCreatorFactory(), language, projectName);
    code = FindFunctionInMap(CodeGeneratorFactory(), language, *dir);
    makefile = FindFunctionInMap(MakefileCreatorFactory(), MakefileGenerator::getMakefileType(), *dir, *code);
    if (dir)
        dir->create();
}

void ProjectGenerator::generateCode()
{
    if(code)
        code->generate();
}

void ProjectGenerator::generateMakefile(char const* makefileType)
{
    if(!makefileType)
    {
    }
    else
    {
        if (makefile)
            makefile->writeMakefile();
    }
}

void ProjectGenerator::generateAll()
{
    generateCode();
    generateMakefile();
}

void ProjectGenerator::gitInit()
{
    std::cout << "Init a git repo y/n? (default = n): ";
    char c{};
    std::cin >> c;
    if(c=='y')
    {
        GitInitializer init{ *dir };
        init.addIgnoreDir("bin");
        init.addIgnoreDir("build");
    }
}

void ProjectGenerator::PrintHelp()
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

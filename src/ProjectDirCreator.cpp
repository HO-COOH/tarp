#include "ProjectDirCreator.hpp"
#include "rang.h"
#include "ProjectGenerator.hpp"

inline auto createDir(std::string const& path)
{
    std::cout << path << '\t';
    return std::filesystem::create_directories(path);
}

struct ConsoleColor
{
    ConsoleColor() { std::cout << rang::bg::blue; }
    ~ConsoleColor() { std::cout << rang::bg::reset << '\n'; }
};

bool CppProjectDirCreator::registered = 
    ProjectGeneratorFactory::registerProjectDirCreator("c", [](char const* name)->std::unique_ptr<ProjectDirCreator> {return std::make_unique<CppProjectDirCreator>(name); })
    && 
    ProjectGeneratorFactory::registerProjectDirCreator("cpp", [](char const* name)->std::unique_ptr<ProjectDirCreator> {return std::make_unique<CppProjectDirCreator>( name); });

void CppProjectDirCreator::create()
{
    ConsoleColor const c;
    createDir(getBinDir());
    createDir(getSourceDir());
    createDir(getLibDir());
    createDir(getBuildDir());
    createDir(getDocDir());
    createDir(getBinDir());
    createDir(getIncludeDir());
}

#include "GitInit.hpp"
#include <cstdlib>
#include <string>
#include <exception>

GitInitializer::GitInitializer(ProjectDirCreator const& projectDir):projectDir(projectDir)
{
    init();
    gitIgnore.open(projectDir.getRootDir() + ".gitignore");
    if (!gitIgnore.is_open())
        throw std::runtime_error{ "Cannot open .gitignore" };//TODO: refactor this exception type
}

void GitInitializer::init() const
{
    system((std::string{ "git init" } + projectDir.getRootDir()).c_str());
}

void GitInitializer::addIgnoreFile(char const* fname)
{
    gitIgnore << fname << '\n';
}

void GitInitializer::addIgnoreDir(char const* dirName)
{

}

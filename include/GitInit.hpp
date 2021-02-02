#pragma once

#include <fstream>
#include "ProjectDirCreator.hpp"
class GitInitializer
{
    ProjectDirCreator const& projectDir;
    std::ofstream gitIgnore;
    void init() const;
public:
    GitInitializer(ProjectDirCreator const& projectDir);
    void addIgnoreFile(char const* fname);
    void addIgnoreDir(char const* dirName);
};
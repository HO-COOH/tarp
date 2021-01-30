#pragma once

#include <filesystem>
class ProjectDirCreator
{
public:
    virtual void createProjectDir(std::filesystem::path const& root) = 0;
};
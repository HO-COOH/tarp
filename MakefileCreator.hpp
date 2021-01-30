#pragma once

#include <filesystem>
#include <fstream>
#include <string>

class MakefileCreator
{
public:
    virtual void writeMakefile(std::filesystem::path const& path) const = 0;
    virtual void writeMakefile(const char *path) const = 0;
    virtual void writeMakefile(std::string const &path) const = 0;
    virtual void writeMakefile(std::ofstream &&stream) const = 0;
    virtual ~MakefileCreator() = 0;
};

class UnixMakefileCreator:public MakefileCreator
{
public:

};

class CMakeCreator:public MakefileCreator
{
};

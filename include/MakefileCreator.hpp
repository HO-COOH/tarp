#pragma once
#include <string>

//#include "ProjectDirCreator.hpp"

struct ProjectDirCreator;
struct CodeGenerator;

class MakefileCreator
{
protected:
    ProjectDirCreator const& projectDir;
    CodeGenerator const& code;
public:
    MakefileCreator(ProjectDirCreator const& projectDir, CodeGenerator const& code) :projectDir{ projectDir }, code{ code } {}
    virtual void writeMakefile() const = 0;
    static std::string getMakefileType();
    virtual ~MakefileCreator() = default;
};


class UnixMakefileCreator:public MakefileCreator
{
public:
    static bool registered;
    UnixMakefileCreator(ProjectDirCreator const& projectDir, CodeGenerator const& code) :MakefileCreator(projectDir, code){};
    void writeMakefile() const override;
};

class CMakeCreator:public MakefileCreator
{
public:
    static bool registered;
    CMakeCreator(ProjectDirCreator const& projectDir, CodeGenerator const& code):MakefileCreator(projectDir, code){}
    void writeMakefile() const override;
};

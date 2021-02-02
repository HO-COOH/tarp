#pragma once
#include "ProjectDirCreator.hpp"
#include <string>


class CodeGenerator
{
protected:
    ProjectDirCreator const& projectDir;
public:
    explicit CodeGenerator(ProjectDirCreator const& projectDir):projectDir{projectDir}{}
    virtual void generate() = 0;
    [[nodiscard]]virtual std::string getGeneratedFilename() const = 0;
    virtual ~CodeGenerator() = default;
};

class CGenerator :public CodeGenerator
{
    static bool registered;
public:
    explicit CGenerator(ProjectDirCreator const& projectDir)
        : CodeGenerator(projectDir)
    {
    }

    void generate() override;
    [[nodiscard]] std::string getGeneratedFilename() const override;
};

class CppGenerator :public CodeGenerator
{
    static bool registered;
public:
    explicit CppGenerator(ProjectDirCreator const& projectDir)
        : CodeGenerator(projectDir)
    {
    }

    void generate() override;
    [[nodiscard]] std::string getGeneratedFilename() const override;
};
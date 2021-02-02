#pragma once

#include <memory>
#include <unordered_map>

#include "CodeGenerator.hpp"
#include "MakefileCreator.hpp"

#ifdef _DEBUG
#include <iostream>
#endif

class CodeGenerator;
class MakefileCreator;
struct ProjectDirCreator;

class ProjectGeneratorFactory
{
    std::unique_ptr<ProjectDirCreator> dir;
    std::unique_ptr<MakefileCreator> makefile;
    std::unique_ptr<CodeGenerator> code;

    static auto& ProjectDirCreatorFactory()
    {
        static std::unordered_map<std::string, std::unique_ptr<ProjectDirCreator>(*)(char const*)> factory;
        return factory;
    }

    static auto& MakefileCreatorFactory()
    {
        static std::unordered_map<std::string, std::unique_ptr<MakefileCreator>(*)(ProjectDirCreator const&, CodeGenerator const&)> factory;
        return factory;
    }

    static auto& CodeGeneratorFactory()
    {
        static std::unordered_map<std::string, std::unique_ptr<CodeGenerator>(*)(ProjectDirCreator const&)> factory;
        return factory;
    }

public:
    static bool registerProjectDirCreator(char const* language, std::unique_ptr<ProjectDirCreator>(*factoryFunction)(char const*))
    {
        ProjectDirCreatorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered Project Dir Creator for: " << language << '\n';
#endif
        return true;
    }

    static bool registerCodeGenerator(char const* language, std::unique_ptr<CodeGenerator>(*factoryFunction)(ProjectDirCreator const&))
    {
        CodeGeneratorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered Code generator for: " << language << '\n';
#endif
        return true;
    }

    static bool registerMakefileCreator(char const* language, std::unique_ptr<MakefileCreator>(*factoryFunction)(ProjectDirCreator const&, CodeGenerator const&))
    {
        MakefileCreatorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered makefile generator for: " << language << '\n';
#endif
        return true;
    }

    ProjectGeneratorFactory(char const* projectName, char const* language);


    void generateCode();
    void generateMakefile();
    void generateAll();

    static void PrintHelp();

};

/*****************************************************************//**
 * \file   ProjectGenerator.hpp
 * \brief  The meta project generator class
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/

#pragma once

#include <memory>
#include <unordered_map>
#include <string_view>
#include "CodeGenerator/CodeGenerator.hpp"
#include "MakefileGenerator/MakefileGenerator.hpp"

#ifdef _DEBUG
#include <iostream>
#endif

//class CodeGenerator;
//class MakefileGenerator;
//struct ProjectDirCreator;


/**
 * @brief The project generator, managing a ProjectDirCreator, a MakefileGenerator and a CodeGenerator
 */
class ProjectGenerator
{
    std::unique_ptr<ProjectDirCreator> dir;
    std::unique_ptr<MakefileGenerator> makefile;
    std::unique_ptr<CodeGenerator> code;

    static auto& ProjectDirCreatorFactory()
    {
        static std::unordered_map<std::string_view, std::unique_ptr<ProjectDirCreator>(*)(char const*)> factory;
        return factory;
    }

    static auto& CodeGeneratorFactory()
    {
        static std::unordered_map<std::string_view, std::unique_ptr<CodeGenerator>(*)(ProjectDirCreator const&)> factory;
        return factory;
    }

    static auto& MakefileCreatorFactory()
    {
        static std::unordered_map<
            std::string_view,
            std::unique_ptr<MakefileGenerator>(*)(ProjectDirCreator const&, CodeGenerator const&)
        > factory;
        return factory;
    }

public:

    /**
     * @brief Register a factory function to create a subclass of ProjectDirCreator
     * @param language The language that ProjectDirCreator takes
     * @param factoryFunction The factory function, which should have the following signature:
     *  std::unique_ptr<ProjectDirCreator>(char const* language)
     * @return always true
     */
    static bool registerProjectDirCreator(char const* language, std::unique_ptr<ProjectDirCreator>(*factoryFunction)(char const*))
    {
        ProjectDirCreatorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered Project Dir Creator for: " << language << '\n';
#endif
        return true;
    }


    /**
     * @brief Register a factory function to create a subclass of CodeGenerator
     * @param language The language that CodeGenerator takes
     * @param factoryFunction The factory function, which should have the following signature:
     *  std::unique_ptr<CodeGenerator>(ProjectDirCreator const&)
     * @return always true
     */
    static bool registerCodeGenerator(char const* language, std::unique_ptr<CodeGenerator>(*factoryFunction)(ProjectDirCreator const&))
    {
        CodeGeneratorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered Code generator for: " << language << '\n';
#endif
        return true;
    }

    /**
     * @brief Register a factory function to create a subclass of MakefileCreator
     * @param language The language that MakefileCreator takes
     * @param factoryFunction The factory function, which should have the following signature:
     *  std::unique_ptr<CodeGenerator>(ProjectDirCreator const&, CodeGenerator const&)
     * @return always true
     */
    static bool registerMakefileCreator(
        char const* language,
        std::unique_ptr<MakefileGenerator> (*factoryFunction)(ProjectDirCreator const&, CodeGenerator const&)
    )
    {
        MakefileCreatorFactory()[language] = factoryFunction;
#ifdef _DEBUG
        std::cout << "Registered makefile generator for: " << language << '\n';
#endif
        return true;
    }

    /**
     * @brief Construct a ProjectGenerator with a projectName and a language
     * @param projectName a string representing the project name
     * @param language a string representing the language
     * @note Upon constructing a ProjectGenerator, the ProjectDirCreator will be called to
     * create a typical directory for the language-specific project
     */
    ProjectGenerator(char const* projectName, char const* language);


    /**
     * @brief Calling a CodeGenerator to generate the language-specific start-up code
     */
    void generateCode();

    /**
     * @brief Calling a MakefileGenerator to generate build system
     * @param makefileType Type of makefile, if null, read from console
     */
    void generateMakefile(char const* makefileType = nullptr);


    /**
     * @brief Equivalent to call generateCode() and generateMakefile()
     */
    void generateAll();

    
    /**
     * @brief Init a git repo
     */
    void gitInit();

    /**
     * @brief Print help message
     */
    static void PrintHelp();
};

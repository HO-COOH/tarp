/*****************************************************************//**
 * \file   CppGenerator.hpp
 * \brief  C++ code generator class
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/
#pragma once

#include "CodeGenerator.hpp"

 /**
  * @brief Subclass of CodeGenerator that generate a "Hello world" C++ program
  */
class CppGenerator :public CodeGenerator
{
    static bool registered;
public:
    /**
     * @brief Explicit constructor to initialize the internal reference to a ProjectDirCreator object to get information from it
     * @param projectDir a const reference to a ProjectDirCreator object
     */
    explicit CppGenerator(ProjectDirCreator const& projectDir) : CodeGenerator(projectDir) {}

    /**
     * @brief Generate a "Hello world" C++ program
     */
    void generate() override;

    /**
    * @brief Return the filename of language-specific generated start-up code
    * @return "main.cpp"
    */
    [[nodiscard]] std::string_view getGeneratedFilename() const override;
};
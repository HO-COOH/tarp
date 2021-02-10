/*****************************************************************//**
 * \file   CMakeGenerator.hpp
 * \brief  Subclass of MakefileGenerator that generate CMakeLists.txt
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/


#pragma once
#include "MakefileGenerator.hpp"

/**
 * @brief Subclass of MakefileGenerator that generates CMakeLists.txt
 */
class CMakeGenerator :public MakefileGenerator
{
    static constexpr auto name = "cmake";
    static bool registered;
public:
    /**
     * @brief The constructor initialize 2 reference members as the parameters
     */
    CMakeGenerator(ProjectDirCreator const& projectDir, CodeGenerator const& code) :MakefileGenerator(projectDir, code) {}

    /**
     * @brief Write CMakeLists.txt
     */
    void writeMakefile() const override;
};

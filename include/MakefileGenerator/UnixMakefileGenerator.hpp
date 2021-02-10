/*****************************************************************//**
 * \file   UnixMakefileGenerator.hpp
 * \brief  Subclass of MakefileGenerator that generate Unix Makefiles
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/
#pragma once

#include "MakefileGenerator.hpp"


/**
 * @brief Subclass of MakefileGenerator that generates Unix Makefiles
 */
class UnixMakefileGenerator :public MakefileGenerator
{
    static constexpr auto name = "make";
    static bool registered;
public:

    /**
     * @brief The constructor initialize 2 reference members as the parameters
     */
    UnixMakefileGenerator(ProjectDirCreator const& projectDir, CodeGenerator const& code) :MakefileGenerator(projectDir, code) {}

    /**
     * @brief Write unix makefiles
     */
    void writeMakefile() const override;
};

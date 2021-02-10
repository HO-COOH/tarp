/*****************************************************************//**
 * \file   MakefileGenerator.hpp
 * \brief  The abstract class of MakefileGenerator
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/
#pragma once
#include <string>

/*Forward declarations*/
struct ProjectDirCreator;
class CodeGenerator;

/**
 * @brief The abstract MakefileGenerator class, which shall be inherited by specific makefile generator
 * @details To create a makefile generator for a specific build system, any subclasses should
 *  1. inherit this class
 *  2. call ProjectGenerator::registerMakefileGenerator("<generator name>", FactoryFunction);
 *      where the FactoryFunction accepts a const reference to a ProjectDirCreator object and a const reference to a CodeGenerator object
 *      and returns a std::unique_ptr of this class, ie. to have this signature:
 *          std::unique_ptr<MakefileGenerator> FactoryFunction(ProjectDirCreator const&, CodeGenerator const&);
 *  For example, a CMakeGenerator
 *  \code{.cpp}
 *  class CMakeGenerator: public MakefileGenerator
 *  {
 *  private:
 *      static bool registered = ProjectGenerator::registerMakefileGenerator("cmake",
 *          [](ProjectDirCreator const& projectDir, CodeGenerator const& code) -> std::unique_ptr<MakefileGenerator>
 *          {
 *              return std::make_unique<CMakeGenerator>(projectDir, code);
 *          });
 *  public:
 *      //...
 *  };
 *  \endcode 
 *  3. Provide the definition of this virtual function:
 *  \code{.cpp}
 *      void writeMakefile();
 *  \endcode
 */
class MakefileGenerator
{
protected:
    ProjectDirCreator const& projectDir;
    CodeGenerator const& code;

    /**
     * @brief Print error message in case the makefile is incompatible with the language
     * @param generatorName name of the generator
     */
    static void throwErrorMessage(char const* generatorName);
public:
    /**
     * @brief The constructor initialize 2 reference members as the parameters
     */
    MakefileGenerator(ProjectDirCreator const& projectDir, CodeGenerator const& code) :projectDir{ projectDir }, code{ code } {}


    /**
     * @brief Write the language specific, buildsystem specific makefiles
     */
    virtual void writeMakefile() const = 0;

    /**
     * @brief Get the makefileGenerator from user input
     * @param input If input is nullptr, read from stdin. Mainly for testing purpose, otherwise should be always nullptr
     * @return String of the makefileGenerator type name 
     */
    static std::string getMakefileType(char const* input = nullptr);

    /**
     * @brief Defaulted virtual destructor, which is a no-op because there this class owns no data
     */
    virtual ~MakefileGenerator() = default;
};



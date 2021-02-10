/*****************************************************************//**
 * \file   CodeGenerator.hpp
 * \brief  The declaration of the abstract CodeGenerator class, which shall be inherited and override by subclasses 
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/
#pragma once
#include "ProjectDirCreator/ProjectDirCreator.hpp"
#include <string_view>


/**
 * @brief The abstract class of language-specific code generators
 * @details To create a code generator of a specific language, any subclasses needs to
 *  1. inherit this class
 *  2. call ProjectGenerator::registerCodeGenerator("<language name>", FactoryFunction);
 *          where the FactoryFunction accepts a const reference to a ProjectDirCreator object
 *          and returns a std::unique_ptr of this class, ie. to have this signature:
 *              std::unique_ptr<CodeGenerator> FactoryFunction(ProjectDirCreator const&);
 * For example, a JavaGenerator
 * \code{.cpp}
 *  class JavaGenerator: public CodeGenerator
 *  {
 *  private:
 *      bool registered = ProjectGenerator::registerCodeGenerator("java",
 *          [](ProjectDirCreator const& dir) -> std::unique_ptr<CodeGenerator>
 *          {
 *              return std::make_unique<JavaGenerator>(dir);
 *      });
 *  public:
 *      //...
 *  };
 *  \endcode
 *  3. Provide the definition of these 2 virtual functions:
 *  \code{.cpp}
 *      void generate();
 *      [[nodiscard]] std::string_view getGeneratedFilename() const;
 *  \endcode
 *  Also define a constructor that accepts a ProjectDirCreator as a const reference,
 *  which provides the necessary location for the code generator to write the generated code:
 *  \code{.cpp}
 *      explicit JavaGenerator(ProjectDirCreator const& projectDir) : CodeGenerator(projectDir) {}
 *  \endcode
 *
 *  Q: Why use inheritance instead of reading a configuration file?
 *  A: Because I thought some language-specific code generators may take more steps, like checking the project type,
 *      checking for system information etc... Therefore using inheritance provided greater flexibility, while still allowing
 *      a modular design.
 */
class CodeGenerator
{
protected:
    ProjectDirCreator const& projectDir;
public:

    /**
     * @brief Explicit constructor to initialize the internal reference to a ProjectDirCreator object to get information from it
     * @param projectDir a const reference to a ProjectDirCreator object
     */
    explicit CodeGenerator(ProjectDirCreator const& projectDir):projectDir{projectDir}{}

    
    /**
     * @brief The virtual destructor
     */
    virtual ~CodeGenerator() = default;

    /*These pure virtual functions must be override by subclasses*/


    /**
     * @brief Generate language-specific start-up code
     */
    virtual void generate() = 0;

    /**
     * @brief Return the filename of language-specific generated start-up code
     */
    [[nodiscard]]virtual std::string_view getGeneratedFilename() const = 0;
};

/*****************************************************************//**
 * \file   CppProjectDirCreator.hpp
 * \brief  The CppProjectDirCreator class
 * 
 * \author Peter
 * \date   February 2021
 *********************************************************************/


#pragma once
#include "ProjectDirCreator.hpp"

 /**
  * @brief Subclass of ProjectDirCreator, creating a typical C/C++ project structure
  */
struct CppProjectDirCreator :public ProjectDirCreator
{
private:
    static bool registered;
public:
    //Make it static instead of constexpr, so we can change it in the future
    inline static auto bin = "bin";
    inline static auto source = "src";
    inline static auto lib = "lib";
    inline static auto build = "build";
    inline static auto doc = "doc";
    inline static auto include = "include";

    /**
     * @brief Constructor taking a string as the project name to be the root of the project
     * @param root The project name
     */
    CppProjectDirCreator(std::string root) :ProjectDirCreator(std::move(root)) {}


    /**
     * @brief Constructor taking a std::filesystem::path as the root of the project
     * @param root The root path of the project
     */
    CppProjectDirCreator(std::filesystem::path&& root) :ProjectDirCreator(std::move(root)) {}


    /**
     * @brief Constructor taking a string as the project name to be the root of the project
     * @param root The project name
     */
    CppProjectDirCreator(char const* root) :ProjectDirCreator(root) {}

    [[nodiscard]] auto getBinDir() const { return projectName + '/' + bin; }
    [[nodiscard]] auto getSourceDir() const { return projectName + '/' + source; }
    [[nodiscard]] auto getLibDir() const { return projectName + '/' + lib; }
    [[nodiscard]] auto getBuildDir() const { return projectName + '/' + build; }
    [[nodiscard]] auto getDocDir() const { return projectName + '/' + doc; }
    [[nodiscard]] auto getIncludeDir() const { return projectName + '/' + include; }


    /**
     * @brief Create the language specific project structure
     * @details For a C/C++ project, it creates:
     *      <root>/<bin>
     *      <root>/<source>
     *      <root>/<lib>
     *      <root>/<build>
     *      <root>/<doc>
     *      <root>/<include>
     */ 
    void create() override;
};